#include "pso.cpp"

/**
 * Class name: Solver
 * 
 * Description: Wrapper of the main Particle Swarm Algorithm. Initializes all important parameters and starts
 * the iterative solving process.
 * 
 * Public members:
 * - max_iteration: after how many iterations the solving process stops, when no satisfying solution is found yet
 * - count_particles: number of particles used for the solving process
 * - vector_size: 3 for a 3-Dimensional Problem
 * - tolerance: tolerance as a termination criteria
 * - inertia: factor for the inertia
 * - social_weight_factor: factor to follow the global dynamic
 * - cognitive_weight_factor: factor to follow the individual dynamic
 * - min_coordinate: minimum range of the x and y values
 * - max_coordinate: minimum range of the x and y values
 */
class Solver {
    public:
        int max_iteration;
        int count_particles;
        int vector_size;
        double tolerance;
        double inertia;
        double social_weight_factor;
        double cognitive_weight_factor;
        double min_coordinate;
        double max_coordinate;

        Solver( const int& init_count_particles, const int& init_vector_size, const double& init_tolerance, 
                const double& init_inertia, const double& init_social_weight_factor, const double& init_cognitive_weight_factor, 
                const double& init_min_coordinate, const double& init_max_coordinate){
            max_iteration = 10;
            count_particles = init_count_particles;
            vector_size = init_vector_size;
            tolerance = init_tolerance;
            inertia = init_inertia;
            social_weight_factor = init_social_weight_factor;
            cognitive_weight_factor = init_cognitive_weight_factor;
            min_coordinate = init_min_coordinate;
            max_coordinate = init_max_coordinate;
        };

    public:
        /**
         * Method name: Run
         * 
         * Description: starts the solving process
         */
        void run(){
            // Initialize the swarm
            Swarm swarm(vector_size, tolerance, inertia, social_weight_factor, cognitive_weight_factor);
            swarm.initialize_particles(count_particles, min_coordinate, max_coordinate);

            // Start the solving process
            int i = 0;
            bool tolerance_reached;
            do{
                tolerance_reached = swarm.update_particles();
                i++;
            }while(i != max_iteration and tolerance_reached == false);

            // Print the global best coordinate at the terminal
            std::cout << swarm.global_best_coordinate[0] << "   " << swarm.global_best_coordinate[1];
        }
};
