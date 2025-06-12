// src/bfe.h
#ifndef BFE_H
#define BFE_H

typedef struct {
    int nmax; // Max expansion order
    int lmax;
    double scale_radius; // A scaling factor 'a'
    double* S_coeffs;    // Pointer to sine coefficients
    double* T_coeffs;    // Pointer to cosine coefficients
} BFEModel;

// We'll also declare the main force function prototype
void bfe_calculate_force(double pos[3], const BFEModel* model, double* force_out);

#endif // BFE_H