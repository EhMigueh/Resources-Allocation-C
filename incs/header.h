#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <time.h>

#define MAX_ID_LENGTH 10
#define MAX_LINE_LENGTH 256
#define FLEXIBILITY_MINUTES 60

// Estructura que representa una entrega
typedef struct
{
    char id[MAX_ID_LENGTH]; // ID de la entrega
    float origin_x;         // Coordenadas de origen X
    float origin_y;         // Coordenadas de origen Y
    float destination_x;    // Coordenadas de destino X
    float destination_y;    // Coordenadas de destino Y
    char start[6];          // Hora de inicio en formato HH:MM
    char end[6];            // Hora de fin en formato HH:MM
    int duration;           // Duración de la entrega en minutos
    int priority;           // Prioridad de la entrega (1-5)
    int vehicle_type;       // Tipo de vehículo (1-3)
    float volume;           // Volumen de la entrega
    float weight;           // Peso de la entrega

} Delivery;

// Estructura que representa un vehículo

typedef struct
{
    char id[MAX_ID_LENGTH];
    int type;
    float capacity_volume; // Capacidad actual de volumen
    float capacity_weight; // Capacidad actual de peso
    float original_volume; // Capacidad original de volumen
    float original_weight; // Capacidad original de peso
    char start[6];
    char end[6];
    float pos_x;
    float pos_y;
    int speciality;
} Vehicle;

// Funciones de errores.
void error_load_delivery(int);
void error_load_vehicle(int, Delivery *);
void error_open_file(FILE *, const char *);
void error_malloc_delivery(Delivery *, FILE *);
void error_malloc_vehicle(Vehicle *, FILE *);

// Funciones auxiliares.
void delete_line_leap(char *);

// Funciones de carga de datos.
int load_delivery(const char *, Delivery **);
int load_vehicle(const char *, Vehicle **);
void export_assignments_to_csv(const char *filename, Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles);
void export_metrics_to_csv(const char *filename, int completed_deliveries, int total_deliveries, float total_distance, float total_wait_time, double execution_time);

// Funciones relacionadas con vehículos.
void validate_vehicle_data(Vehicle *, int);
void assign_vehicles_to_deliveries(Delivery *, int, Vehicle *, int);
float calculate_total_distance(Vehicle *, int, Delivery *, int);
float calculate_distance(float x1, float y1, float x2, float y2);
void simulate_delays(Delivery *deliveries, int n_deliveries, int delay_minutes);
void calculate_vehicle_utilization(Vehicle *vehicles, int n_vehicles);

// Funciones nuevas.
void schedule_edf(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles);
void schedule_spt(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles);
void schedule_priority(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles);
void schedule_nearest_neighbor(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles);

int compare_by_end(const void *a, const void *b);
int compare_by_duration(const void *a, const void *b);
int compare_by_priority(const void *a, const void *b);