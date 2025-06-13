// src/bfe.c
#include "bfe.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

// Creates a BFEModel from a file
BFEModel* bfe_create_from_file(const char* filename) {
    // TODO: Implement the real BFE model loading from file.
    return NULL;
}

// Destroys given BFEModel and frees resources
void bfe_destroy(BFEModel* model) {
    if (!model) return;
    if (model->S_coeffs) {
        free(model->S_coeffs);
    }
    if (model->T_coeffs) {
        free(model->T_coeffs);
    }
    free(model);
}

// Calculates force at a given position using the BFE model
void bfe_calculate_force(double pos[3], const BFEModel* model, double* force_out) {
    // TODO: Implement the real BFE math here.
    if (model == NULL) {
        force_out[0] = 0.0;
        force_out[1] = 0.0;
        force_out[2] = 0.0;
        return;
    }

    force_out[0] = 0.0;
    force_out[1] = 0.0;
    force_out[2] = 0.0;
}

// Evolves the BFE coefficients based on particle positions and velocities
// MAKE TOGGLEABLE (Dynamic vs. Static BFE)
void bfe_evolve_coeffs(BFEModel* model, const Particle particles[], int num_particles, double dt) {
    // TODO: Implement the real BFE coefficient evolution logic.
    return;
}