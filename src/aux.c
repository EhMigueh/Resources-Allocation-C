#include "header.h"

// Menú principal para seleccionar la estrategia de scheduling (TEMPORAL)
void menu_scheduling()
{
    fprintf(stdout, "\nSeleccione la estrategia de scheduling:\n\n");
    fprintf(stdout, "1. Earliest Deadline First (EDF)\n");
    fprintf(stdout, "2. Shortest Processing Time (SPT)\n");
    fprintf(stdout, "3. Priority-Based Scheduling\n");
    fprintf(stdout, "4. Nearest Neighbor\n");
    fprintf(stdout, "\nIngrese su elección: ");
}

// Print para probar si se cargaron las entregas y vehículos correctamente
void print_deliveries_and_vehicles(Delivery *deliveries, Vehicle *vehicles, int n_deliveries, int n_vehicles)
{
    // Mostrar las entregas cargadas
    fprintf(stdout, "\n--- Entregas cargadas ---\n");
    for (int i = 0; i < n_deliveries; i++)
    {
        fprintf(stdout, "Entrega %d: %s\n", i + 1, deliveries[i].id);
        fprintf(stdout, "  Origen: (%.2f, %.2f)\n", deliveries[i].origin_x, deliveries[i].origin_y);
        fprintf(stdout, "  Destino: (%.2f, %.2f)\n", deliveries[i].destination_x, deliveries[i].destination_y);
        fprintf(stdout, "  Hora de inicio: %s\n", deliveries[i].start);
        fprintf(stdout, "  Hora de fin: %s\n", deliveries[i].end);
        fprintf(stdout, "  Duración: %d minutos\n", deliveries[i].duration);
        fprintf(stdout, "  Prioridad: %d\n", deliveries[i].priority);
        fprintf(stdout, "  Tipo de vehículo: %d\n", deliveries[i].vehicle_type);
        fprintf(stdout, "  Volumen: %.2f\n", deliveries[i].volume);
        fprintf(stdout, "  Peso: %.2f\n", deliveries[i].weight);
    }

    // Mostrar los vehículos cargados
    fprintf(stdout, "\n--- Vehículos cargados ---\n");
    for (int i = 0; i < n_vehicles; i++)
    {
        fprintf(stdout, "Vehículo %d: %s\n", i + 1, vehicles[i].id);
        fprintf(stdout, "  Tipo: %d\n", vehicles[i].type);
        fprintf(stdout, "  Capacidad de volumen: %.2f\n", vehicles[i].capacity_volume);
        fprintf(stdout, "  Capacidad de peso: %.2f\n", vehicles[i].capacity_weight);
        fprintf(stdout, "  Hora de inicio: %s\n", vehicles[i].start);
        fprintf(stdout, "  Hora de fin: %s\n", vehicles[i].end);
        fprintf(stdout, "  Posición: (%.2f, %.2f)\n", vehicles[i].pos_x, vehicles[i].pos_y);
        fprintf(stdout, "  Especialidad: %d\n", vehicles[i].speciality);
    }
}