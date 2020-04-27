#include "InputLayer.h"

InputLayer::InputLayer(std::vector<double> *inputs) : Layer(inputs, inputs->size()) {}

void InputLayer::calculate_output() {
    for(int i = 0; i < inputs->size(); i++) {
        (*outputs)[i] = (f((*inputs)[i]));
    }
    calculated = true;
}

InputLayer::~InputLayer() = default;