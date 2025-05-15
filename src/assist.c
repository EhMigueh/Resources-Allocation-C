#include "../incs/constants.h"
#include "../incs/models.h"
#include "../incs/errors.h"
#include "../incs/utils.h"

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

// Funcion para exportar CSV
void export_to_csv(const char *filename, Delivery *deliveries, int n_deliveries)
{
    FILE *file = fopen(filename, "w");
    error_open_file(file, filename);

    fprintf(file, "ID Entrega,ID Vehiculo,Litros de Combustible Usados,Distancia Recorrida (KM),Inicio del Viaje,Fin del Viaje\n");

    for (int i = 0; i < n_deliveries; i++)
    {
        if (deliveries[i].vehicle_assigned[0] != '\0')
            fprintf(file, "%s,%s,%.2f,%.2f,%s,%s\n", deliveries[i].id, deliveries[i].vehicle_assigned, deliveries[i].liters_used, deliveries[i].distance, deliveries[i].start, deliveries[i].end);
        else
            fprintf(file, "%s,N/A,N/A,N/A,N/A,N/A\n", deliveries[i].id);
    }

    fclose(file);

    fprintf(stdout, GREEN_COLOR "Informe exportado como archivo CSV: %s\n\n" RESET_COLOR, filename);
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

void show_metrics(float total_distance, float liters_used, float total_cost, int completed_deliveries, float total_wait_time, int n_deliveries, double execution_time, int n_vehicles, int used_vehicles, float total_satisfaction)
{
    fprintf(stdout, YELLOW_COLOR "\n--- Metricas Totales de la Simulacion ---\n\n" RESET_COLOR);
    fprintf(stdout, "Numero de entregas completadas: %d/%d entregas\n", completed_deliveries, n_deliveries);
    fprintf(stdout, "Tiempo total de espera: %.2f hrs\n", total_wait_time);
    fprintf(stdout, "Distancia total recorrida: %.2f km\n", total_distance);
    fprintf(stdout, "Satisfacción del cliente: %.2f/5\n", total_satisfaction);
    fprintf(stdout, "Utilización de recursos: %d/%d vehiculos\n", used_vehicles, n_vehicles);
    fprintf(stdout, "Tiempo de ejecucion del algoritmo: %.6f seg\n", execution_time);
    fprintf(stdout, "Litros totales de combustible usados: %.2f L\n", liters_used);
    fprintf(stdout, "Costo total del combustible: $%.0f CLP\n\n", total_cost);
}

int show_vehicles(Vehicle *vehicles, int n_vehicles)
{
    fprintf(stdout, YELLOW_COLOR "--- Vehiculos ---\n\n" RESET_COLOR);
    int count = 0;

    for (int i = 0; i < n_vehicles; i++)
    {
        if (vehicles[i].deliveries_assigned == 0)
        {
            fprintf(stdout, "El vehiculo %s no realizo entregas.\n\n", vehicles[i].id);
            continue;
        }
        fprintf(stdout, "Vehiculo %s: Entregas Asignadas: %d\n", vehicles[i].id, vehicles[i].deliveries_assigned);
        fprintf(stdout, "Capacidad restante del vehiculo %s: Volumen = %.2f m3, Peso = %.2f kg\n\n", vehicles[i].id, vehicles[i].capacity_volume, vehicles[i].capacity_weight);
        count++;
    }

    return count;
}

void show_deliveries(Delivery *deliveries, int n_deliveries)
{
    fprintf(stdout, YELLOW_COLOR "--- Entregas ---\n\n" RESET_COLOR);

    for (int i = 0; i < n_deliveries; i++)
    {
        if (deliveries[i].vehicle_assigned[0] == '\0')
        {
            fprintf(stdout, "La entrega %s no fue asignada a ningun vehiculo.\n\n", deliveries[i].id);
            continue;
        }
        fprintf(stdout, "Entrega %s: Vehiculo Agignado: %s\n", deliveries[i].id, deliveries[i].vehicle_assigned);
        fprintf(stdout, "Requisitos de la Entrega %s: Volumen = %.2f m3, Peso = %.2f kg\n\n", deliveries[i].id, deliveries[i].volume, deliveries[i].weight);
    }
}

float calculate_satisfaction(Delivery *delivery, int n_deliveries, int completed_deliveries)
{
    if (completed_deliveries == 0)
        return 0.0;

    float total_satisfaction = 0.0;

    for (int i = 0; i < n_deliveries; i++)
        if (delivery[i].user_satisfaction > 0)
            total_satisfaction += delivery[i].user_satisfaction;

    return total_satisfaction / completed_deliveries;
}

// Verificación solapamientos de tiempo con entregas previas (Detección de conflictos)
bool has_time_conflict(Delivery *deliveries, int n_deliveries, Delivery *current)
{
    int current_start = time_to_minutes(current->start);
    int current_end = current_start + current->duration;

    for (int i = 0; i < n_deliveries; i++)
    {
        if (strcmp(deliveries[i].vehicle_assigned, "") != 0 &&
            strcmp(deliveries[i].vehicle_assigned, current->vehicle_assigned) == 0)
        {
            int assigned_start = time_to_minutes(deliveries[i].start);
            int assigned_end = assigned_start + deliveries[i].duration;

            if ((current_start < assigned_end && current_end > assigned_start))
                return true; // Hay solapamiento
        }
    }

    return false;
}
