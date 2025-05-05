#include "header.h"

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

// implementacion personalizada de Quick Sort
void custom_qsort(Delivery *deliveries, int low, int high)
{
    if (low < high)
    {
        int pi = partition(deliveries, low, high); // indice de particion
        custom_qsort(deliveries, low, pi - 1);     // ordenar elementos antes de la particion
        custom_qsort(deliveries, pi + 1, high);    // ordenar elementos despues de la particion
    }
}
