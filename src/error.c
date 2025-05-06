#include "header.h"

void error_load_delivery(int n_deliveries)
{
    if (n_deliveries == 0)
    {
        fprintf(stderr, RED_COLOR "\nERROR! No se pudieron cargar las tareas.\n");
        fprintf(stderr, "Revise el archivo deliveries.csv o las funcion load_delivery.\n\n" RESET_COLOR);
        exit(EXIT_FAILURE);
    }
}

void error_load_vehicle(int n_vehicles, Delivery *deliveries)
{
    if (n_vehicles == 0)
    {
        fprintf(stderr, RED_COLOR "\nERROR! No se pudieron cargar los vehiculos.\n");
        fprintf(stderr, "Revise el archivo vehicles.csv o las funcion load_vehicle.\n\n" RESET_COLOR);
        free(deliveries);
        exit(EXIT_FAILURE);
    }
}

void error_open_file(FILE *file, const char *filename)
{
    if (!file)
    {
        fprintf(stderr, RED_COLOR "\nERROR! No se pudo abrir el archivo %s.\n\n" RESET_COLOR, filename);
        exit(EXIT_FAILURE);
    }
}

void error_malloc_delivery(Delivery *temp, FILE *file)
{
    if (!temp)
    {
        fprintf(stderr, RED_COLOR "\nERROR! No se pudo asignar memoria para las entregas.\n\n" RESET_COLOR);
        fclose(file);
        exit(EXIT_FAILURE);
    }
}

void error_malloc_vehicle(Vehicle *temp, FILE *file)
{
    if (!temp)
    {
        fprintf(stderr, RED_COLOR "\nERROR! No se pudo asignar memoria para los vehiculos.\n\n" RESET_COLOR);
        fclose(file);
        exit(EXIT_FAILURE);
    }
}

void error_read_top_delivery(FILE *file, Delivery *temp_deliveries)
{
    fclose(file);
    free(temp_deliveries);
    fprintf(stderr, RED_COLOR "\nERROR! No se pudieron leer las entregas.\n");
    fprintf(stderr, "Revise el archivo deliveries.csv o la funcion load_delivery.\n\n" RESET_COLOR);
    exit(EXIT_FAILURE);
}

void error_read_top_vehicle(FILE *file, Vehicle *temp_vehicles)
{
    fclose(file);
    free(temp_vehicles);
    fprintf(stderr, RED_COLOR "\nERROR! No se pudieron leer los vehiculos.\n");
    fprintf(stderr, "Revise el archivo vehicles.csv o la funcion load_vehicle.\n\n" RESET_COLOR);
    exit(EXIT_FAILURE);
}

void error_format_delivery(const char *line)
{
    fprintf(stderr, RED_COLOR "\nERROR! Linea mal formateada en deliveries.csv: %s\n\n" RESET_COLOR, line);
    exit(EXIT_FAILURE);
}

void error_format_vehicle(const char *line)
{
    fprintf(stderr, RED_COLOR "\nERROR! Linea mal formateada en vehicles.csv: %s\n\n" RESET_COLOR, line);
    exit(EXIT_FAILURE);
}

void error_parse_delivery(int parsed, const char *line)
{
    if (parsed != 12)
    {
        fprintf(stderr, RED_COLOR "\nERROR! Error al parsear la linea en deliveries.csv: %s\n\n" RESET_COLOR, line);
        exit(EXIT_FAILURE);
    }
}

void error_parse_vehicle(int parsed, const char *line)
{
    if (parsed != 9)
    {
        fprintf(stderr, RED_COLOR "\nERROR! Error al parsear la linea en vehicles.csv: %s\n\n" RESET_COLOR, line);
        exit(EXIT_FAILURE);
    }
}

void error_vehicle_capacity(void)
{
    fprintf(stderr, RED_COLOR "\nERROR! Capacidad del vehiculo no valida.\n");
    fprintf(stderr, "Revise el archivo vehicles.csv o la funcion load_vehicle.\n\n" RESET_COLOR);
    exit(EXIT_FAILURE);
}

void error_vehicle_type(void)
{
    fprintf(stderr, RED_COLOR "\nERROR! Tipo de vehiculo no valido.\n");
    fprintf(stderr, "Revise el archivo vehicles.csv o la funcion load_vehicle.\n\n" RESET_COLOR);
    exit(EXIT_FAILURE);
}