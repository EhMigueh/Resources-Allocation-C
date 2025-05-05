#include "header.h"

// Estrategia: Nearest Neighbor
void schedule_nearest_neighbor(Delivery *deliveries, int n_deliveries, Vehicle *vehicles, int n_vehicles)
{
    fprintf(stdout, "\n--- Estrategia: Nearest-Neighbor Scheduling ---\n\n");
    assign_vehicles_to_deliveries(deliveries, n_deliveries, vehicles, n_vehicles, NEAREST_NEIGHBOR);
}
