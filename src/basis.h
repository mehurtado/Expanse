// src/basis.h
#ifndef BASIS_H
#define BASIS_H

// Calculates sin(m*phi) and cos(m*phi)
void basis_sincos(int mmax, double phi, double* c, double* s);

// Calculates both P_l^m(x) and their derivatives
void basis_legendre_deriv(int lmax, double x, double* p, double* dp);

#endif // BASIS_H