#include "header.h"

// Función para intercambiar dos entregas
void swap(Delivery *a, Delivery *b)
{
    Delivery temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Delivery *deliveries, int low, int high, SchedulingMode mode)
{
    int pivot;
    int i = low - 1;

    if (mode == EARLIEST_DEADLINE_FIRST)
        pivot = time_to_minutes(deliveries[high].end); // Usamos el ultimo elemento como pivote
    else
        pivot = deliveries[high].priority; // Se usa la prioridad elemento como pivote

    for (int j = low; j < high; j++)
    {
        if (mode == EARLIEST_DEADLINE_FIRST)
        {
            if (time_to_minutes(deliveries[j].end) <= pivot)
            {
                i++;
                swap(&deliveries[i], &deliveries[j]);
            }
        }
        else
        {
            if (deliveries[j].priority >= pivot) // Cambiado a mayor o igual para orden descendente
            {
                i++;
                swap(&deliveries[i], &deliveries[j]);
            }
        }
    }
    swap(&deliveries[i + 1], &deliveries[high]);
    return i + 1;
}

void custom_qsort(Delivery *deliveries, int low, int high, SchedulingMode mode)
{
    if (low < high)
    {
        int pi = partition(deliveries, low, high, mode); // Índice de particion
        custom_qsort(deliveries, low, pi - 1, mode);     // ordenar elementos antes de la particion
        custom_qsort(deliveries, pi + 1, high, mode);    // ordenar elementos despues de la particion
    }
}