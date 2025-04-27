#include "header.h"

int main(void)
{
    Delivery *deliveries = NULL;
    Vehicle *vehicles = NULL;

    // Cargar entregas y vehículos desde los archivos CSV
    int n_deliveries = load_delivery("db/deliveries.csv", &deliveries);
    error_load_delivery(n_deliveries);

    int n_vehicles = load_vehicle("db/vehicles.csv", &vehicles);
    error_load_vehicle(n_vehicles, deliveries);

    fprintf(stderr, "Se han cargado %d entregas y %d vehículos.\n", n_deliveries, n_vehicles);

    // Mostrar las entregas cargadas
    printf("\n--- Entregas cargadas ---\n");
    for (int i = 0; i < n_deliveries; i++)
    {
        printf("Entrega %d: %s\n", i + 1, deliveries[i].id);
        printf("  Origen: (%.2f, %.2f)\n", deliveries[i].origin_x, deliveries[i].origin_y);
        printf("  Destino: (%.2f, %.2f)\n", deliveries[i].destination_x, deliveries[i].destination_y);
        printf("  Hora de inicio: %s\n", deliveries[i].start);
        printf("  Hora de fin: %s\n", deliveries[i].end);
        printf("  Duración: %d minutos\n", deliveries[i].duration);
        printf("  Prioridad: %d\n", deliveries[i].priority);
        printf("  Tipo de vehículo: %d\n", deliveries[i].vehicle_type);
        printf("  Volumen: %.2f\n", deliveries[i].volume);
        printf("  Peso: %.2f\n", deliveries[i].weight);
    }

    // Mostrar los vehículos cargados
    printf("\n--- Vehículos cargados ---\n");
    for (int i = 0; i < n_vehicles; i++)
    {
        printf("Vehículo %d: %s\n", i + 1, vehicles[i].id);
        printf("  Tipo: %d\n", vehicles[i].type);
        printf("  Capacidad de volumen: %.2f\n", vehicles[i].capacity_volume);
        printf("  Capacidad de peso: %.2f\n", vehicles[i].capacity_weight);
        printf("  Hora de inicio: %s\n", vehicles[i].start);
        printf("  Hora de fin: %s\n", vehicles[i].end);
        printf("  Posición: (%.2f, %.2f)\n", vehicles[i].pos_x, vehicles[i].pos_y);
        printf("  Especialidad: %d\n", vehicles[i].speciality);
    }

    // Validar los datos de los vehículos
    validate_vehicle_data(vehicles, n_vehicles);

    // Asignar entregas a vehículos
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles);

    // Calcular la distancia total recorrida por los vehículos
    float total_distance = calculate_total_distance(vehicles, n_vehicles, deliveries, n_deliveries);
    printf("\nDistancia total recorrida por los vehículos: %.2f km\n", total_distance);

    // Calcular la utilización de los vehículos
    printf("\n--- Utilización de los vehículos ---\n");
    calculate_vehicle_utilization(vehicles, n_vehicles);

    // Liberar memoria
    free(deliveries);
    free(vehicles);

    return EXIT_SUCCESS;
}