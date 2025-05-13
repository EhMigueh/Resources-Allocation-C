#include "header.h"

// Calcular la distancia entre dos puntos (x1, y1) y (x2, y2)
float calculate_distance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Función para convertir una hora en formato HH:MM a minutos totales
int time_to_minutes(const char *time_str)
{
    int hours, minutes;
    sscanf(time_str, "%d:%d", &hours, &minutes);
    return hours * 60 + minutes;
}

// Funcion para exportar csv
void export_to_csv(const char *filename, Delivery *deliveries, int n_deliveries)
{
    FILE *file = fopen(filename, "w");
    error_open_file(file, filename);

    fprintf(file, "ID Entrega,ID Vehículo,Litros de Combustible Usados,Distancia Recorrida (KM)\n");

    for (int i = 0; i < n_deliveries; i++)
    {
        if (deliveries[i].vehicle_assigned[0] != '\0')
        {
            fprintf(file, "%s,%s,%.2f,%.2f\n",
                    deliveries[i].id,
                    deliveries[i].vehicle_assigned,
                    deliveries[i].liters_used,
                    deliveries[i].distance);
        }
        else
        {
            fprintf(file, "%s,N/A,N/A,N/A\n", deliveries[i].id);
        }
    }

    fclose(file);
    printf("Informe exportado como archivo CSV: %s\n\n", filename);
}

float calculate_gasoline_by_type(int type)
{
    switch (type)
    {
    case 1:
        return 0.12;
    case 2:
        return 0.15;
    case 3:
        return 0.18;
    default:
        return 0.14;
    }
}

void show_metrics(float total_distance, float liters_used, float total_cost, int completed_deliveries, float total_wait_time, int n_deliveries, double execution_time)
{
    fprintf(stdout, "\n--- Métricas de la Simulación ---\n\n");
    fprintf(stdout, "Numero de entregas completadas: %d/%d\n", completed_deliveries, n_deliveries);
    fprintf(stdout, "Distancia total recorrida: %.2f km\n", total_distance);
    fprintf(stdout, "Tiempo total de espera: %.2f hrs\n", total_wait_time);
    fprintf(stdout, "Tiempo de ejecucion del algoritmo: %.6f seg\n", execution_time);
    fprintf(stdout, "Litros totales de combustible usados: %.2f L\n", liters_used);
    fprintf(stdout, "Costo total del combustible: $%.0f CLP\n\n", total_cost);
}
