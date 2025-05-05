#include "header.h"

// Función para intercambiar dos entregas
void swap(Delivery *a, Delivery *b)
{
    Delivery temp = *a;
    *a = *b;
    *b = temp;
}

// Funcion de partición para Quick Sort
int partition_time(Delivery *deliveries, int low, int high)
{
    int pivot = time_to_minutes(deliveries[high].end); // Usamos el ultimo elemento como pivote
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (time_to_minutes(deliveries[j].end) <= pivot)
        {
            i++;
            swap(&deliveries[i], &deliveries[j]);
        }
    }
    swap(&deliveries[i + 1], &deliveries[high]);
    return i + 1;
}

// Implementacion personalizada de Quick Sort
void custom_qsort_time(Delivery *deliveries, int low, int high)
{
    if (low < high)
    {
        int pi = partition_time(deliveries, low, high); // Índice de particion
        custom_qsort_time(deliveries, low, pi - 1);     // ordenar elementos antes de la particion
        custom_qsort_time(deliveries, pi + 1, high);    // ordenar elementos despues de la particion
    }
}

int partition_priority(Delivery *deliveries, int low, int high)
{
    int pivot = deliveries[high].priority; // Se usa la prioridad elemento como pivote
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (deliveries[j].priority >= pivot) // Cambiado a mayor o igual para orden descendente
        {
            i++;
            swap(&deliveries[i], &deliveries[j]);
        }
    }
    swap(&deliveries[i + 1], &deliveries[high]);
    return i + 1;
}

void custom_qsort_priority(Delivery *Delivery, int low, int high)
{
    if (low < high)
    {
        int pi = partition_priority(Delivery, low, high); // Índice de particion
        custom_qsort_priority(Delivery, low, pi - 1);     // ordenar elementos antes de la particion
        custom_qsort_priority(Delivery, pi + 1, high);    // ordenar elementos despues de la particion
    }
}