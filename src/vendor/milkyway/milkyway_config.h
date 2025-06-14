// src/vendor/milkyway/milkyway_config.h
// This is a custom, simplified config for the Expanse project.

#ifndef MW_CONFIG_H
#define MW_CONFIG_H

// Define the alignment macro for GCC/Clang compilers
#define MW_ALIGN_TYPE_V(n) __attribute__((aligned(n)))

// Define compatibility macros
#define CONST_F const

// Standard Settings
#define DOUBLEPREC 1
#define HAVE_SINCOS 1
#define HAVE_UNISTD_H 1
#define HAVE_STDINT_H 1
#define HAVE_MALLOC_H 1
#define HAVE_EXP10 1
#define HAVE_EXP2 1
#define HAVE_FMAX 1
#define HAVE_FMIN 1

#endif // MW_CONFIG_H