#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <time.h>
#include <stdbool.h>

#include "models.h"
#include "enums.h"

// Auxiliares
float calculate_distance(float, float, float, float);
int time_to_minutes(const char *);
float calculate_gasoline_by_type(int);
void show_metrics(float, float, float, int, float, int, double, int, int, float);
int show_vehicles(Vehicle *, int);
void show_deliveries(Delivery *, int);
float calculate_satisfaction(Delivery *, int, int);
bool has_time_conflict(Delivery *, int, Delivery *);

// Generación de CSV
void generate_random_time(char *, int, int);
float generate_random_float(float, float);
void generate_random_deliveries_csv();
void generate_random_vehicles_csv();
void create_random_databases();
void export_to_csv(const char *, Delivery *, int);

#endif