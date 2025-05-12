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

/*
void calculate_total_distance(Vehicle *vehicles, int n_vehicles, Delivery *deliveries, int n_deliveries)
{
    float total_distance = 0.0;

    for (int i = 0; i < n_deliveries; i++)
        for (int j = 0; j < n_vehicles; j++)
            if (vehicles[j].type >= deliveries[i].vehicle_type && vehicles[j].capacity_volume >= deliveries[i].volume && vehicles[j].capacity_weight >= deliveries[i].weight)
            {
                float distance = sqrt(pow(deliveries[i].origin_x - vehicles[j].pos_x, 2) + pow(deliveries[i].origin_y - vehicles[j].pos_y, 2));
                total_distance += distance;
                break;
            }

    fprintf(stdout, "Distancia total recorrida por los vehículos: %.2f km\n", total_distance);
}
*/

/*
// Calcular la utilización de los vehículos
void calculate_vehicle_utilization(Vehicle *vehicles, int n_vehicles)
{
    fprintf(stdout, "\n\n--- Utilización de los vehículos ---\n\n");

    for (int j = 0; j < n_vehicles; j++)
    {
        float used_volume = vehicles[j].original_volume - vehicles[j].capacity_volume;
        float used_weight = vehicles[j].original_weight - vehicles[j].capacity_weight;

        // Mensajes de depuración
        fprintf(stdout, "Vehículo %s: Volumen original=%.2f, Volumen usado=%.2f\n", vehicles[j].id, vehicles[j].original_volume, used_volume);
        fprintf(stdout, "Vehículo %s: Peso original=%.2f, Peso usado=%.2f\n", vehicles[j].id, vehicles[j].original_weight, used_weight);

        if (vehicles[j].original_volume > 0)
            fprintf(stdout, "  Utilización de volumen: %.2f%%\n", (used_volume / vehicles[j].original_volume) * 100);
        else
            fprintf(stdout, "  Utilización de volumen: 0.00%%\n");

        if (vehicles[j].original_weight > 0)
            fprintf(stdout, "  Utilización de peso: %.2f%%\n\n", (used_weight / vehicles[j].original_weight) * 100);
        else
            fprintf(stdout, "  Utilización de peso: 0.00%%\n\n");
    }
}
*/

// Funcion para exportar csv
void export_to_csv(const char *filename, Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    FILE *file = fopen(filename, "w");
    error_open_file(file, filename);

    fprintf(file, "ID Entrega,ID Vehículo,Litros de Combustible Usados,Distancia Recorrida (KM)\n");

    for (int i = 0; i < n_deliveries; i++)
    {
        if (deliveries[i].vehicle_assigned[0] != '\0')
        {
            for (int j = 0; j < n_vehicles; j++)
            {
                float delivery_distance = calculate_distance(deliveries[i].origin_x, deliveries[i].origin_y, deliveries[i].destination_x, deliveries[i].destination_y);
                float origin_distance = calculate_distance(vehicles[j].pos_x, vehicles[j].pos_y, deliveries[i].origin_x, deliveries[i].origin_y);
                float real_distance = origin_distance + delivery_distance;
                float liters_used = real_distance * calculate_gasoline_by_type(vehicles[j].type);
                fprintf(file, "%s,%s,%.2f,%.2f\n", deliveries[i].id, deliveries[i].vehicle_assigned, liters_used, real_distance);
                break;
            }
        }
        else
            fprintf(file, "%s,N/A,N/A,N/A\n", deliveries[i].id);
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
