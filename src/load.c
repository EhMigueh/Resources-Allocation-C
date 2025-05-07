#include "header.h"

// Función para cargar los datos desde el CSV (dependiendo del tipo)
int load_csv_data(const char *filename, void **data, DataType type)
{
    FILE *file = fopen(filename, "r");
    error_open_file(file, filename);

    char line[MAX_LINE_LENGTH];
    int count = 0;
    int capacity = 10;
    void *temp_data = NULL;

    if (type == DATA_DELIVERY)
    {
        temp_data = malloc(capacity * sizeof(Delivery));
        error_malloc(temp_data, NULL, file, type);
        error_read_header(file, temp_data, NULL, type, line);
    }
    else
    {
        temp_data = malloc(capacity * sizeof(Vehicle));
        error_malloc(NULL, temp_data, file, type);
        error_read_header(file, NULL, temp_data, type, line);
    }

    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        if (count == capacity)
        {
            capacity *= 2;
            temp_data = realloc(temp_data, (type == DATA_DELIVERY ? sizeof(Delivery) : sizeof(Vehicle)) * capacity);
            if (type == DATA_DELIVERY)
                error_malloc(temp_data, temp_data, file, type);
            else
                error_malloc(temp_data, temp_data, file, type);
        }

        delete_line_leap(line);

        if (type == DATA_DELIVERY)
        {
            error_format(line, filename);
            int parsed = parse_delivery(line, &((Delivery *)temp_data)[count]);
            error_parse(parsed, line, type);
        }
        else
        {
            error_format(line, filename);
            int parsed = parse_vehicle(line, &((Vehicle *)temp_data)[count]);
            error_parse(parsed, line, type);
            ((Vehicle *)temp_data)[count].original_volume = ((Vehicle *)temp_data)[count].capacity_volume;
            ((Vehicle *)temp_data)[count].original_weight = ((Vehicle *)temp_data)[count].capacity_weight;
            ((Vehicle *)temp_data)[count].deliveries_assigned = 0;
        }
        count++;
    }
    fclose(file);
    *data = temp_data;
    return count;
}

// Función para eliminar el salto de línea al final de una cadena, si existe
void delete_line_leap(char *line)
{
    char *newline = strchr(line, '\n');
    if (newline)
        *newline = '\0'; // Reemplaza el salto de línea con un terminador nulo
}

// Función para parsear los datos de una entrega
int parse_delivery(char *line, Delivery *delivery)
{
    return sscanf(line, "%[^,],%f,%f,%f,%f,%[^,],%[^,],%d,%d,%d,%f,%f",
                  delivery->id, &delivery->origin_x, &delivery->origin_y,
                  &delivery->destination_x, &delivery->destination_y, delivery->start,
                  delivery->end, &delivery->duration, &delivery->priority,
                  &delivery->vehicle_type, &delivery->volume, &delivery->weight);
}

// Función para parsear los datos de un vehículo
int parse_vehicle(char *line, Vehicle *vehicle)
{
    return sscanf(line, "%[^,],%d,%f,%f,%[^,],%[^,],%f,%f,%d",
                  vehicle->id, &vehicle->type, &vehicle->capacity_volume,
                  &vehicle->capacity_weight, vehicle->start, vehicle->end,
                  &vehicle->pos_x, &vehicle->pos_y, &vehicle->speciality);
}

// Validar los datos de los vehículos, esto siempre debería estar bien
void validate_vehicle_data(Vehicle *vehicles, int n_vehicles)
{
    for (int i = 0; i < n_vehicles; i++)
    {
        if (vehicles[i].capacity_volume <= 0 || vehicles[i].capacity_weight <= 0)
            error_vehicle_capacity();
        if (vehicles[i].type < 1 || vehicles[i].type > 3)
            error_vehicle_type();
    }
}