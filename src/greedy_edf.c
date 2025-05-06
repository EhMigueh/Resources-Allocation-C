#include "header.h"

// Estrategia: Earliest Deadline First (EDF)
void schedule_edf(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    custom_qsort_time(deliveries, 0, n_deliveries - 1); // Usar Quick Sort personalizado
    fprintf(stdout, "\n--- Estrategia: Earliest Deadline First (EDF) ---\n\n");
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles, EARLIEST_DEADLINE_FIRST);
}

int compare_deadlines(const void *a, const void *b)
{
    Delivery *d1 = (Delivery *)a;
    Delivery *d2 = (Delivery *)b;

    int t1 = time_to_minutes(d1->end);
    int t2 = time_to_minutes(d2->end);

    return t1 - t2; // orden ascendente
}
