#ifndef LAYER_H
#define LAYER_H

#include <vector>

class Network;

class Layer {
public:
    Layer(std::vector<double> *inputs, size_t layer_neuron_count);

    virtual ~Layer();

    bool is_calculated();

    virtual void calculate_output() = 0;

    std::vector<double> *outputs;

    friend class Network;
protected:
    bool calculated;
    size_t layer_neuron_count;
    std::vector<double> *inputs;
    double f(double x);
};

#endif