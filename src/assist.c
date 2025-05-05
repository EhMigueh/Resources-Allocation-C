#include "header.h"

// Menú principal para seleccionar la estrategia de scheduling (TEMPORAL)
void menu_scheduling()
{
    fprintf(stdout, "\nSeleccione la estrategia de scheduling:\n\n");
    fprintf(stdout, "1. Earliest Deadline First (EDF)\n");
    fprintf(stdout, "2. Priority-Based Scheduling\n");
    fprintf(stdout, "3. Nearest Neighbor\n");
    fprintf(stdout, "\nIngrese su elección: ");
}

// Función para eliminar el salto de línea al final de una cadena, si existe
void delete_line_leap(char *line)
{
    char *newline = strchr(line, '\n');
    if (newline)
        *newline = '\0'; // Reemplaza el salto de línea con un terminador nulo
}

// Validar los datos de los vehículos, esto siempre debería estar bien
void validate_vehicle_data(Vehicle *vehicles, int n_vehicles)
{
    for (int i = 0; i < n_vehicles; i++)
    {
        if (vehicles[i].capacity_volume <= 0 || vehicles[i].capacity_weight <= 0)
            error_vehicle_capacity();
        if (vehicles[i].type < 1 || vehicles[i].type > 3)
            error_vehicle_type();
    }
}

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

// Calcular la distancia total recorrida por los vehículos
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