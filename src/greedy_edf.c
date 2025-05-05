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

// burbuja
/*
// Estrategia: Earliest Deadline First (EDF)
void schedule_edf(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    sort_by_end(deliveries, n_deliveries); // Usar la función personalizada
    fprintf(stdout, "\n--- Estrategia: Earliest Deadline First (EDF) ---\n\n");
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles, EARLIEST_DEADLINE_FIRST);
}

void sort_by_end(Delivery *deliveries, int n_deliveries)
{
    for (int i = 0; i < n_deliveries - 1; i++)
    {
        for (int j = 0; j < n_deliveries - i - 1; j++)
        {
            if (time_to_minutes(deliveries[j].end) > time_to_minutes(deliveries[j + 1].end))
            {
                Delivery temp = deliveries[j];
                deliveries[j] = deliveries[j + 1];
                deliveries[j + 1] = temp;
            }
        }
    }
}
*/