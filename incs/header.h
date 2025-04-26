#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_LENGTH 10
#define MAX_LINE_LENGTH 256

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
    char id[MAX_ID_LENGTH]; // ID del vehículo
    int type;               // Tipo de vehículo (1-3)
    float capacity_volume;  // Capacidad del vehículo en volumen
    float capacity_weight;  // Capacidad del vehículo en peso
    char start[6];          // Hora de inicio en formato HH:MM
    char end[6];            // Hora de fin en formato HH:MM
    float pos_x;            // Coordenadas de origen X
    float pos_y;            // Coordenadas de origen Y
    int speciality;         // Especialidad del vehículo (1-3)
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

//