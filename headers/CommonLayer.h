#ifndef COMMON_LAYER_H
#define COMMON_LAYER_H

#include "Layer.h"

#define WEIGHTS_DEFAULT_CONSTANT 0.5

class CommonLayer : public Layer {
public:
    CommonLayer(std::vector<double> *inputs, size_t layer_neuron_count);
    
    ~CommonLayer();

    void calculate_output() override;

    friend class Network;
private:
    std::vector<std::vector<double> > *weights;
};

#endif