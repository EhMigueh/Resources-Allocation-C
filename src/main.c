#include "header.h"

int main(int argc, char *argv[])
{
    Delivery *deliveries = NULL;
    Vehicle *vehicles = NULL;

    // Cargar entregas y vehículos desde los archivos CSV
    int n_deliveries = load_delivery("input/deliveries.csv", &deliveries);
    error_load_delivery(n_deliveries);

    int n_vehicles = load_vehicle("input/vehicles.csv", &vehicles);
    error_load_vehicle(n_vehicles, deliveries);

    fprintf(stdout, "\nSe han cargado %d entregas y %d vehículos.\n", n_deliveries, n_vehicles);

    // Validar los datos de los vehículos
    validate_vehicle_data(vehicles, n_vehicles);

    // Procesar los argumentos de la línea de comandos
    process_command(argc, argv, deliveries, n_deliveries, vehicles, n_vehicles);

    // Calcular la distancia total recorrida por los vehículos
    calculate_total_distance(vehicles, n_vehicles, deliveries, n_deliveries);

    // Calcular la utilización de los vehículos
    calculate_vehicle_utilization(vehicles, n_vehicles);

    // Liberar memoria
    free(deliveries);
    free(vehicles);

    return EXIT_SUCCESS;
}