#include "header.h"

// Estrategia: Earliest Deadline First (EDF)
void schedule_edf(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    qsort(deliveries, n_deliveries, sizeof(Delivery), compare_by_end);
    printf("\n--- Estrategia: Earliest Deadline First (EDF) ---\n");
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles);
}

int compare_by_end(const void *a, const void *b)
{
    Delivery *delivery_a = (Delivery *)a;
    Delivery *delivery_b = (Delivery *)b;
    return strcmp(delivery_a->end, delivery_b->end);
}

// Estrategia: Shortest Processing Time (SPT)
void schedule_spt(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    qsort(deliveries, n_deliveries, sizeof(Delivery), compare_by_duration);
    printf("\n--- Estrategia: Shortest Processing Time (SPT) ---\n");
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles);
}

int compare_by_duration(const void *a, const void *b)
{
    Delivery *delivery_a = (Delivery *)a;
    Delivery *delivery_b = (Delivery *)b;
    return delivery_a->duration - delivery_b->duration;
}

// Estrategia: Priority-Based Scheduling
void schedule_priority(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    qsort(deliveries, n_deliveries, sizeof(Delivery), compare_by_priority);
    printf("\n--- Estrategia: Priority-Based Scheduling ---\n");
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles);
}

int compare_by_priority(const void *a, const void *b)
{
    Delivery *delivery_a = (Delivery *)a;
    Delivery *delivery_b = (Delivery *)b;
    return delivery_b->priority - delivery_a->priority;
}

void schedule_nearest_neighbor(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    for (int i = 0; i < n_deliveries; i++)
    {
        int best_vehicle = -1;
        float min_distance = FLT_MAX;

        // mira el vehiculo mas cerca
        for (int j = 0; j < n_vehicles; j++)
        {
            // solo los que tengan capacidad suficiente
            if (vehicles[j].capacity_volume >= deliveries[i].volume &&
                vehicles[j].capacity_weight >= deliveries[i].weight)
            {

                // calcula la distancia desde la ubicacion del vehiculo al origen de la entrega
                float distance = calculate_distance(vehicles[j].pos_x, vehicles[j].pos_y,
                                                    deliveries[i].origin_x, deliveries[i].origin_y);

                // actualiza el auto mas cercano
                if (distance < min_distance)
                {
                    min_distance = distance;
                    best_vehicle = j;
                }
            }
        }

        // asgina la entrega al vehiculo mas cercano
        if (best_vehicle != -1)
        {
            // actauliza la capacidad del vehiculo
            vehicles[best_vehicle].capacity_volume -= deliveries[i].volume;
            vehicles[best_vehicle].capacity_weight -= deliveries[i].weight;

            // actualiza la ubicacion del vehiculo a la ubicacion de la entrega
            vehicles[best_vehicle].pos_x = deliveries[i].destination_x;
            vehicles[best_vehicle].pos_y = deliveries[i].destination_y;

            printf("Entrega %s asignada al vehículo %s\n", deliveries[i].id, vehicles[best_vehicle].id);
        }
        else
        {
            printf("No se pudo asignar vehículo para la entrega %s\n", deliveries[i].id);
        }
    }
}