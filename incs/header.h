#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <time.h>

#define MAX_ID_LENGTH 10
#define MAX_LINE_LENGTH 256
#define FLEXIBILITY_MINUTES 60

#define RESET_COLOR "\x1b[0m"
#define RED_COLOR "\x1b[31m"
#define YELLOW_COLOR "\x1b[33m"

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
    int deliveries_assigned; // Este nuevo campo, es para la optimizacion de balanceo de carga
} Vehicle;

// Tipos de algoritmos
typedef enum
{
    NEAREST_NEIGHBOR,
    PRIORITY_BASED,
    EARLIEST_DEADLINE_FIRST,
} SchedulingMode;

// Funciones de errores.
void error_load_delivery(int);
void error_load_vehicle(int, Delivery *);
void error_open_file(FILE *, const char *);
void error_malloc_delivery(Delivery *, FILE *);
void error_malloc_vehicle(Vehicle *, FILE *);
void error_read_top_delivery(FILE *, Delivery *);
void error_read_top_vehicle(FILE *, Vehicle *);
void error_selection_choice(Delivery *, Vehicle *);
void error_format_delivery(const char *);
void error_format_vehicle(const char *);
void error_parse_delivery(int, const char *);
void error_parse_vehicle(int, const char *);
void error_vehicle_capacity(void);
void error_vehicle_type(void);

// Funciones auxiliares.
void menu_scheduling(void);
void delete_line_leap(char *);
void validate_vehicle_data(Vehicle *, int);
int time_to_minutes(const char *);

// Funciones de carga de datos.
int load_delivery(const char *, Delivery **);
int load_vehicle(const char *, Vehicle **);

// Funciones relacionadas con vehículos.
void assign_vehicles_to_deliveries(Delivery *, int, Vehicle *, int, SchedulingMode);
void calculate_total_distance(Vehicle *, int, Delivery *, int);
float calculate_distance(float, float, float, float);
void simulate_delays(Delivery *, int, int);
void calculate_vehicle_utilization(Vehicle *, int);

// Funciones de ordenamiento.
void swap(Delivery *, Delivery *);
int partition_time(Delivery *, int, int);
void custom_qsort_time(Delivery *, int, int);
int partition_priority(Delivery *, int, int);
void custom_qsort_priority(Delivery *, int, int);

// Funciones Earliest Deadline First
void schedule_edf(Delivery *, int, Vehicle *, int);
int compare_deadlines(const void *, const void *);

// Funciones Priority-Based
void schedule_based_priority(Delivery *, int, Vehicle *, int);
int compare_by_priority(const void *, const void *);

// Funciones Nearest Neighbor
void schedule_nearest_neighbor(Delivery *, int, Vehicle *, int);

// NI IDEA DE DÓNDE SALE ESTO...
/*
void export_assignments_to_csv(const char *, Delivery *, int, Vehicle *, int);
void export_metrics_to_csv(const char *, int, int, float, float, double);

void sort_by_end(Delivery *, int);
int compare_by_end(const void *, const void *);

int compare_by_duration(const void *, const void *);
*/