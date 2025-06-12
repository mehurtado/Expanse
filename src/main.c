#include <stdio.h>
#include "simulation.h"

int main() {
    SimulationState state;
    state.particle_count = 1;
    state.current_time = 0.0;

    // Initialize our single particle at the origin with no initial velocity
    state.particles[0] = (Particle){
        .id = 1,
        .mass = 1.0,
        .position = {0.0, 0.0, 0.0},
        .velocity = {0.0, 0.0, 0.0}
    };

    double dt = 0.1; // Timestep of 0.1 seconds
    int num_steps = 20;

    printf("Starting simulation...\n");
    printf("Step | Time | Y-Position\n");
    printf("-----|------|-----------\n");

    for (int i = 0; i <= num_steps; i++) {
        // Print current state
        printf("%4d | %4.1f | %9.4f\n", i, state.current_time, state.particles[0].position[1]);

        // Advance the simulation
        simulation_step(&state, dt);
    }

    return 0;
}