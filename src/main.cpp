#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <random>
#include <fstream>

#include "fitness_function.cpp"
#include "random_generator.cpp"
#include "solver.cpp"

int main(void){

    // Declare start parameters
    int count_particles = 40;
    int vector_size = 3;
    double tolerance = 0.05;
    double inertia = 0.5;
    double social_weight_factor = 4.3;
    double cognitive_weight_factor = 3.3;
    double min_coordinate = -10.0;
    double max_coordinate = 10.0;

    // Setup of the Particle Swarm Algorithm Solver
    Solver solver(count_particles, vector_size, tolerance, inertia, social_weight_factor, cognitive_weight_factor, min_coordinate, max_coordinate);

    // Start the solving process
    solver.run();

    return 0;
}