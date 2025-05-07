#include "header.h"

int main(int argc, char *argv[])
{
    Delivery *deliveries = NULL;
    Vehicle *vehicles = NULL;
    srand((unsigned int)time(NULL));

    // Cargar entregas y vehículos desde los archivos CSV
    int n_deliveries = load_csv_data("input/deliveries.csv", (void **)&deliveries, DATA_DELIVERY);
    error_load_data(n_deliveries, DATA_DELIVERY, NULL);

    int n_vehicles = load_csv_data("input/vehicles.csv", (void **)&vehicles, DATA_VEHICLE);
    error_load_data(n_vehicles, DATA_VEHICLE, deliveries);

    fprintf(stdout, GREEN_COLOR "\nSe han cargado %d entregas y %d vehículos.\n" RESET_COLOR, n_deliveries, n_vehicles);

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