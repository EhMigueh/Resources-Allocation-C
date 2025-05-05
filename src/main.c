#include "header.h"

int main(void)
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

    // Menú para seleccionar la estrategia de scheduling (TEMPORAL)
    int choice;
    menu_scheduling();

    if (scanf("%d", &choice) != 1)
        error_selection_choice(deliveries, vehicles);

    // Ejecutar la estrategia seleccionada (TEMPORAL)
    switch (choice)
    {
    case 1:
        schedule_edf(deliveries, n_deliveries, vehicles, n_vehicles);
        break;
    case 2:
        schedule_priority(deliveries, n_deliveries, vehicles, n_vehicles);
        break;
    case 3:
        schedule_nearest_neighbor(deliveries, n_deliveries, vehicles, n_vehicles);
        break;
    default:
        fprintf(stdout, YELLOW_COLOR "\nOpción no válida. Seleccione otra opción.\n\n" RESET_COLOR);
        exit(EXIT_FAILURE); // TEMPORAL
        break;
    }

    // Calcular la distancia total recorrida por los vehículos
    calculate_total_distance(vehicles, n_vehicles, deliveries, n_deliveries);

    // Calcular la utilización de los vehículos
    calculate_vehicle_utilization(vehicles, n_vehicles);

    // Liberar memoria
    free(deliveries);
    free(vehicles);

    return EXIT_SUCCESS;
}
