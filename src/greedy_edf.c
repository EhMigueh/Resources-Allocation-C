#include "header.h"

// Estrategia: Earliest Deadline First (EDF)
void schedule_edf(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    custom_qsort_time(deliveries, 0, n_deliveries - 1); // Usar Quick Sort personalizado
    fprintf(stdout, "\n--- Estrategia: Earliest Deadline First (EDF) ---\n\n");
    assign_edf(deliveries, n_deliveries, vehicles, n_vehicles);
}

void assign_edf(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    int completed_deliveries = 0;
    float total_wait_time = 0.0;
    float total_distance = 0.0;

    clock_t start_time = clock();

    for (int i = 0; i < n_deliveries; i++)
    {
        int best_vehicle = -1;
        float min_distance = FLT_MAX;
        float best_real_distance = FLT_MAX;

        for (int j = 0; j < n_vehicles; j++)
        {
            if (vehicles[j].type >= deliveries[i].vehicle_type &&
                vehicles[j].capacity_volume >= deliveries[i].volume &&
                vehicles[j].capacity_weight >= deliveries[i].weight &&
                time_to_minutes(vehicles[j].start) <= time_to_minutes(deliveries[i].start) + FLEXIBILITY_MINUTES &&
                time_to_minutes(vehicles[j].end) >= time_to_minutes(deliveries[i].end))
            {
                int delivery_deadline = time_to_minutes(deliveries[i].end);
                float distance_to_origin = calculate_distance(vehicles[j].pos_x, vehicles[j].pos_y, deliveries[i].origin_x, deliveries[i].origin_y);
                float delivery_distance = calculate_distance(deliveries[i].origin_x, deliveries[i].origin_y, deliveries[i].destination_x, deliveries[i].destination_y);
                float real_distance = distance_to_origin + delivery_distance;

                float urgency_score = delivery_deadline + distance_to_origin;

                if (urgency_score < min_distance)
                {
                    min_distance = urgency_score;
                    best_vehicle = j;
                    best_real_distance = real_distance;
                }
            }
        }

        if (best_vehicle != -1)
        {
            int j = best_vehicle;

            int vehicle_arrival_time = time_to_minutes(vehicles[j].start);
            int delivery_start_time = time_to_minutes(deliveries[i].start);
            float wait_time = (delivery_start_time > vehicle_arrival_time) ? (delivery_start_time - vehicle_arrival_time) : 0;

            completed_deliveries++;
            total_wait_time += wait_time;
            total_distance += best_real_distance;

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
}

int compare_deadlines(const void *a, const void *b)
{
    Delivery *d1 = (Delivery *)a;
    Delivery *d2 = (Delivery *)b;

    int t1 = time_to_minutes(d1->end);
    int t2 = time_to_minutes(d2->end);

    return t1 - t2; // orden ascendente
}