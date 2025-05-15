#ifndef ENUMS_H
#define ENUMS_H

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
#endif
