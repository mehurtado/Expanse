#include <stdio.h>
#include "simulation.h"

int main() {
    SimulationState state;
    state.current_time = 0.0;

    load_simulation_state("init.txt", &state);

    if (state.particle_count == 0) {
        printf("Failed to load particles. Exiting.\n");
        return 1;
    }

    printf("Loaded %d particle(s).\nStarting simulation...\n", state.particle_count);

    double dt = 3600 * 24; // Timestep of one day in seconds
    int num_steps = 365;

    // Initial force calculation
    apply_forces(&state);

    for (int i = 0; i <= num_steps; i++) {
        if (i % 10 == 0) { // Print output every 10 steps
             printf("Day %3d: Pos=(%.2e, %.2e, %.2e)\n", i, state.particles[0].position[0], state.particles[0].position[1], state.particles[0].position[2]);
        }
        simulation_step(&state, dt);
    }

    return 0;
}