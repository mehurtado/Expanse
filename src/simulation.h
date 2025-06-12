#ifndef SIMULATION_H
#define SIMULATION_H

#include "particle.h"

#define MAX_PARTICLES 128 // A simple, fixed-size array for now

typedef struct {
    Particle particles[MAX_PARTICLES];
    int particle_count;
    double current_time;
} SimulationState;

// This is the main function that will advance the simulation by one step
void simulation_step(SimulationState* state, double dt);

// Ths function initializes the simulation state
void load_simulation_state(const char* filename, SimulationState* state);

// This function applies forces to all particles based on their current positions
void apply_forces(SimulationState* state);

#endif // SIMULATION_H