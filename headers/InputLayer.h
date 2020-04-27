#ifndef INPUT_LAYER_H
#define INPUT_LAYER_H

#include "Layer.h"

class InputLayer : public Layer {
public:
    InputLayer(std::vector<double> *inputs);

    void calculate_output() override;

    ~InputLayer();
};

#endif