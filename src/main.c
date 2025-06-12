#include <stdio.h>
#include "particle.h"

int main() {
    // Create an instance of our Particle struct on the stack
    Particle p1;
    p1.id = 1;
    p1.mass = 1.0; // e.g., in solar masses
    p1.position[0] = 0.0; // x
    p1.position[1] = 0.0; // y
    p1.position[2] = 0.0; // z
    p1.velocity[0] = 0.0;
    p1.velocity[1] = 0.0;
    p1.velocity[2] = 0.0;

    printf("Created Particle ID %d:\n", p1.id);
    printf("  Mass: %f\n", p1.mass);
    printf("  Position: (%f, %f, %f)\n", p1.position[0], p1.position[1], p1.position[2]);
    printf("  Velocity: (%f, %f, %f)\n", p1.velocity[0], p1.velocity[1], p1.velocity[2]);

    return 0;
}