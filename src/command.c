#include "header.h"

// Función para mostrar el menú de ayuda
void show_help()
{
    fprintf(stdout, CYAN_COLOR "\n--- Ayuda: Opciones de Algoritmos ---\n\n");
    fprintf(stdout, "Uso: ./build/program.out [opciones]\n\n");
    fprintf(stdout, "Opciones disponibles:\n\n");
    fprintf(stdout, "  --h, --help                          Muestra este menu de ayuda.\n");
    fprintf(stdout, "  --db, --database <entregas> <autos>   Crea las bases de datos de manera aleatoria.\n");
    fprintf(stdout, "  --edf                                Ejecuta el algoritmo Earliest Deadline First (EDF).\n");
    fprintf(stdout, "  --pb, --priority                     Ejecuta el algoritmo Priority-Based Scheduling.\n");
    fprintf(stdout, "  --nn                                 Ejecuta el algoritmo Nearest Neighbor.\n");
    fprintf(stdout, "\nEjemplo:\n\n");
    fprintf(stdout, "  ./build/program.out --edf\n");
    fprintf(stdout, "  ./build/program.out --db 20 10\n\n" RESET_COLOR);
    exit(EXIT_SUCCESS);
}

// Función para procesar los argumentos de la línea de comandos
void process_command(int argc, char *argv[], Delivery *deliveries, int *n_deliveries, Vehicle *vehicles, int *n_vehicles)
{
    if (argc < 2)
        error_no_arguments();

    if (strcmp(argv[1], "--h") == 0 || strcmp(argv[1], "--help") == 0)
        show_help();
    else if (strcmp(argv[1], "--db") == 0 || strcmp(argv[1], "--database") == 0)
    {
        error_invalid_argc(argc);

        // Validar que los argumentos sean números
        char *endptr1, *endptr2;
        int num_deliveries = strtol(argv[2], &endptr1, 10);
        int num_vehicles = strtol(argv[3], &endptr2, 10);

        error_invalid_numbers(endptr1, endptr2, num_deliveries, num_vehicles);

        create_random_databases(num_deliveries, num_vehicles);
    }
    else if (strcmp(argv[1], "--edf") == 0)
    {
        // Cargar datos antes de ejecutar el algoritmo
        *n_deliveries = load_csv_data("./input/deliveries.csv", (void **)&deliveries, DATA_DELIVERY);
        *n_vehicles = load_csv_data("./input/vehicles.csv", (void **)&vehicles, DATA_VEHICLE);

        fprintf(stdout, GREEN_COLOR "\nEntregas (%d) y Vehiculos (%d) generados/cargados con exito.\n" RESET_COLOR, *n_deliveries, *n_vehicles);

        schedule_edf(deliveries, *n_deliveries, vehicles, *n_vehicles);

        // Ejecutar programa en python.
        system("python3 ./python/plot_edf.py");
    }
    else if (strcmp(argv[1], "--pb") == 0 || strcmp(argv[1], "--priority") == 0)
    {
        // Cargar datos antes de ejecutar el algoritmo
        *n_deliveries = load_csv_data("./input/deliveries.csv", (void **)&deliveries, DATA_DELIVERY);
        *n_vehicles = load_csv_data("./input/vehicles.csv", (void **)&vehicles, DATA_VEHICLE);

        fprintf(stdout, GREEN_COLOR "\nEntregas (%d) y Vehiculos (%d) generados/cargados con exito.\n" RESET_COLOR, *n_deliveries, *n_vehicles);

        schedule_pb(deliveries, *n_deliveries, vehicles, *n_vehicles);

        // Ejecutar programa en python.
        system("python3 ./python/plot_pb.py");
    }
    else if (strcmp(argv[1], "--nn") == 0)
    {
        // Cargar datos antes de ejecutar el algoritmo
        *n_deliveries = load_csv_data("./input/deliveries.csv", (void **)&deliveries, DATA_DELIVERY);
        *n_vehicles = load_csv_data("./input/vehicles.csv", (void **)&vehicles, DATA_VEHICLE);

        fprintf(stdout, GREEN_COLOR "\nEntregas (%d) y Vehiculos (%d) generados/cargados con exito.\n" RESET_COLOR, *n_deliveries, *n_vehicles);

        schedule_nn(deliveries, *n_deliveries, vehicles, *n_vehicles);

        // Ejecutar programa en python.
        system("python3 ./python/plot_nn.py");
    }
    else
        error_invalid_option();
}