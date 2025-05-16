#include "constants.h"
#include "models.h"
#include "errors.h"
#include "utils.h"
#include "functions.h"

// Función de manejo de errores general
void fatal_error(const char *header, const char *detail, const char *filename)
{
    fprintf(stderr, RED_COLOR "\nERROR! %s\n", header);
    fprintf(stderr, "%s\n", detail);
    fprintf(stderr, "Posible ERROR en el archivo -> %s.\n\n" RESET_COLOR, filename);
    exit(EXIT_FAILURE);
}

// Se muestra cuando se intenta abrir un archivo y no se puede
void error_open_file(FILE *file, const char *filename)
{
    if (!file)
        fatal_error("No se pudo abrir el archivo", "Revise el nombre del archivo o su ruta", filename);
}

void error_create_file(FILE *file, const char *filename)
{
    if (!file)
        fatal_error("No se pudo crear el archivo", "Revise el nombre del archivo o su ruta", filename);
}

// Se muestra cuando no se pueden cargar los datos desde el archivo CSV
void error_load_data(int n, DataType type, Delivery *deliveries)
{
    if (type == DATA_DELIVERY && n == 0)
        fatal_error("No se pudieron cargar las entregas", "Revise el archivo deliveries.csv o la funcion load_csv_data/parse_deliveries", "input/deliveries.csv o load.c");
    else if (type == DATA_VEHICLE && n == 0)
    {
        fatal_error("No se pudieron cargar los vehiculos", "Revise el archivo vehicles.csv o la funcion load_csv_data/parse_vehicles", "input/vehicles.csv o load.c");
        free(deliveries);
    }
}

// Se muestra cuando no se puede asignar memoria para las entregas o vehículos
void error_malloc(Delivery *tempdelivery, Vehicle *tempvehicle, FILE *file, DataType type)
{
    if (type == DATA_DELIVERY && !tempdelivery)
    {
        fclose(file);
        fatal_error("No se pudo asignar memoria para las entregas", "Revise el archivo deliveries.csv o la funcion load_csv_data", "input/deliveries.csv o load.c");
    }
    else if (type == DATA_VEHICLE && !tempvehicle)
    {
        fclose(file);
        fatal_error("No se pudo asignar memoria para los vehiculos", "Revise el archivo vehicles.csv o la funcion load_csv_data", "input/vehicles.csv o load.c");
    }
}

// Se muestra cuando no se pueden leer los encabezados del archivo CSV
void error_read_header(FILE *file, Delivery *temp_deliveries, Vehicle *temp_vehicles, DataType type, char *line)
{
    if (fgets(line, MAX_LINE_LENGTH, file) == NULL)
    {
        if (type == DATA_DELIVERY)
        {
            fclose(file);
            free(temp_deliveries);
            fatal_error("No se pudieron leer los encabezados de deliveries.csv", "Revise el archivo deliveries.csv o la funcion load_csv_data", "input/deliveries.csv o load.c");
        }
        else if (type == DATA_VEHICLE)
        {
            fclose(file);
            free(temp_vehicles);
            fatal_error("No se pudieron leer los encabezados de vehicles.csv", "Revise el archivo vehicles.csv o la funcion load_csv_data", "input/vehicles.csv o load.c");
        }
    }
}

// Se muestra cuando la línea no está formateada correctamente
void error_format(const char *line, const char *filename)
{
    if (strchr(line, ',') == NULL)
        fatal_error("Linea mal formateada", "Revise el archivo o la función load_csv_data", filename);
}

// Se muestra cuando la línea no se parsea correctamente
void error_parse(int parsed, const char *line, DataType type)
{
    if (type == DATA_DELIVERY && parsed != 12)
        fatal_error("Linea mal parseada", "Revise el archivo deliveries.csv o la funcion parse_delivery", line);
    else if (type == DATA_VEHICLE && parsed != 8)
        fatal_error("Linea mal parseada", "Revise el archivo vehicles.csv o la funcion parse_vehicle", line);
}

// Se muestra cuando la capacidad del vehículo no es válida
void error_vehicle_capacity(void)
{
    fatal_error("Capacidad del vehiculo invalida", "Revise el archivo vehicles.csv o la funcion validate_vehicle_data/load_csv_data", "input/vehicles.csv o load.c");
}

// Se muestra cuando el tipo de vehículo no es válido
void error_vehicle_type(void)
{
    fatal_error("Tipo de vehiculo invalido", "Revise el archivo vehicles.csv o la funcion validate_vehicle_data/load_csv_data", "input/vehicles.csv o load.c");
}

void error_no_arguments(void)
{
    show_help();
    fatal_error("No se proporcionaron argumentos", "Revise la opcion --h o --help", "main.c");
}

void error_invalid_option(void)
{
    show_help();
    fatal_error("Opcion invalida", "Revise la opcion --h o --help", "main.c");
}

void error_invalid_argc(int argc)
{
    if (argc < 4)
        fatal_error("Debes especificar el numero de entregas y vehiculos", "Ejemplo: ./build/program.out --db 20 10 o ./build/program.out --database 20 10", "terminal");
}

void error_invalid_numbers(char *endptr1, char *endptr2, int num_deliveries, int num_vehicles)
{
    if (*endptr1 != '\0' || *endptr2 != '\0' || num_deliveries <= 0 || num_vehicles <= 0)
        fatal_error("Los valores de entregas y vehiculos deben ser numeros enteros positivos", "Ejemplo: ./build/program.out --db 20 10 o ./build/program.out --database 20 10", "terminal");
}

void error_vehicle_entries(int num_vehicles)
{
    if (num_vehicles > MAX_ENTRIES)
        fatal_error("El numero de vehiculos no puede exceder el maximo de entradas", "Ejemplo: ./build/program.out --db 20 10 o ./build/program.out --database 20 10", "MAX_ENTRIES -> header.h");
}

void error_delivery_entries(int num_deliveries)
{
    if (num_deliveries > MAX_ENTRIES)
        fatal_error("El numero de entregas no puede exceder el maximo de entradas", "Ejemplo: ./build/program.out --db 20 10 o ./build/program.out --database 20 10", "MAX_ENTRIES -> header.h");
}

void error_exec_python(void)
{
    fatal_error("Error al ejecutar el script de Python", "Revise el archivo o la funcion schedule_edf/schedule_pb/schedule_nn", "python/plot_edf.py o python/plot_pb.py o python/plot_nn.py");
}