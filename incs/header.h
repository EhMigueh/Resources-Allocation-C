#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <time.h>

#define MAX_ID_LENGTH 10
#define MAX_LINE_LENGTH 256
#define FLEXIBILITY_MINUTES 60
#define MAX_NUM_DELIVERIES 15
#define MAX_NUM_VEHICLES 15

#define RESET_COLOR "\x1b[0m"
#define RED_COLOR "\x1b[31m"
#define YELLOW_COLOR "\x1b[33m"
#define CYAN_COLOR "\x1b[36m"
#define GREEN_COLOR "\x1b[32m"

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

// Tipos de datos para la carga de datos
typedef enum
{
    DATA_DELIVERY,
    DATA_VEHICLE,
} DataType;

// Funciones relacionadas con el manejo de los comandos
void show_help();
void process_command(int, char *argv[], Delivery *, int, Vehicle *, int);

// Funciones de carga de datos.
int load_csv_data(const char *, void **, DataType);
int parse_delivery(char *, Delivery *);
int parse_vehicle(char *, Vehicle *);
void delete_line_leap(char *);
void validate_vehicle_data(Vehicle *, int);

// Funciones Earliest Deadline First
void schedule_edf(Delivery *, int, Vehicle *, int);
int compare_deadlines(const void *, const void *);
void assign_edf(Delivery *, int, Vehicle *, int);

// Funciones Priority-Based
void schedule_based_priority(Delivery *, int, Vehicle *, int);
int compare_by_priority(const void *, const void *);

// Funciones Nearest Neighbor
void schedule_nearest_neighbor(Delivery *, int, Vehicle *, int);

// Funciones de ordenamiento.
void swap(Delivery *, Delivery *);
int partition(Delivery *, int, int, SchedulingMode);
void custom_qsort(Delivery *, int, int, SchedulingMode);

// Funciones dedicadas a la asignación de vehículos
void assign_vehicles_to_deliveries(Delivery *, int, Vehicle *, int, SchedulingMode);

// Funciones auxiliares
float calculate_distance(float, float, float, float);
int time_to_minutes(const char *);
void calculate_total_distance(Vehicle *, int, Delivery *, int);
void calculate_vehicle_utilization(Vehicle *, int);

// Funciones dedicadas a la creación de CSV
void generate_random_time(char *, int, int);
float generate_random_float(float, float);
void generate_random_deliveries_csv();
void generate_random_vehicles_csv();
void create_random_databases();

// Funciones de errores.
void fatal_error(const char *, const char *, const char *);
void error_open_file(FILE *, const char *);
void error_create_file(FILE *, const char *);
void error_load_data(int, DataType, Delivery *);
void error_malloc(Delivery *, Vehicle *, FILE *, DataType);
void error_read_header(FILE *, Delivery *, Vehicle *, DataType, char *);
void error_format(const char *, const char *);
void error_parse(int, const char *, DataType);
void error_vehicle_capacity(void);
void error_vehicle_type(void);
void error_no_arguments(void);
void error_invalid_option(void);

// NI IDEA DE DÓNDE SALE ESTO...
/*
void export_assignments_to_csv(const char *, Delivery *, int, Vehicle *, int);
void export_metrics_to_csv(const char *, int, int, float, float, double);

void simulate_delays(Delivery *, int, int);
*/
