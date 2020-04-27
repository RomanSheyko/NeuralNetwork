#ifndef NETWORK_H
#define NETWORK_H

#include "Layer.h"

class Network {
public:
    Network(std::vector<double> *inputs);
    ~Network();
    void addLayer(size_t network_size);
    void deleteLastLayer();
    const std::vector<double>& getOutput() const;
    void calculateOutput();
    void evalutionLearning(size_t population, std::vector<std::vector<double>*> *input_data, std::vector<std::vector<double>*> *answers);
private:
    std::vector<Layer*> *layers;
};

#endif