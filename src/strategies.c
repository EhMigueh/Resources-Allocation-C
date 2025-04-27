#include "header.h"

// Estrategia: Earliest Deadline First (EDF)
void schedule_edf(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    qsort(deliveries, n_deliveries, sizeof(Delivery), compare_by_end);
    printf("\n--- Estrategia: Earliest Deadline First (EDF) ---\n");
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles, "EARLIEST_DEADLINE_FIRST");
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
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles, "SHORTEST_PROCESSING_TIME");
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
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles, "PRIORITY_BASED");
}

int compare_by_priority(const void *a, const void *b)
{
    Delivery *delivery_a = (Delivery *)a;
    Delivery *delivery_b = (Delivery *)b;
    return delivery_b->priority - delivery_a->priority;
}

void schedule_nearest_neighbor(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    printf("\n--- Estrategia: Nearest-Neighbor Scheduling ---\n");
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles, "NEAREST_NEIGHBOR");
}
