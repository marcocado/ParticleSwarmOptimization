/**
 * Class name: Particle
 * 
 * Description: Class of one Particle of the Swarm. This class has methods to update the three 
 * attributes of every particle. A particle is characterized by a coordinate, a velocity and
 * the best coordinate a individual particle has reached yet.
 * 
 * Public members:
 * - coordinate: location of the particle
 * - velocity: dynamic of the particle
 * - local_best_coordinate: best coordinate reached for the particle
 */
class Particle{
    public:
        std::vector<double> coordinate;
        std::vector<double> velocity;
        std::vector<double> local_best_coordinate;

        Particle(std::vector<double> input_coordinate, std::vector<double> input_velocity, std::vector<double> input_local_best_coordinate){
            coordinate = input_coordinate;
            velocity = input_velocity;
            local_best_coordinate = input_local_best_coordinate;
        };

    public:
        void update_velocity(int vector_size, double inertia, double cognitive_weight_factor, double social_weight_factor, std::vector<double> global_best_coordinate){
            double random_1 = generate_random_number(0.0, 0.4);
            double random_2 = generate_random_number(0.0, 0.4);
            for(int i = 0; i != vector_size-1; i++){
                velocity[i] = inertia*velocity[i] + cognitive_weight_factor*random_1*(local_best_coordinate[i] - coordinate[i]) + social_weight_factor*random_2*(global_best_coordinate[i] - coordinate[i]);
            }
        }

        void update_coordinate(int vector_size){
            for(int i = 0; i != vector_size-1; i++){
                coordinate[i] = coordinate[i] + velocity[i];
            }
            coordinate[vector_size-1] = fitness_function(coordinate[0], coordinate[1]);
        }

        std::vector<double> check_local_best_coordinate(int vector_size, std::vector<double> global_best_coordinate){
            if(coordinate[vector_size-1] < local_best_coordinate[vector_size-1]){
                local_best_coordinate = coordinate;
            }
            if(coordinate[vector_size-1] < global_best_coordinate[vector_size-1]){
                global_best_coordinate = coordinate;
            }
            return global_best_coordinate;
        }

        void print_coordinate(){
            for(auto & value : coordinate){
                std::cout << value << ";";
            }
        }

        void print_velocity(){
            for(auto & value : velocity){
                std::cout << value << ";";
            }
            std::cout << "\n";
        }

        std::string csv_print_coordinate(){
            return std::to_string(coordinate[0]) + ";" + std::to_string(coordinate[1]) + ";" + std::to_string(coordinate[2]) + ";";
        }

        std::string csv_print_velocity(){
            return std::to_string(velocity[0]) + ";" + std::to_string(velocity[1]) + ";" + std::to_string(velocity[2]) + "\n";
        }
};

/**
 * Class name: Swarm
 * 
 * Description: Class of the complete swarm, this class is the core of the Optimization Algorithm 
 * 
 * Public members:
 * - vector_size: 3 for a 3-Dimensional Problem
 * - tolerance: tolerance as a termination criteria
 * - inertia: factor for the inertia
 * - social_weight_factor: factor to follow the global dynamic
 * - cognitive_weight_factor: factor to follow the individual dynamic
 * - global_best_coordinate: best coordinate reached for all particles
 * - particles: vector of all particle instances
 */
class Swarm {
    public:
        int vector_size; 
        double tolerance;
        double inertia; 
        double social_weight_factor; 
        double cognitive_weight_factor;
        std::vector<double> global_best_coordinate; 
        std::vector<Particle> particles;

        Swarm(int input_vector_size, double input_tolerance, double input_inertia, 
            double input_social_weight_factor, double input_cognitive_weight_factor){
            vector_size = input_vector_size;
            tolerance = input_tolerance;
            inertia = input_inertia;
            social_weight_factor = input_social_weight_factor;
            cognitive_weight_factor = input_cognitive_weight_factor;
            global_best_coordinate = generate_random_vector(0.0, 1.0, input_vector_size);
            std::vector<Particle> default_particles;
            particles = default_particles;
        };
    
    public:
        /**
         * Method name: Initialize Particles
         * 
         * Description: Method to initialize all particles and append them at the end of the vector of the swarm
         */
        void initialize_particles(int count_particles, double min_coordinate, double max_coordinate){
            for(int i = 0; i != count_particles; i++){
                std::vector<double> current_coordinate = generate_random_vector(min_coordinate, max_coordinate, vector_size);
                current_coordinate = calculate_coordinate(current_coordinate);
                std::vector<double> current_velocity = generate_random_vector(0.0, 1.0, vector_size); //generate_random_vector(-1.0, 1.0, vector_size);
                std::vector<double> local_best_coordinate = current_coordinate;
                Particle current_particle(current_coordinate, current_velocity, local_best_coordinate);
                particles.push_back(current_particle);
            }
        }

        /**
         * Method name: Update Particles
         * 
         * Description: Method where all important methods for the solving process are executed. For every stepp the velocity and
         * coordinates are calculated at first. Afterwards, the method checks, if new local and global best coordinates are
         * found. Furthermore the method checks, if the tolerance is reached.
         */
        bool update_particles(){
            bool tolerance_readched;
            for(auto & current_particle : particles){
                current_particle.print_coordinate();
                current_particle.update_velocity(vector_size, inertia, social_weight_factor, cognitive_weight_factor, global_best_coordinate);
                current_particle.update_coordinate(vector_size);
                global_best_coordinate = current_particle.check_local_best_coordinate(vector_size, global_best_coordinate);
                if(current_particle.coordinate[vector_size-1] < tolerance){
                    tolerance_readched = true;
                }
                else{
                    tolerance_readched = false;
                }
                current_particle.print_velocity();
            }
            return tolerance_readched;
        }

        void print_coordinates(){
            for(auto & current_particle : particles){
                current_particle.print_coordinate(); 
            }
        }

        std::string csv_print(){
            std::string coordinate_line;
            std::string velocity_line;
            for(auto & current_particle : particles){
                coordinate_line = current_particle.csv_print_coordinate(); 
                velocity_line = current_particle.csv_print_velocity(); 
            }
            return coordinate_line + velocity_line;
        }
};