#include "header.h"

// Función para mostrar el menu de ayuda
void show_help()
{
    fprintf(stdout, CYAN_COLOR "\n--- Ayuda: Opciones de Algoritmos ---\n\n");
    fprintf(stdout, "Uso: ./build/program.out [opciones]\n\n");
    fprintf(stdout, "Opciones disponibles:\n");
    fprintf(stdout, "  --h, --help          Muestra este menu de ayuda.\n");
    fprintf(stdout, "  --db --database      Crea las bases de datos de manera aleatoria.\n");
    fprintf(stdout, "  --edf                Ejecuta el algoritmo Earliest Deadline First (EDF).\n");
    fprintf(stdout, "  --pb, --priority     Ejecuta el algoritmo Priority-Based Scheduling.\n");
    fprintf(stdout, "  --nn                 Ejecuta el algoritmo Nearest Neighbor.\n");
    fprintf(stdout, "\nEjemplo:\n");
    fprintf(stdout, "  ./build/program.out --edf\n\n" RESET_COLOR);
    exit(EXIT_SUCCESS);
}

// Función para procesar los argumentos de la linea de comandos
void process_command(int argc, char *argv[], Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    if (argc < 2)
        error_no_arguments();

    if (strcmp(argv[1], "--h") == 0 || strcmp(argv[1], "--help") == 0)
        show_help();
    else if (strcmp(argv[1], "--db") == 0 || strcmp(argv[1], "--database") == 0)
    {
        fprintf(stdout, YELLOW_COLOR "Creando bases de datos aleatorias...\n" RESET_COLOR);
        // Aquí se llamaría a la función para crear las bases de datos aleatorias
        // create_random_databases();
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(argv[1], "--edf") == 0)
        schedule_edf(deliveries, n_deliveries, vehicles, n_vehicles);
    else if (strcmp(argv[1], "--pb") == 0 || strcmp(argv[1], "--priority") == 0)
        schedule_based_priority(deliveries, n_deliveries, vehicles, n_vehicles);
    else if (strcmp(argv[1], "--nn") == 0)
        schedule_nearest_neighbor(deliveries, n_deliveries, vehicles, n_vehicles);
    else
        error_invalid_option();
}