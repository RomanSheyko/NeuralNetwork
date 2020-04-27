#include <iostream>
#include <vector>
#include "Network.h"

double randMToN(double M, double N)
{
    return M + (rand() / ( RAND_MAX / (N-M) ) ) ;  
}

int main(int argc, char *argv[]) {
    std::vector<double> input_array;
    input_array.resize(3);
    input_array[0] = 0;
    input_array[1] = 0;
    input_array[2] = 255;
    Network network(&input_array);
    network.addLayer(10);
    network.addLayer(3);
    //network.evalutionLearning(50, &data_set, &check_set);
    network.calculateOutput();
    for(int i = 0; i < network.getOutput().size(); i++) {
        std::cout << network.getOutput()[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}