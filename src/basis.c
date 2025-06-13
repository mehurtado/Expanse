// src/basis.c
#include "basis.h"
#include <math.h> // For sin() and cos()
#include "milkyway_math_double.h"

void basis_sincos(int mmax, double phi, double* c, double* s) {
    c[0] = 1.0;
    s[0] = 0.0;

    if (mmax > 0) {
        c[1] = mw_cos(phi); // Using MW@H's math functions
        s[1] = mw_sin(phi);

        for (int m = 2; m <= mmax; m++) {
            c[m] = 2.0 * c[1] * c[m-1] - c[m-2];
            s[m] = 2.0 * c[1] * s[m-1] - s[m-2];
        }
    }
}

void basis_legendre_deriv(int lmax, double x, double* p, double* dp) {
    // TODO: Implement the Legendre polynomial and derivative calculation
}