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

        Solver(int input_count_particles, int input_vector_size, double input_tolerance, 
                    double input_inertia, double input_social_weight_factor, double input_cognitive_weight_factor, 
                    double input_min_coordinate, double input_max_coordinate){
            max_iteration = 40;
            count_particles = input_count_particles;
            vector_size = input_vector_size;
            tolerance = input_tolerance;
            inertia = input_inertia;
            social_weight_factor = input_social_weight_factor;
            cognitive_weight_factor = input_cognitive_weight_factor;
            min_coordinate = input_min_coordinate;
            max_coordinate = input_max_coordinate;
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

            // Create a csv file
            std::ofstream csv_file;
            csv_file.open("/home/marco/Projekte/ParticleSwarmOptimization/data/output.csv");

            // Start the solving process
            int i = 0;
            bool tolerance_reached;
            do{
                tolerance_reached = swarm.update_particles();
                i++;
            }while(i != max_iteration and tolerance_reached == false);

            // Close the csv file
            csv_file.close();

            // Print the global best coordinate at the terminal
            std::cout << swarm.global_best_coordinate[0] << "   " << swarm.global_best_coordinate[1];
        }
};