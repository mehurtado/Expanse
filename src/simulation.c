// src/simulation.c
#include "simulation.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

// Gravitational constant and a central mass at the origin
const double G = 6.67430e-11;
const double M_central = 1.989e30; // Mass of the Sun

// Calculates forces and updates particle accelerations
void apply_forces(SimulationState* state) {
    for (int i = 0; i < state->particle_count; i++) {
        Particle* p = &state->particles[i];

        double r_vec[3] = {-p->position[0], -p->position[1], -p->position[2]};
        double r_mag = sqrt(r_vec[0]*r_vec[0] + r_vec[1]*r_vec[1] + r_vec[2]*r_vec[2]);

        if (r_mag < 1e-9) continue; // Avoid division by zero at the center

        double f_mag = (G * M_central * p->mass) / (r_mag * r_mag);
        double f_vec[3] = {f_mag * r_vec[0]/r_mag, f_mag * r_vec[1]/r_mag, f_mag * r_vec[2]/r_mag};

        // a = F/m
        p->acceleration[0] = f_vec[0] / p->mass;
        p->acceleration[1] = f_vec[1] / p->mass;
        p->acceleration[2] = f_vec[2] / p->mass;
    }
}

// Updates positions and velocities using the Velocity Verlet algorithm
void update_particles(SimulationState* state, double dt) {
    for (int i = 0; i < state->particle_count; i++) {
        Particle* p = &state->particles[i];

        // 1. Update position: p_new = p_old + v * dt + 0.5 * a * dt^2
        p->position[0] += p->velocity[0] * dt + 0.5 * p->acceleration[0] * dt * dt;
        p->position[1] += p->velocity[1] * dt + 0.5 * p->acceleration[1] * dt * dt;
        p->position[2] += p->velocity[2] * dt + 0.5 * p->acceleration[2] * dt * dt;

        // Store old acceleration before recalculating
        double old_accel[3];
        memcpy(old_accel, p->acceleration, sizeof(old_accel));

        // We will recalculate forces/accelerations at the new position
        // For now, we assume it's done externally. We will do this in simulation_step.
        // (A placeholder for the force update)

        // 2. Update velocity: v_new = v_old + 0.5 * (a_old + a_new) * dt
        // We will complete this in the main step function.
    }
}

// The main simulation step using the Velocity Verlet algorithm
void simulation_step(SimulationState* state, double dt) {
    // First half-step velocity update
    for (int i = 0; i < state->particle_count; i++) {
        Particle* p = &state->particles[i];
        p->velocity[0] += 0.5 * p->acceleration[0] * dt;
        p->velocity[1] += 0.5 * p->acceleration[1] * dt;
        p->velocity[2] += 0.5 * p->acceleration[2] * dt;
    }

    // Update positions to full step
    for (int i = 0; i < state->particle_count; i++) {
        Particle* p = &state->particles[i];
        p->position[0] += p->velocity[0] * dt;
        p->position[1] += p->velocity[1] * dt;
        p->position[2] += p->velocity[2] * dt;
    }

    // Calculate new forces/accelerations at the new positions
    apply_forces(state);

    // Second half-step velocity update
    for (int i = 0; i < state->particle_count; i++) {
        Particle* p = &state->particles[i];
        p->velocity[0] += 0.5 * p->acceleration[0] * dt;
        p->velocity[1] += 0.5 * p->acceleration[1] * dt;
        p->velocity[2] += 0.5 * p->acceleration[2] * dt;
    }

    state->current_time += dt;
}

// New function to load state from a file
void load_simulation_state(const char* filename, SimulationState* state) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening initial conditions file");
        state->particle_count = 0;
        return;
    }

    state->particle_count = 0;
    double m, px, py, pz, vx, vy, vz;
    while (fscanf(file, "%lf %lf %lf %lf %lf %lf %lf", &m, &px, &py, &pz, &vx, &vy, &vz) == 7) {
        if (state->particle_count < MAX_PARTICLES) {
            int i = state->particle_count;
            state->particles[i] = (Particle){.id = i+1, .mass = m, .position = {px, py, pz}, .velocity = {vx, vy, vz}};
            state->particle_count++;
        }
    }
    fclose(file);
}