#include "header.h"

// Función para eliminar el salto de línea al final de una cadena, si existe
void delete_line_leap(char *line)
{
    char *newline = strchr(line, '\n');
    if (newline)
        *newline = '\0'; // Reemplaza el salto de línea con un terminador nulo
}

// Función para cargar las entregas desde el CSV
int load_delivery(const char *filename, Delivery **deliveries)
{
    FILE *file = fopen(filename, "r");
    error_open_file(file, filename);

    char line[MAX_LINE_LENGTH];
    int count = 0;
    int capacity = 10;

    Delivery *temp_deliveries = malloc(capacity * sizeof(Delivery));
    error_malloc_delivery(temp_deliveries, file);

    // Lee los encabezados y los descarta
    if (fgets(line, MAX_LINE_LENGTH, file) == NULL)
        error_read_top_delivery(file, temp_deliveries);

    // Lee cada línea del archivo
    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        if (count == capacity)
        {
            capacity *= 2;
            temp_deliveries = realloc(temp_deliveries, sizeof(Delivery) * capacity);
            error_malloc_delivery(temp_deliveries, file);
        }

        delete_line_leap(line);

        // Validar que la línea tenga el formato correcto
        if (strchr(line, ',') == NULL)
            error_format_delivery(line);

        // Parsear los datos
        int parsed = sscanf(line, "%[^,],%f,%f,%f,%f,%[^,],%[^,],%d,%d,%d,%f,%f",
                            temp_deliveries[count].id, &temp_deliveries[count].origin_x, &temp_deliveries[count].origin_y,
                            &temp_deliveries[count].destination_x, &temp_deliveries[count].destination_y, temp_deliveries[count].start,
                            temp_deliveries[count].end, &temp_deliveries[count].duration, &temp_deliveries[count].priority,
                            &temp_deliveries[count].vehicle_type, &temp_deliveries[count].volume, &temp_deliveries[count].weight);

        error_parse_delivery(parsed, line);

        count++;
    }

    fclose(file);
    *deliveries = temp_deliveries;

    return count; // Devuelve el número de vehículos cargados
}

// Función para cargar los vehículos desde el CSV.
int load_vehicle(const char *filename, Vehicle **vehicles)
{
    FILE *file = fopen(filename, "r");
    error_open_file(file, filename);

    char line[MAX_LINE_LENGTH];
    int count = 0;
    int capacity = 10;

    Vehicle *temp_vehicles = malloc(capacity * sizeof(Vehicle));
    error_malloc_vehicle(temp_vehicles, file);

    // Lee los encabezados y los descarta
    if (fgets(line, MAX_LINE_LENGTH, file) == NULL)
        error_read_top_vehicle(file, temp_vehicles);

    // Lee cada línea del archivo
    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        if (count == capacity)
        {
            capacity *= 2;
            temp_vehicles = realloc(temp_vehicles, sizeof(Vehicle) * capacity);
            error_malloc_vehicle(temp_vehicles, file);
        }

        delete_line_leap(line);

        // Validar que la línea tenga el formato correcto
        if (strchr(line, ',') == NULL)
            error_format_vehicle(line);

        // Parsear los datos
        int parsed = sscanf(line, "%[^,],%d,%f,%f,%[^,],%[^,],%f,%f,%d",
                            temp_vehicles[count].id, &temp_vehicles[count].type, &temp_vehicles[count].capacity_volume,
                            &temp_vehicles[count].capacity_weight, temp_vehicles[count].start, temp_vehicles[count].end,
                            &temp_vehicles[count].pos_x, &temp_vehicles[count].pos_y, &temp_vehicles[count].speciality);

        error_parse_vehicle(parsed, line);

        // Inicializar las capacidades originales
        temp_vehicles[count].original_volume = temp_vehicles[count].capacity_volume;
        temp_vehicles[count].original_weight = temp_vehicles[count].capacity_weight;
        temp_vehicles[count].deliveries_assigned = 0;

        count++;
    }

    fclose(file);
    *vehicles = temp_vehicles;

    return count; // Devuelve el número de vehículos cargados
}