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
            error_vehicle_capacity();
        if (vehicles[i].type < 1 || vehicles[i].type > 3)
            error_vehicle_type();
    }
}

void assign_vehicles_to_deliveries(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles, SchedulingMode mode)
{
    int completed_deliveries = 0;
    float total_wait_time = 0.0;
    float total_distance = 0.0;

    clock_t start_time = clock();

    // si el modo es EARLIEST_DEADLINE_FIRST se debe ordenar para que las fechas limite mas cercana queden primero
    if (mode == EARLIEST_DEADLINE_FIRST)
    {
        qsort(deliveries, n_deliveries, sizeof(Delivery), compare_deadlines);
    }

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
                switch (mode)
                {
                case NEAREST_NEIGHBOR:
                {
                    float distance_to_origin = calculate_distance(vehicles[j].pos_x, vehicles[j].pos_y,
                                                                  deliveries[i].origin_x, deliveries[i].origin_y);
                    int vehicle_available_time = time_to_minutes(vehicles[j].start);
                    int delivery_start_time = time_to_minutes(deliveries[i].start);
                    float time_difference = delivery_start_time - vehicle_available_time;

                    float volume_util = 1.0f - (vehicles[j].capacity_volume / vehicles[j].original_volume); // mide cuan lleno esta el vehiculo con respecto al volumen total
                    float weight_util = 1.0f - (vehicles[j].capacity_weight / vehicles[j].original_weight); // midel cuan lleno esta el vehiclo con respecto al pso maximo
                    float utilization_score = (volume_util + weight_util) / 2.0f;                           // promedio de volumen y peso utilizado, si utilization_score es bajo, queda poca capacidad

                    float score = distance_to_origin + (0.5f * time_difference) + (5.0f * vehicles[j].deliveries_assigned) + (10.0f * utilization_score); // intento de mejor asignacion

                    if (time_difference < 0)
                        time_difference = 0;

                    // float score = distance_to_origin + (0.5f * time_difference) + (5.0f * vehicles[j].deliveries_assigned);
                    if (score < min_distance)
                    {
                        min_distance = score;
                        best_vehicle = j;
                    }
                    break;
                }

                case EARLIEST_DEADLINE_FIRST:
                {
                    int delivery_deadline = time_to_minutes(deliveries[i].end);
                    // int vehicle_available_time = time_to_minutes(vehicles[j].start);
                    float distance_to_origin = calculate_distance(vehicles[j].pos_x, vehicles[j].pos_y,
                                                                  deliveries[i].origin_x, deliveries[i].origin_y);

                    float urgency_score = delivery_deadline + distance_to_origin;

                    if (urgency_score < min_distance)
                    {
                        min_distance = urgency_score;
                        best_vehicle = j;
                    }
                    break;
                }

                default:
                {
                    float distance = calculate_distance(vehicles[j].pos_x, vehicles[j].pos_y,
                                                        deliveries[i].origin_x, deliveries[i].origin_y);

                    if (distance < min_distance)
                    {
                        min_distance = distance;
                        best_vehicle = j;
                    }
                    break;
                }
                }
            }
        }

        // asignar la entrega al mejor vehículo
        if (best_vehicle != -1)
        {
            int j = best_vehicle;

            int vehicle_arrival_time = time_to_minutes(vehicles[j].start);
            int delivery_start_time = time_to_minutes(deliveries[i].start);
            float wait_time = (delivery_start_time > vehicle_arrival_time) ? (delivery_start_time - vehicle_arrival_time) : 0;

            completed_deliveries++;
            total_wait_time += wait_time;
            total_distance += min_distance;

            vehicles[j].deliveries_assigned++;
            vehicles[j].capacity_volume -= deliveries[i].volume;
            vehicles[j].capacity_weight -= deliveries[i].weight;

            vehicles[j].pos_x = deliveries[i].destination_x;
            vehicles[j].pos_y = deliveries[i].destination_y;

            fprintf(stdout, "Asignando entrega %s al vehículo %s\n", deliveries[i].id, vehicles[j].id);
            fprintf(stdout, "Capacidad restante del vehículo %s: Volumen=%.2f, Peso=%.2f\n\n",
                    vehicles[j].id, vehicles[j].capacity_volume, vehicles[j].capacity_weight);

            assigned = 1;
        }

        if (!assigned)
        {
            for (int j = 0; j < n_vehicles; j++)
            {
                if (vehicles[j].type >= deliveries[i].vehicle_type &&
                    vehicles[j].capacity_volume >= deliveries[i].volume &&
                    vehicles[j].capacity_weight >= deliveries[i].weight &&
                    time_to_minutes(vehicles[j].start) <= time_to_minutes(deliveries[i].start) + FLEXIBILITY_MINUTES &&
                    time_to_minutes(vehicles[j].end) >= time_to_minutes(deliveries[i].end))
                {
                    vehicles[j].deliveries_assigned++;
                    vehicles[j].capacity_volume -= deliveries[i].volume;
                    vehicles[j].capacity_weight -= deliveries[i].weight;

                    vehicles[j].pos_x = deliveries[i].destination_x;
                    vehicles[j].pos_y = deliveries[i].destination_y;

                    fprintf(stdout, "⚠️  Asignación forzada de entrega %s al vehículo %s\n", deliveries[i].id, vehicles[j].id);
                    fprintf(stdout, "Capacidad restante del vehículo %s: Volumen=%.2f, Peso=%.2f\n\n",
                            vehicles[j].id, vehicles[j].capacity_volume, vehicles[j].capacity_weight);
                    break;
                }
            }
        }

        if (!assigned)
        {
            fprintf(stdout, "No se pudo asignar un vehículo para la entrega %s\n\n", deliveries[i].id);
        }
    }

    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    fprintf(stdout, "\n--- Métricas ---\n\n");
    fprintf(stdout, "Número de entregas completadas: %d/%d\n", completed_deliveries, n_deliveries);
    fprintf(stdout, "Distancia total recorrida: %.2f km\n", total_distance);
    fprintf(stdout, "Tiempo total de espera: %.2f minutos\n", total_wait_time);
    fprintf(stdout, "Tiempo de ejecución del algoritmo: %.6f segundos\n", execution_time);
}

// Calcular la distancia total recorrida por los vehículos
void calculate_total_distance(Vehicle *vehicles, int n_vehicles, Delivery *deliveries, int n_deliveries)
{
    float total_distance = 0.0;

    for (int i = 0; i < n_deliveries; i++)
        for (int j = 0; j < n_vehicles; j++)
            if (vehicles[j].type >= deliveries[i].vehicle_type && vehicles[j].capacity_volume >= deliveries[i].volume && vehicles[j].capacity_weight >= deliveries[i].weight)
            {
                float distance = sqrt(pow(deliveries[i].origin_x - vehicles[j].pos_x, 2) + pow(deliveries[i].origin_y - vehicles[j].pos_y, 2));
                total_distance += distance;
                break;
            }

    fprintf(stdout, "Distancia total recorrida por los vehículos: %.2f km\n", total_distance);
}

// Calcular la utilización de los vehículos
void calculate_vehicle_utilization(Vehicle *vehicles, int n_vehicles)
{
    fprintf(stdout, "\n\n--- Utilización de los vehículos ---\n\n");

    for (int j = 0; j < n_vehicles; j++)
    {
        float used_volume = vehicles[j].original_volume - vehicles[j].capacity_volume;
        float used_weight = vehicles[j].original_weight - vehicles[j].capacity_weight;

        // Mensajes de depuración
        fprintf(stdout, "Vehículo %s: Volumen original=%.2f, Volumen usado=%.2f\n", vehicles[j].id, vehicles[j].original_volume, used_volume);
        fprintf(stdout, "Vehículo %s: Peso original=%.2f, Peso usado=%.2f\n", vehicles[j].id, vehicles[j].original_weight, used_weight);

        if (vehicles[j].original_volume > 0)
            fprintf(stdout, "  Utilización de volumen: %.2f%%\n", (used_volume / vehicles[j].original_volume) * 100);
        else
            fprintf(stdout, "  Utilización de volumen: 0.00%%\n");

        if (vehicles[j].original_weight > 0)
            fprintf(stdout, "  Utilización de peso: %.2f%%\n\n", (used_weight / vehicles[j].original_weight) * 100);
        else
            fprintf(stdout, "  Utilización de peso: 0.00%%\n\n");
    }
}

int compare_deadlines(const void *a, const void *b)
{
    Delivery *d1 = (Delivery *)a;
    Delivery *d2 = (Delivery *)b;

    int t1 = time_to_minutes(d1->end);
    int t2 = time_to_minutes(d2->end);

    return t1 - t2; // orden ascendente
}
