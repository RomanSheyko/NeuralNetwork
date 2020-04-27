#include "Layer.h"
#include <cmath>

Layer::Layer(std::vector<double> *inputs, size_t layer_neuron_count) {
    this->inputs = inputs;
    this->calculated = false;
    this->layer_neuron_count = layer_neuron_count;
    this->outputs = new std::vector<double>;
    this->outputs->resize(layer_neuron_count);
}

Layer::~Layer() {
    delete outputs;
}

bool Layer::is_calculated() {
    return calculated;
}

double Layer::f(double x) {
    //TODO: replace to f(x) = 0.5 * (x / (1 + abs(x))) + 0.5 or other function approximated to sigmoid
    return 1/(1+exp(-x));
}