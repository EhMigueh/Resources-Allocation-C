#include "header.h"

// Estrategia: Priority-Based Scheduling
void schedule_based_priority(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    custom_qsort(deliveries, 0, n_deliveries - 1, PRIORITY_BASED);
    fprintf(stdout, "\n--- Estrategia: Priority-Based Scheduling ---\n\n");

    int completed_deliveries = 0;
    float total_wait_time = 0.0;
    float total_distance = 0.0;
    float liters_used = 0.0;
    float total_cost = 0.0;

    clock_t start_time = clock();

    for (int i = 0; i < n_deliveries; i++)
    {
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
                float distance = calculate_distance(vehicles[j].pos_x, vehicles[j].pos_y, deliveries[i].origin_x, deliveries[i].origin_y);

                if (distance < min_distance)
                {
                    min_distance = distance;
                    best_vehicle = j;
                }
            }
        }

        if (best_vehicle != -1)
        {
            int j = best_vehicle;
            float this_delivery_liters = min_distance * calculate_gasoline_by_type(vehicles[j].type);
            liters_used += this_delivery_liters;
            total_cost += this_delivery_liters * PRICE_PER_LITER;

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
            fprintf(stdout, "Capacidad restante del vehículo %s: Volumen=%.2f, Peso=%.2f\n\n", vehicles[j].id, vehicles[j].capacity_volume, vehicles[j].capacity_weight);
        }
        else
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
    fprintf(stdout, "Litros totales usados: %.2f L\n", liters_used);
    fprintf(stdout, "Costo total de bencina: $%.0f CLP\n", total_cost);
}

// Función de comparación para ordenar entregas por prioridad
int compare_by_priority(const void *a, const void *b)
{
    Delivery *delivery_a = (Delivery *)a;
    Delivery *delivery_b = (Delivery *)b;
    return delivery_b->priority - delivery_a->priority;
}