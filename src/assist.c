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

// Funcion para exportar csv
void exportar_informe_csv(const char *nombre_archivo, Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    FILE *file = fopen(nombre_archivo, "w");
    if (!file)
    {
        fprintf(stderr, "Error al crear el archivo %s\n", nombre_archivo);
        return;
    }

    fprintf(file, "ID Entrega,ID Vehículo,Volumen,Peso,Distancia Real (km),Tiempo de Espera (min),Entregas Asignadas,Capacidad Volumen Restante,Capacidad Peso Restante\n");

    for (int i = 0; i < n_deliveries; i++)
    {
        int best_vehicle = -1;
        for (int j = 0; j < n_vehicles; j++)
        {
            if (vehicles[j].pos_x == deliveries[i].destination_x &&
                vehicles[j].pos_y == deliveries[i].destination_y)
            {
                best_vehicle = j;
                break;
            }
        }

        if (best_vehicle != -1)
        {
            float distancia_origen = calculate_distance(
                vehicles[best_vehicle].pos_x, vehicles[best_vehicle].pos_y,
                deliveries[i].origin_x, deliveries[i].origin_y);
            float distancia_entrega = calculate_distance(
                deliveries[i].origin_x, deliveries[i].origin_y,
                deliveries[i].destination_x, deliveries[i].destination_y);
            float distancia_real = distancia_origen + distancia_entrega;

            int tiempo_vehiculo = time_to_minutes(vehicles[best_vehicle].start);
            int tiempo_inicio = time_to_minutes(deliveries[i].start);
            float tiempo_espera = (tiempo_inicio > tiempo_vehiculo) ? tiempo_inicio - tiempo_vehiculo : 0;

            fprintf(file, "%s,%s,%.2f,%.2f,%.2f,%.2f,%d,%.2f,%.2f\n",
                    deliveries[i].id,
                    vehicles[best_vehicle].id,
                    deliveries[i].volume,
                    deliveries[i].weight,
                    distancia_real,
                    tiempo_espera,
                    vehicles[best_vehicle].deliveries_assigned,
                    vehicles[best_vehicle].capacity_volume,
                    vehicles[best_vehicle].capacity_weight);
        }
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char fecha[20];
    strftime(fecha, sizeof(fecha), "%Y-%m-%d", &tm);

    fprintf(file, "INFORME DE OPERACIONES LOGÍSTICAS\n");
    fprintf(file, "----------------------------------\n");
    fprintf(file, "Empresa: Entregas Don Pepito\n");
    fprintf(file, "RUT: 11.111.111-7\n");
    fprintf(file, "Fecha del informe: %s\n", fecha);
    fprintf(file, "\n");
    fprintf(file, "----------------------------------\n");

    fclose(file);
    printf("Informe exportado como archivo CSV: %s\n", nombre_archivo);
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
