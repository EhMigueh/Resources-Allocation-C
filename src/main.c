#include "header.h"

int main(int argc, char *argv[])
{
    // Variables para entregas y vehículos
    Delivery deliveries[MAX_ENTRIES];
    Vehicle vehicles[MAX_ENTRIES];
    int n_deliveries = 0; // Inicializar con 0
    int n_vehicles = 0;   // Inicializar con 0

    // Procesar los argumentos de la línea de comandos
    process_command(argc, argv, deliveries, &n_deliveries, vehicles, &n_vehicles);

    return 0;
}