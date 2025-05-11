#include "header.h"

// Función para mostrar el menú de ayuda
void show_help()
{
    fprintf(stdout, CYAN_COLOR "\n--- Ayuda: Opciones de Algoritmos ---\n\n");
    fprintf(stdout, "Uso: ./build/program.out [opciones]\n\n");
    fprintf(stdout, "Opciones disponibles:\n");
    fprintf(stdout, "  --h, --help          Muestra este menú de ayuda.\n");
    fprintf(stdout, "  --db --database      Crea las bases de datos de manera aleatoria.\n");
    fprintf(stdout, "  --edf                Ejecuta el algoritmo Earliest Deadline First (EDF).\n");
    fprintf(stdout, "  --pb, --priority     Ejecuta el algoritmo Priority-Based Scheduling.\n");
    fprintf(stdout, "  --nn                 Ejecuta el algoritmo Nearest Neighbor.\n");
    fprintf(stdout, "  --g <deliveries> <vehicles>  Genera archivos CSV personalizados.\n");
    fprintf(stdout, "\nEjemplo:\n");
    fprintf(stdout, "  ./build/program.out --edf\n");
    fprintf(stdout, "  ./build/program.out --g 20 10\n\n" RESET_COLOR);
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
        create_random_databases();

        // Cargar datos desde los archivos generados
        *n_deliveries = load_csv_data("./input/deliveries.csv", (void **)&deliveries, DATA_DELIVERY);
        *n_vehicles = load_csv_data("./input/vehicles.csv", (void **)&vehicles, DATA_VEHICLE);

        fprintf(stdout, GREEN_COLOR "Bases de datos generadas y cargadas con éxito.\n" RESET_COLOR);
    }
    else if (strcmp(argv[1], "--edf") == 0)
    {
        // Cargar datos antes de ejecutar el algoritmo
        *n_deliveries = load_csv_data("./input/deliveries.csv", (void **)&deliveries, DATA_DELIVERY);
        *n_vehicles = load_csv_data("./input/vehicles.csv", (void **)&vehicles, DATA_VEHICLE);

        schedule_edf(deliveries, *n_deliveries, vehicles, *n_vehicles);
    }
    else if (strcmp(argv[1], "--pb") == 0 || strcmp(argv[1], "--priority") == 0)
    {
        // Cargar datos antes de ejecutar el algoritmo
        *n_deliveries = load_csv_data("./input/deliveries.csv", (void **)&deliveries, DATA_DELIVERY);
        *n_vehicles = load_csv_data("./input/vehicles.csv", (void **)&vehicles, DATA_VEHICLE);

        schedule_based_priority(deliveries, *n_deliveries, vehicles, *n_vehicles);
    }
    else if (strcmp(argv[1], "--nn") == 0)
    {
        // Cargar datos antes de ejecutar el algoritmo
        *n_deliveries = load_csv_data("./input/deliveries.csv", (void **)&deliveries, DATA_DELIVERY);
        *n_vehicles = load_csv_data("./input/vehicles.csv", (void **)&vehicles, DATA_VEHICLE);

        schedule_nearest_neighbor(deliveries, *n_deliveries, vehicles, *n_vehicles);
    }
    else if (strcmp(argv[1], "--g") == 0)
    {
        if (argc < 4)
        {
            fprintf(stderr, RED_COLOR "Error: Debes especificar el numero de entregas y vehiculos.\n" RESET_COLOR);
            fprintf(stderr, "Ejemplo: ./build/program.out --g 20 10\n");
            exit(EXIT_FAILURE);
        }

        // Validar que los argumentos sean números
        char *endptr1, *endptr2;
        int num_deliveries = strtol(argv[2], &endptr1, 10);
        int num_vehicles = strtol(argv[3], &endptr2, 10);

        if (*endptr1 != '\0' || *endptr2 != '\0' || num_deliveries <= 0 || num_vehicles <= 0)
        {
            fprintf(stderr, RED_COLOR "Error: Los valores de entregas y vehiculos deben ser numeros enteros positivos.\n" RESET_COLOR);
            fprintf(stderr, "Ejemplo: ./build/program.out --g 20 10\n");
            exit(EXIT_FAILURE);
        }

        // Generar los archivos CSV personalizados
        generate_custom_csv(num_deliveries, num_vehicles);

        // Cargar los datos generados en las estructuras
        *n_deliveries = load_csv_data("./input/deliveries.csv", (void **)&deliveries, DATA_DELIVERY);
        *n_vehicles = load_csv_data("./input/vehicles.csv", (void **)&vehicles, DATA_VEHICLE);

        fprintf(stdout, GREEN_COLOR "Archivos CSV personalizados generados y cargados con exito.\n" RESET_COLOR);
        exit(EXIT_SUCCESS);
    }
    else
        error_invalid_option();
}