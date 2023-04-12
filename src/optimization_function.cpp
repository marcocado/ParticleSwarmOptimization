/**
 * Function name: Optimization Function
 * 
 * Description: The function of the optimization problem. As an example we use a simple test function
 * 
 * Parameters:
 * - x: x-Value
 * - y: y-Value
 * 
 * Return value: z
 */
double optimization_function(double x, double y){
    return pow(x - 2.0, 2.0) + pow(y + 4.0, 2.0);
}

std::vector<std::vector<double>> calculate_coordinate_array(std::vector<std::vector<double>> input_vector){
    int iterator_end = input_vector.size();
    for(int i = 0; i != iterator_end; i++){
        input_vector[2][i] = fitness_function(input_vector[0][i], input_vector[1][i]);
    }
    return input_vector;
}

/**
 * Function name: Coordinate Calculation
 * 
 * Description: Calculates the z-Value with the Fitness Function
 * 
 * Parameters:
 * - input_vector: Vector containing x, y, z of a point
 * 
 * Return value: input_vector with the calculated z value
 */
std::vector<double> calculate_coordinate(std::vector<double> input_vector){
    input_vector[2] = fitness_function(input_vector[0], input_vector[1]);
    return input_vector;
}