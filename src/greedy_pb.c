#include "header.h"

// Estrategia: Priority-Based Scheduling
void schedule_based_priority(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    custom_qsort(deliveries, 0, n_deliveries - 1, PRIORITY_BASED);
    fprintf(stdout, "\n--- Estrategia: Priority-Based Scheduling ---\n\n");
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles, PRIORITY_BASED);
}

// Función de comparación para ordenar entregas por prioridad
int compare_by_priority(const void *a, const void *b)
{
    Delivery *delivery_a = (Delivery *)a;
    Delivery *delivery_b = (Delivery *)b;
    return delivery_b->priority - delivery_a->priority;
}