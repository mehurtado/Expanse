#ifndef SIMULATION_H
#define SIMULATION_H

#include "particle.h"
#include "bfe.h"

#define MAX_PARTICLES 128 // A simple, fixed-size array for now

typedef struct {
    Particle particles[MAX_PARTICLES];
    BFEModel* model;
    int particle_count;
    double current_time;
} SimulationState;

// Creates a new SimulationState object
SimulationState* simulation_create();

// Destroys the SimulationState object and frees resources
void simulation_destroy(SimulationState* state);

// This is the main function that will advance the simulation by one step
void simulation_step(SimulationState* state, double dt);

// Ths function initializes the simulation state
int simulation_load_particles(SimulationState* state, const char* filename);

// This function applies forces to all particles based on their current positions
void apply_forces(SimulationState* state);

#endif // SIMULATION_H