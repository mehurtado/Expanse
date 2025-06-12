// src/bfe.c
#include "bfe.h"
#include <stddef.h>

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