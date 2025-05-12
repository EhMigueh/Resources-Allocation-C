#include "header.h"

// Estrategia: Priority-Based Scheduling
void schedule_pb(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
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
        float best_real_distance = FLT_MAX;

        for (int j = 0; j < n_vehicles; j++)
        {
            if (vehicles[j].type >= deliveries[i].vehicle_type &&
                vehicles[j].capacity_volume >= deliveries[i].volume &&
                vehicles[j].capacity_weight >= deliveries[i].weight &&
                time_to_minutes(vehicles[j].start) <= time_to_minutes(deliveries[i].start) + FLEXIBILITY_MINUTES &&
                time_to_minutes(vehicles[j].end) >= time_to_minutes(deliveries[i].end))
            {
                float distance_to_origin = calculate_distance(vehicles[j].pos_x, vehicles[j].pos_y, deliveries[i].origin_x, deliveries[i].origin_y);
                float delivery_distance = calculate_distance(deliveries[i].origin_x, deliveries[i].origin_y, deliveries[i].destination_x, deliveries[i].destination_y);
                float real_distance = distance_to_origin + delivery_distance;

                if (real_distance < min_distance)
                {
                    min_distance = real_distance;
                    best_vehicle = j;
                    best_real_distance = real_distance;
                }
            }
        }

        if (best_vehicle != -1)
        {
            int j = best_vehicle;
            float this_delivery_liters = best_real_distance * calculate_gasoline_by_type(vehicles[j].type);
            liters_used += this_delivery_liters;
            total_cost += this_delivery_liters * PRICE_PER_LITER;

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
            deliveries[i].distance = best_real_distance;
            deliveries[i].liters_used = this_delivery_liters;
            strcpy(deliveries[i].vehicle_assigned, vehicles[j].id);

            fprintf(stdout, "ID Entrega: %s - ID Vehiculo: %s - Litros usados: %.2f - Distancia recorrida: %.2f\n", deliveries[i].id, vehicles[j].id, this_delivery_liters, best_real_distance); // temporal
        }
        else
            continue;
    }

    fprintf(stdout, "\nCOMPARAR CON LOS INFORMES...\n\n"); // temporal

    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    for (int i = 0; i < n_vehicles; i++)
    {
        if (vehicles[i].deliveries_assigned == 0)
        {
            fprintf(stdout, "El vehículo %s no realizó entregas.\n\n", vehicles[i].id);
            continue;
        }
        fprintf(stdout, "Vehículo %s: Entregas Asignadas: %d\n", vehicles[i].id, vehicles[i].deliveries_assigned);
        fprintf(stdout, "Capacidad restante del vehículo %s: Volumen=%.2f, Peso=%.2f\n\n", vehicles[i].id, vehicles[i].capacity_volume, vehicles[i].capacity_weight);
    }

    for (int i = 0; i < n_deliveries; i++)
        if (deliveries[i].vehicle_assigned[0] == '\0')
            fprintf(stdout, "La entrega %s no fue asignada a ningún vehículo.\n", deliveries[i].id);

    show_metrics(total_distance, liters_used, total_cost, completed_deliveries, total_wait_time / 60, n_deliveries, execution_time);

    export_to_csv("./output/informe_entregas_pb.csv", deliveries, n_deliveries, n_vehicles);
}
