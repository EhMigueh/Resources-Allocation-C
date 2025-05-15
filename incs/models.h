#ifndef MODELS_H
#define MODELS_H

#include "constants.h"

// Estructura que representa una entrega
typedef struct
{
    char id[MAX_ID_LENGTH];   // ID de la entrega
    float origin_x;           // Coordenadas de origen X
    float origin_y;           // Coordenadas de origen Y
    float destination_x;      // Coordenadas de destino X
    float destination_y;      // Coordenadas de destino Y
    char start[6];            // Hora de inicio en formato HH:MM
    char end[6];              // Hora de fin en formato HH:MM
    int duration;             // Duración de la entrega en minutos
    int priority;             // Prioridad de la entrega (1-5)
    int vehicle_type;         // Tipo de vehículo (1-3)
    float volume;             // Volumen de la entrega
    float weight;             // Peso de la entrega
    char vehicle_assigned[5]; // ID del vehículo asignado
    float distance;           // Distancia recorrida
    float liters_used;        // Litros de combustible usados
    int user_satisfaction;
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
    int deliveries_assigned; // Campo para la optimizacion -> balanceo de carga
} Vehicle;

#endif
