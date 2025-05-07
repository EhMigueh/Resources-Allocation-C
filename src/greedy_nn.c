#include "header.h"

void schedule_nearest_neighbor(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    fprintf(stdout, "\n--- Estrategia: Nearest-Neighbor Scheduling ---\n\n");
    assign_nearest_neighbor(deliveries, n_deliveries, vehicles, n_vehicles);
}

void assign_nearest_neighbor(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    int completed_deliveries = 0;
    float total_wait_time = 0.0f;
    float total_distance = 0.0f;

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
                float distance_to_origin = calculate_distance(
                    vehicles[j].pos_x, vehicles[j].pos_y,
                    deliveries[i].origin_x, deliveries[i].origin_y);

                float delivery_distance = calculate_distance(
                    deliveries[i].origin_x, deliveries[i].origin_y,
                    deliveries[i].destination_x, deliveries[i].destination_y);

                float real_distance = distance_to_origin + delivery_distance;

                int vehicle_available_time = time_to_minutes(vehicles[j].start);
                int delivery_start_time = time_to_minutes(deliveries[i].start);
                float time_difference = (delivery_start_time - vehicle_available_time > 0) ? (delivery_start_time - vehicle_available_time) : 0;

                float volume_util = 1.0f - (vehicles[j].capacity_volume / vehicles[j].original_volume);
                float weight_util = 1.0f - (vehicles[j].capacity_weight / vehicles[j].original_weight);
                float utilization_score = (volume_util + weight_util) / 2.0f;

                float score = distance_to_origin +
                              (0.5f * time_difference) +
                              (5.0f * vehicles[j].deliveries_assigned) +
                              (10.0f * utilization_score);

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
            fprintf(stdout, "Capacidad restante del vehículo %s: Volumen=%.2f, Peso=%.2f\n\n",
                    vehicles[j].id, vehicles[j].capacity_volume, vehicles[j].capacity_weight);
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

    exportar_informe_csv("Informe_diario_de_entregas.csv", deliveries, n_deliveries, vehicles, n_vehicles);
}

void exportar_informe_csv(const char *nombre_archivo, Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    FILE *file = fopen(nombre_archivo, "w");
    if (!file)
    {
        fprintf(stderr, "Error al crear el archivo %s\n", nombre_archivo);
        return;
    }

    fprintf(file, "ID Entrega,ID Vehículo,Volumen,Peso,Distancia Real (km),Tiempo de Espera (min),Entregas Asignadas,Capacidad Volumen Restante,Capacidad Peso Restante\n");

    for (int i = 0; i < n_deliveries; i++)
    {
        int best_vehicle = -1;
        for (int j = 0; j < n_vehicles; j++)
        {
            if (vehicles[j].pos_x == deliveries[i].destination_x &&
                vehicles[j].pos_y == deliveries[i].destination_y)
            {
                best_vehicle = j;
                break;
            }
        }

        if (best_vehicle != -1)
        {
            float distancia_origen = calculate_distance(
                vehicles[best_vehicle].pos_x, vehicles[best_vehicle].pos_y,
                deliveries[i].origin_x, deliveries[i].origin_y);
            float distancia_entrega = calculate_distance(
                deliveries[i].origin_x, deliveries[i].origin_y,
                deliveries[i].destination_x, deliveries[i].destination_y);
            float distancia_real = distancia_origen + distancia_entrega;

            int tiempo_vehiculo = time_to_minutes(vehicles[best_vehicle].start);
            int tiempo_inicio = time_to_minutes(deliveries[i].start);
            float tiempo_espera = (tiempo_inicio > tiempo_vehiculo) ? tiempo_inicio - tiempo_vehiculo : 0;

            fprintf(file, "%s,%s,%.2f,%.2f,%.2f,%.2f,%d,%.2f,%.2f\n",
                    deliveries[i].id,
                    vehicles[best_vehicle].id,
                    deliveries[i].volume,
                    deliveries[i].weight,
                    distancia_real,
                    tiempo_espera,
                    vehicles[best_vehicle].deliveries_assigned,
                    vehicles[best_vehicle].capacity_volume,
                    vehicles[best_vehicle].capacity_weight);
        }
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char fecha[20];
    strftime(fecha, sizeof(fecha), "%Y-%m-%d", &tm);

    fprintf(file, "INFORME DE OPERACIONES LOGÍSTICAS\n");
    fprintf(file, "----------------------------------\n");
    fprintf(file, "Empresa: Entregas Don Pepito\n");
    fprintf(file, "RUT: 11.111.111-7\n");
    fprintf(file, "Fecha del informe: %s\n", fecha);
    fprintf(file, "\n");
    fprintf(file, "----------------------------------\n");

    fclose(file);
    printf("Informe exportado como archivo CSV: %s\n", nombre_archivo);
}
