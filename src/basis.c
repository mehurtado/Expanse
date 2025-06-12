// src/basis.c
#include "basis.h"
#include <math.h> // For sin() and cos()

void basis_sincos(int mmax, double phi, double* c, double* s) {
    c[0] = 1.0;
    s[0] = 0.0;

    if (mmax > 0) {
        c[1] = cos(phi);
        s[1] = sin(phi);

        for (int m = 2; m <= mmax; m++) {
            // Use the trig recurrence relations
            c[m] = 2.0 * c[1] * c[m-1] - c[m-2];
            s[m] = 2.0 * c[1] * s[m-1] - s[m-2];
        }
    }
}

void basis_legendre(int lmax, double x, double* p) {
    // TODO: Implement the Legendre polynomial calculation
}