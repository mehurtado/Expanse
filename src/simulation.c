#include "simulation.h"

// This function calculates the forces on each particle.
// For now, we'll use a simple, constant downward gravity as a test.
void calculate_forces(SimulationState* state) {
    // Constant downward acceleration (e.g., -9.8 m/s^2 in the y-direction)
    const double gravity[3] = {0.0, -9.8, 0.0};

    for (int i = 0; i < state->particle_count; i++) {
        // F = m * a  =>  a = F / m
        // Here we are calculating acceleration from the force field.
        // Since our "force" is just constant gravity (an acceleration),
        // we apply it directly, ignoring mass for this simple test.

        // We'll store the calculated acceleration temporarily in the velocity update logic.
        // A more robust engine might have an `acceleration[3]` field in the Particle struct.
    }
}

// This function updates particle positions and velocities based on forces.
void update_particles(SimulationState* state, double dt) {
    const double gravity[3] = {0.0, -9.8, 0.0}; // Same as above

    for (int i = 0; i < state->particle_count; i++) {
        // Update velocity: v_new = v_old + a * dt
        state->particles[i].velocity[0] += gravity[0] * dt;
        state->particles[i].velocity[1] += gravity[1] * dt;
        state->particles[i].velocity[2] += gravity[2] * dt;

        // Update position: p_new = p_old + v_new * dt
        state->particles[i].position[0] += state->particles[i].velocity[0] * dt;
        state->particles[i].position[1] += state->particles[i].velocity[1] * dt;
        state->particles[i].position[2] += state->particles[i].velocity[2] * dt;
    }
}

// This is the main public function that runs one step.
void simulation_step(SimulationState* state, double dt) {
    // In a more complex simulation, calculate_forces would be called first.
    // For our simple test, all logic is in update_particles.
    update_particles(state, dt);

    state->current_time += dt;
}