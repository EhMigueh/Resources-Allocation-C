#include "header.h"

void menu_scheduling()
{
    fprintf(stdout, "\nSeleccione la estrategia de scheduling:\n");
    fprintf(stdout, "1. Earliest Deadline First (EDF)\n");
    fprintf(stdout, "2. Shortest Processing Time (SPT)\n");
    fprintf(stdout, "3. Priority-Based Scheduling\n");
    fprintf(stdout, "4. Nearest Neighbor\n");
    fprintf(stdout, "Ingrese su elección: ");
}