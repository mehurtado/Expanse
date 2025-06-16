// src/basis.c
#include "basis.h"
#include <math.h> // For sin() and cos()
#include <stdio.h> // For debugging
#include <string.h>
#include <unistd.h> // For write()
#include "milkyway/milkyway_math.h"

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
    const int stride = lmax + 1;

    // --- Part 1: Calculate P_l^m(x) ---
    // Base case P_0^0 = 1
    p[0] = 1.0;

    if (lmax == 0) return;

    // Calculate diagonal terms P_m^m
    p[1 * stride + 1] = -mw_sqrt((1.0 - x) * (1.0 + x));
    for (int m = 2; m <= lmax; m++) {
        p[m * stride + m] = (2.0 * m - 1.0) * p[1 * stride + 1] / (-m) * p[(m - 1) * stride + (m - 1)];
    }
    
    // Calculate the first column (m=0)
    p[1 * stride + 0] = x; // Handle l=1 case separately
    for (int l = 2; l <= lmax; l++) {
        p[l * stride + 0] = ((2.0 * l - 1.0) * x * p[(l - 1) * stride + 0] - (l - 1.0) * p[(l - 2) * stride + 0]) / l;
    }

    // Use recurrence relation to calculate all other terms
    for (int l = 2; l <= lmax; l++) {
        for (int m = 1; m < l; m++) {
            p[l * stride + m] = ((2.0 * l - 1.0) * x * p[(l - 1) * stride + m] - (l + m - 1.0) * p[(l - 2) * stride + m]) / (l - m);
        }
    }

    // --- Part 2: Calculate dP/dx ---
    if (dp == NULL) {
        return; // Skip derivative calculation if not needed
    }
    
    dp[0] = 0.0;
    if (lmax == 0) return;
    
    for (int l = 1; l <= lmax; l++) {
        for (int m = 0; m < l; m++) {
            dp[l * stride + m] = ((l * x * p[l * stride + m] - (l + m) * p[(l - 1) * stride + m]) / (x * x - 1.0));
        }
        dp[l * stride + l] = (l * x * p[l * stride + l] - (l + l) * p[(l - 1) * stride + l]) / (x * x - 1);
    }
}