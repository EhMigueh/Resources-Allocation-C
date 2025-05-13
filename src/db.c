#include "header.h"

void generate_random_time(char *buffer, int min_hour, int max_hour)
{
    int hour = min_hour + rand() % (max_hour - min_hour + 1);
    int minute = (rand() % 4) * 15; // Genera minutos en múltiplos de 15
    snprintf(buffer, 7, "%02d:%02d", hour, minute);
}

float generate_random_float(float min, float max)
{
    return min + ((float)rand() / RAND_MAX) * (max - min);
}

void generate_random_deliveries_csv(int num_deliveries)
{
    error_delivery_entries(num_deliveries);

    FILE *file = fopen("./input/deliveries.csv", "w");
    error_create_file(file, "./input/deliveries.csv");

    fprintf(file, "id,origin_x,origin_y,destination_x,destination_y,start,end,duration,priority,vehicle_type,volume,weight\n");
    for (int i = 0; i < num_deliveries; i++)
    {
        char id[MAX_ID_LENGTH];
        char start[7];
        char end[7];
        snprintf(id, MAX_ID_LENGTH, "D%03d", i + 1);
        float origin_x = generate_random_float(5.0, 15.0);
        float origin_y = generate_random_float(10.0, 25.0);
        float destination_x = generate_random_float(10.0, 30.0);
        float destination_y = generate_random_float(10.0, 30.0);
        generate_random_time(start, 7, 11);
        generate_random_time(end, 12, 16);
        int duration = 20 + rand() % 31;
        int priority = 1 + rand() % 5;
        int vehicle_type = 1 + rand() % 3;
        float volume = generate_random_float(1.0, 4.0);
        float weight = generate_random_float(5.0, 20.0);

        fprintf(file, "%s,%.2f,%.2f,%.2f,%.2f,%s,%s,%d,%d,%d,%.2f,%.2f\n",
                id, origin_x, origin_y, destination_x, destination_y,
                start, end, duration, priority, vehicle_type, volume, weight);
    }
    fclose(file);
}

void generate_random_vehicles_csv(int num_vehicles)
{
    error_vehicle_entries(num_vehicles);

    FILE *file = fopen("./input/vehicles.csv", "w");
    error_create_file(file, "./input/vehicles.csv");

    fprintf(file, "id,type,capacity_volume,capacity_weight,start,end,pos_x,pos_y,speciality\n");
    for (int i = 0; i < num_vehicles; i++)
    {
        char id[MAX_ID_LENGTH];
        char start[7];
        char end[7];
        snprintf(id, MAX_ID_LENGTH, "V%03d", i + 1);
        int type = 1 + rand() % 3;
        float capacity_volume = generate_random_float(5.0, 12.0);
        float capacity_weight = generate_random_float(25.0, 60.0);
        generate_random_time(start, 7, 10);
        generate_random_time(end, 16, 20);
        float pos_x = generate_random_float(0.0, 10.0);
        float pos_y = generate_random_float(0.0, 10.0);
        int speciality = rand() % 2;

        fprintf(file, "%s,%d,%.2f,%.2f,%s,%s,%.2f,%.2f,%d\n",
                id, type, capacity_volume, capacity_weight,
                start, end, pos_x, pos_y, speciality);
    }
    fclose(file);
}

void create_random_databases(int num_deliveries, int num_vehicles)
{
    // Generar entregas y vehículos con valores predeterminados
    generate_random_deliveries_csv(num_deliveries);
    generate_random_vehicles_csv(num_vehicles);

    // Mostrar mensaje de éxito
    fprintf(stdout, GREEN_COLOR "\nBases de datos generadas con exito.\n\n" RESET_COLOR);
}
