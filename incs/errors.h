#ifndef ERRORS_H
#define ERRORS_H

#include "util.h"
#include "models.h"
#include "enums.h"

// Funciones de errores
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
void error_invalid_argc(int);
void error_invalid_numbers(char *, char *, int, int);
void error_vehicle_entries(int);
void error_delivery_entries(int);
void error_exec_python(void);

#endif
