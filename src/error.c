#include "header.h"

void fatal_error(const char *header, const char *detail, const char *filename)
{
    fprintf(stderr, RED_COLOR "\nERROR! %s\n", header);
    fprintf(stderr, "%s\n", detail);
    fprintf(stderr, "Posible ERROR en el archivo -> %s.\n\n" RESET_COLOR, filename);
    exit(EXIT_FAILURE);
}

void error_open_file(FILE *file, const char *filename)
{
    if (!file)
        fatal_error("No se pudo abrir el archivo", "Revise el nombre del archivo o su ruta", filename);
}

void error_load_data(int n, DataType type, Delivery *deliveries)
{
    if (type == DATA_DELIVERY && n == 0)
        fatal_error("No se pudieron cargar las entregas", "Revise el archivo deliveries.csv o la función load_csv_data/parse_deliveries", "input/deliveries.csv o load.c");
    else if (type == DATA_VEHICLE && n == 0)
    {
        fatal_error("No se pudieron cargar los vehículos", "Revise el archivo vehicles.csv o la función load_csv_data/parse_vehicles", "input/vehicles.csv o load.c");
        free(deliveries);
    }
}

void error_malloc(Delivery *tempdelivery, Vehicle *tempvehicle, FILE *file, DataType type)
{
    if (type == DATA_DELIVERY && !tempdelivery)
    {
        fclose(file);
        fatal_error("No se pudo asignar memoria para las entregas", "Revise el archivo deliveries.csv o la función load_csv_data", "input/deliveries.csv o load.c");
    }
    else if (type == DATA_VEHICLE && !tempvehicle)
    {
        fclose(file);
        fatal_error("No se pudo asignar memoria para los vehículos", "Revise el archivo vehicles.csv o la función load_csv_data", "input/vehicles.csv o load.c");
    }
}

void error_read_header(FILE *file, Delivery *temp_deliveries, Vehicle *temp_vehicles, DataType type, char *line)
{
    if (fgets(line, MAX_LINE_LENGTH, file) == NULL)
    {
        if (type == DATA_DELIVERY)
        {
            fclose(file);
            free(temp_deliveries);
            fatal_error("No se pudieron leer los encabezados de deliveries.csv", "Revise el archivo deliveries.csv o la función load_csv_data", "input/deliveries.csv o load.c");
        }
        else if (type == DATA_VEHICLE)
        {
            fclose(file);
            free(temp_vehicles);
            fatal_error("No se pudieron leer los encabezados de vehicles.csv", "Revise el archivo vehicles.csv o la función load_csv_data", "input/vehicles.csv o load.c");
        }
    }
}

void error_format(const char *line, const char *filename)
{
    if (strchr(line, ',') == NULL)
        fatal_error("Linea mal formateada", "Revise el archivo o la función load_csv_data", filename);
}

void error_parse(int parsed, const char *line, DataType type)
{
    if (type == DATA_DELIVERY && parsed != 12)
        fatal_error("Línea mal parseada", "Revise el archivo deliveries.csv o la función parse_delivery", line);
    else if (type == DATA_VEHICLE && parsed != 9)
        fatal_error("Linea mal parseada", "Revise el archivo vehicles.csv o la función parse_vehicle", line);
}

void error_vehicle_capacity(void)
{
    fatal_error("Capacidad del vehículo no válida", "Revise el archivo vehicles.csv o la función validate_vehicle_data/load_csv_data", "input/vehicles.csv o load.c");
}

void error_vehicle_type(void)
{
    fatal_error("Tipo de vehículo no válido", "Revise el archivo vehicles.csv o la función validate_vehicle_data/load_csv_data", "input/vehicles.csv o load.c");
}