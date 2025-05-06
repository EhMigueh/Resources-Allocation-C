#include "header.h"

// Función para mostrar el menu de ayuda
void show_help()
{
    fprintf(stdout, "\n--- Ayuda: Opciones de Algoritmos ---\n\n");
    fprintf(stdout, "Uso: program.out [opciones]\n\n");
    fprintf(stdout, "Opciones disponibles:\n");
    fprintf(stdout, "  --h, --help          Muestra este menu de ayuda.\n");
    fprintf(stdout, "  --edf                Ejecuta el algoritmo Earliest Deadline First (EDF).\n");
    fprintf(stdout, "  --priority           Ejecuta el algoritmo Priority-Based Scheduling.\n");
    fprintf(stdout, "  --nn                 Ejecuta el algoritmo Nearest Neighbor.\n");
    fprintf(stdout, "\nEjemplo:\n");
    fprintf(stdout, "  ./program.out --edf\n\n");
}

// Funcion para procesar los argumentos de la linea de comandos
void process_command(int argc, char *argv[], Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    if (argc < 2)
    {
        fprintf(stderr, RED_COLOR "Error: No se proporcionaron argumentos.\n" RESET_COLOR);
        show_help();
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "--h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        show_help();
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(argv[1], "--edf") == 0)
    {
        schedule_edf(deliveries, n_deliveries, vehicles, n_vehicles);
    }
    else if (strcmp(argv[1], "--priority") == 0 || strcmp(argv[1], "--py") == 0)
    {
        schedule_based_priority(deliveries, n_deliveries, vehicles, n_vehicles);
    }
    else if (strcmp(argv[1], "--nn") == 0)
    {
        schedule_nearest_neighbor(deliveries, n_deliveries, vehicles, n_vehicles);
    }
    else
    {
        fprintf(stderr, RED_COLOR "Error: Opción no valida '%s'.\n" RESET_COLOR, argv[1]);
        show_help();
        exit(EXIT_FAILURE);
    }
}