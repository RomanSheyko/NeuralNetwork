#include "CommonLayer.h"

CommonLayer::CommonLayer(std::vector<double> *inputs, size_t layer_neuron_count) : Layer(inputs, layer_neuron_count) {
    this->weights = new std::vector<std::vector<double> >;
    this->weights->resize(this->layer_neuron_count);
    for(int i = 0; i < this->layer_neuron_count; i++) {
        (*weights)[i].resize(this->inputs->size());
        for(int j = 0; j < this->inputs->size(); j++)
            (*weights)[i][j] = WEIGHTS_DEFAULT_CONSTANT;
    }
}

CommonLayer::~CommonLayer() {
    delete weights;
}

void CommonLayer::calculate_output() {
    std::vector<double>& ref_outputs = *outputs;
    std::vector<double>& ref_inputs = *inputs;
    std::vector<std::vector<double> >& ref_weights = *weights;
    double output;
    for(int i = 0; i < layer_neuron_count; i++) {
        output = 0;
        for(int j = 0; j < ref_inputs.size(); j++) {
            output += ref_inputs[j] * ref_weights[i][j];
        }
        output = f(output);
        (*outputs)[i] = output;
    }
    this->calculated = true;
}