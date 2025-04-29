#include "header.h"

void error_load_delivery(int var)
{
    if (var == 0)
    {
        fprintf(stderr, "ERROR! No se pudieron cargar las tareas.\n");
        fprintf(stderr, "Revise el archivo deliveries.csv o las función load_delivery.\n");
        exit(EXIT_FAILURE);
    }
}

void error_load_vehicle(int var, Delivery *deliveries)
{
    if (var == 0)
    {
        fprintf(stderr, "ERROR! No se pudieron cargar los vehículos.\n");
        fprintf(stderr, "Revise el archivo vehicles.csv o las función load_vehicle.\n");
        free(deliveries);
        exit(EXIT_FAILURE);
    }
}

void error_open_file(FILE *file, const char *filename)
{
    if (!file)
    {
        fprintf(stderr, "ERROR! No se pudo abrir el archivo %s.\n", filename);
        exit(EXIT_FAILURE);
    }
}

void error_malloc_delivery(Delivery *temp, FILE *file)
{
    if (!temp)
    {
        fprintf(stderr, "ERROR! No se pudo asignar memoria para las entregas.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
}

void error_malloc_vehicle(Vehicle *temp, FILE *file)
{
    if (!temp)
    {
        fprintf(stderr, "ERROR! No se pudo asignar memoria para los vehículos.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
}

void error_selection_choice(Delivery *deliveries, Vehicle *vehicles)
{
    fprintf(stderr, "ERROR! Opción inválida. Por favor, ingrese un número válido.\n");
    free(deliveries);
    free(vehicles);
    exit(EXIT_FAILURE);
}