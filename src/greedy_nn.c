#include "constants.h"
#include "models.h"
#include "utils.h"
#include "functions.h"

void schedule_nn(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    fprintf(stdout, CYAN_COLOR "\n--- Estrategia: Nearest-Neighbor Scheduling ---\n\n" RESET_COLOR);

    int completed_deliveries = 0;
    float total_wait_time = 0.0f;
    float total_distance = 0.0f;
    float liters_used = 0.0;
    float total_cost = 0.0;

    clock_t start_time = clock();

    for (int i = 0; i < n_deliveries; i++)
    {
        int best_vehicle = -1;
        float min_score = FLT_MAX;
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
                int vehicle_available_time = time_to_minutes(vehicles[j].start);
                int delivery_start_time = time_to_minutes(deliveries[i].start);
                float time_difference = (delivery_start_time - vehicle_available_time > 0) ? (delivery_start_time - vehicle_available_time) : 0;

                float volume_util = 1.0f - (vehicles[j].capacity_volume / vehicles[j].original_volume);
                float weight_util = 1.0f - (vehicles[j].capacity_weight / vehicles[j].original_weight);
                float utilization_score = (volume_util + weight_util) / 2.0f;

                float score = distance_to_origin + (0.5f * time_difference) + (5.0f * vehicles[j].deliveries_assigned) + (10.0f * utilization_score);

                if (score < min_score)
                {
                    min_score = score;
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

            int satisfaction = 1;
            int optimal_wait[] = {20, 30, 40, 50, 60};
            int max_wait[] = {60, 90, 120, 150, 180};
            int priority_index = deliveries[i].priority - 1;
            int wait = (int)wait_time;

            if (wait <= optimal_wait[priority_index])
                satisfaction = 5;
            else if (wait <= optimal_wait[priority_index] + (max_wait[priority_index] - optimal_wait[priority_index]) / 3)
                satisfaction = 4;
            else if (wait <= optimal_wait[priority_index] + 2 * (max_wait[priority_index] - optimal_wait[priority_index]) / 3)
                satisfaction = 3;
            else if (wait <= max_wait[priority_index])
                satisfaction = 2;
            else
                satisfaction = 1;

            deliveries[i].user_satisfaction = satisfaction;
        }
        else
            continue;
    }

    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    int used_vehicles = show_vehicles(vehicles, n_vehicles);

    show_deliveries(deliveries, n_deliveries);

    float total_satisfaction = calculate_satisfaction(deliveries, n_deliveries, completed_deliveries);

    show_metrics(total_distance, liters_used, total_cost, completed_deliveries, total_wait_time / 60, n_deliveries, execution_time, n_vehicles, used_vehicles, total_satisfaction);

    export_to_csv("./output/informe_entregas_nn.csv", deliveries, n_deliveries);
}