#include "header.h"

//burbuja
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

//qsort

// Función para intercambiar dos entregas
void swap(Delivery *a, Delivery *b) 
{
    Delivery temp = *a;
    *a = *b;
    *b = temp;
}

// Funcion de partición para Quick Sort
int partition(Delivery *deliveries, int low, int high) 
{
    int pivot = time_to_minutes(deliveries[high].end); // Usamos el ultimo elemento como pivote
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (time_to_minutes(deliveries[j].end) <= pivot) 
        {
            i++;
            swap(&deliveries[i], &deliveries[j]);
        }
    }
    swap(&deliveries[i + 1], &deliveries[high]);
    return i + 1;
}

// implementacion personalizada de Quick Sort
void custom_qsort(Delivery *deliveries, int low, int high) 
{
    if (low < high) 
    {
        int pi = partition(deliveries, low, high); // indice de particion
        custom_qsort(deliveries, low, pi - 1);     // ordenar elementos antes de la particion
        custom_qsort(deliveries, pi + 1, high);   // ordenar elementos despues de la particion
    }
}

// Estrategia: Earliest Deadline First (EDF)
void schedule_edf(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles) 
{
    custom_qsort(deliveries, 0, n_deliveries - 1); // Usar Quick Sort personalizado
    fprintf(stdout, "\n--- Estrategia: Earliest Deadline First (EDF) ---\n\n");
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles, EARLIEST_DEADLINE_FIRST);
}




// Estrategia: Shortest Processing Time (SPT)
void schedule_spt(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    qsort(deliveries, n_deliveries, sizeof(Delivery), compare_by_duration);
    fprintf(stdout, "\n--- Estrategia: Shortest Processing Time (SPT) ---\n\n");
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles, SHORTEST_PROCESSING_TIME);
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
    fprintf(stdout, "\n--- Estrategia: Priority-Based Scheduling ---\n\n");
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles, PRIORITY_BASED);
}

int compare_by_priority(const void *a, const void *b)
{
    Delivery *delivery_a = (Delivery *)a;
    Delivery *delivery_b = (Delivery *)b;
    return delivery_b->priority - delivery_a->priority;
}

// Estrategia: Nearest Neighbor
void schedule_nearest_neighbor(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    fprintf(stdout, "\n--- Estrategia: Nearest-Neighbor Scheduling ---\n\n");
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles, NEAREST_NEIGHBOR);
}
