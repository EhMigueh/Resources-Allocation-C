#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "models.h"
#include "enums.h"

// Comandos
void show_help();
void process_command(int, char *[], Delivery *, int *, Vehicle *, int *);

// Carga de datos
int load_csv_data(const char *, void **, DataType);
int parse_delivery(char *, Delivery *);
int parse_vehicle(char *, Vehicle *);
void delete_line_leap(char *);
void validate_vehicle_data(Vehicle *, int);

// Algoritmos
void schedule_edf(Delivery *, int, Vehicle *, int);
void schedule_pb(Delivery *, int, Vehicle *, int);
void schedule_nn(Delivery *, int, Vehicle *, int);

// Ordenamiento
void swap(Delivery *, Delivery *);
int partition(Delivery *, int, int, SchedulingMode);
void custom_qsort(Delivery *, int, int, SchedulingMode);

#endif
