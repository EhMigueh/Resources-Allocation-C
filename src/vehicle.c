#include "header.h"

// Calcular la distancia entre dos puntos (x1, y1) y (x2, y2)
float calculate_distance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Función para convertir una hora en formato HH:MM a minutos totales
int time_to_minutes(const char *time_str)
{
    int hours, minutes;
    sscanf(time_str, "%d:%d", &hours, &minutes);
    return hours * 60 + minutes;
}

// Validar los datos de los vehículos
void validate_vehicle_data(Vehicle *vehicles, int n_vehicles)
{
    for (int i = 0; i < n_vehicles; i++)
    {
        if (vehicles[i].capacity_volume <= 0 || vehicles[i].capacity_weight <= 0)
        {
            fprintf(stderr, "ERROR! El vehículo %s tiene capacidades inválidas.\n", vehicles[i].id);
            exit(EXIT_FAILURE);
        }
        if (vehicles[i].type < 1 || vehicles[i].type > 3)
        {
            fprintf(stderr, "ERROR! El vehículo %s tiene un tipo inválido.\n", vehicles[i].id);
            exit(EXIT_FAILURE);
        }
    }
}

void assign_vehicles_to_deliveries(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles, SchedulingMode mode)
{
    int completed_deliveries = 0;
    float total_wait_time = 0.0;
    float total_distance = 0.0;

    clock_t start_time = clock();

    for (int i = 0; i < n_deliveries; i++)
    {
        int assigned = 0;
        int best_vehicle = -1;
        float min_distance = FLT_MAX;

        for (int j = 0; j < n_vehicles; j++)
        {
            if (vehicles[j].type >= deliveries[i].vehicle_type &&
                vehicles[j].capacity_volume >= deliveries[i].volume &&
                vehicles[j].capacity_weight >= deliveries[i].weight &&
                time_to_minutes(vehicles[j].start) <= time_to_minutes(deliveries[i].start) + FLEXIBILITY_MINUTES &&
                time_to_minutes(vehicles[j].end) >= time_to_minutes(deliveries[i].end))
            {
                if (mode == NEAREST_NEIGHBOR)
                {
                    float distance_to_origin = calculate_distance(
                        vehicles[j].pos_x, vehicles[j].pos_y,
                        deliveries[i].origin_x, deliveries[i].origin_y);

                    int vehicle_available_time = time_to_minutes(vehicles[j].start);
                    int delivery_start_time = time_to_minutes(deliveries[i].start);
                    float time_difference = delivery_start_time - vehicle_available_time;
                    if (time_difference < 0)
                        time_difference = 0;

                    // distancia + (penalización por tiempo de espera)
                    float score = distance_to_origin + (0.5f * time_difference);

                    if (score < min_distance)
                    {
                        min_distance = score;
                        best_vehicle = j;
                    }
                }

                else
                {
                    // aca hay que implementar los otros modos de asignacion, pero ppr miestyras dejare esto kbros :P
                    float distance = calculate_distance(vehicles[j].pos_x, vehicles[j].pos_y,
                                                        deliveries[i].origin_x, deliveries[i].origin_y);

                    if (distance < min_distance)
                    {
                        min_distance = distance;
                        best_vehicle = j;
                    }
                }
            }
        }

        // asignar la entrega al mejor vehiulo
        if (best_vehicle != -1)
        {
            int j = best_vehicle;

            // tiempo de espera
            int vehicle_arrival_time = time_to_minutes(vehicles[j].start);
            int delivery_start_time = time_to_minutes(deliveries[i].start);
            float wait_time = (delivery_start_time > vehicle_arrival_time) ? (delivery_start_time - vehicle_arrival_time) : 0;

            // metricas
            completed_deliveries++;
            total_wait_time += wait_time;
            total_distance += min_distance;

            // restas
            vehicles[j].capacity_volume -= deliveries[i].volume;
            vehicles[j].capacity_weight -= deliveries[i].weight;

            // actualizacion la posicion del vehicilo al destino de la entrega
            vehicles[j].pos_x = deliveries[i].destination_x;
            vehicles[j].pos_y = deliveries[i].destination_y;

            printf("Asignando entrega %s al vehículo %s\n", deliveries[i].id, vehicles[j].id);
            printf("Capacidad restante del vehículo %s: Volumen=%.2f, Peso=%.2f\n",
                   vehicles[j].id, vehicles[j].capacity_volume, vehicles[j].capacity_weight);

            assigned = 1;
        }

        if (!assigned)
        {
            printf("No se pudo asignar un vehículo para la entrega %s\n", deliveries[i].id);
        }
    }

    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("\n--- Métricas ---\n");
    printf("Número de entregas completadas: %d/%d\n", completed_deliveries, n_deliveries);
    printf("Distancia total recorrida: %.2f km\n", total_distance);
    printf("Tiempo total de espera: %.2f minutos\n", total_wait_time);
    printf("Tiempo de ejecución del algoritmo: %.6f segundos\n", execution_time);
}

// Calcular la distancia total recorrida por los vehículos
float calculate_total_distance(Vehicle *vehicles, int n_vehicles, Delivery *deliveries, int n_deliveries)
{
    float total_distance = 0.0;

    for (int i = 0; i < n_deliveries; i++)
    {
        for (int j = 0; j < n_vehicles; j++)
        {
            if (vehicles[j].type >= deliveries[i].vehicle_type &&
                vehicles[j].capacity_volume >= deliveries[i].volume &&
                vehicles[j].capacity_weight >= deliveries[i].weight)
            {
                float distance = sqrt(pow(deliveries[i].origin_x - vehicles[j].pos_x, 2) +
                                      pow(deliveries[i].origin_y - vehicles[j].pos_y, 2));
                total_distance += distance;
                break;
            }
        }
    }

    return total_distance;
}

// Calcular la utilización de los vehículos
void calculate_vehicle_utilization(Vehicle *vehicles, int n_vehicles)
{
    for (int j = 0; j < n_vehicles; j++)
    {
        float used_volume = vehicles[j].original_volume - vehicles[j].capacity_volume;
        float used_weight = vehicles[j].original_weight - vehicles[j].capacity_weight;

        // Mensajes de depuración
        printf("Vehículo %s: Volumen original=%.2f, Volumen usado=%.2f\n",
               vehicles[j].id, vehicles[j].original_volume, used_volume);
        printf("Vehículo %s: Peso original=%.2f, Peso usado=%.2f\n",
               vehicles[j].id, vehicles[j].original_weight, used_weight);

        if (vehicles[j].original_volume > 0)
        {
            printf("  Utilización de volumen: %.2f%%\n", (used_volume / vehicles[j].original_volume) * 100);
        }
        else
        {
            printf("  Utilización de volumen: 0.00%%\n");
        }

        if (vehicles[j].original_weight > 0)
        {
            printf("  Utilización de peso: %.2f%%\n", (used_weight / vehicles[j].original_weight) * 100);
        }
        else
        {
            printf("  Utilización de peso: 0.00%%\n");
        }
    }
}