#include "Network.h"
#include "InputLayer.h"
#include "CommonLayer.h"
#include <cmath>

static double randMToN(double M, double N)
{
    return M + (rand() / ( RAND_MAX / (N-M) ) ) ;  
}

Network::Network(std::vector<double> *inputs) {
    this->layers = new std::vector<Layer*>;
    Layer *input_layer = new InputLayer(inputs);
    this->layers->push_back(input_layer);
}

Network::~Network() {
    for(auto layer : *layers) {
        delete layer;
    }
    delete layers;
}

void Network::addLayer(size_t network_size) {
    CommonLayer *layer = new CommonLayer((*layers)[layers->size() - 1]->outputs, network_size);
    layers->push_back(layer);
}

void Network::deleteLastLayer() {
    delete (*layers)[layers->size() - 1];
    layers->pop_back();
}

const std::vector<double>& Network::getOutput() const {
    return *((*layers)[layers->size() - 1]->outputs);
}

void Network::calculateOutput() {
    for(int i = 0; i < layers->size(); i++) {
        (*layers)[i]->calculate_output();
    }
}

void Network::evalutionLearning(size_t population_num, std::vector<std::vector<double>*> *input_data, std::vector<std::vector<double>*> *answers) {
    srand((unsigned)time(NULL));
    CommonLayer *common_layer;
    Network *pnet;
    std::vector<Network*> population;
    std::vector<double> mistakes;
    mistakes.resize(population_num);
    std::vector<double> input_set;
    input_set.resize(this->layers->at(0)->layer_neuron_count);
    for(int i = 0; i < population_num; i++) {
        //creating same network
        pnet = new Network(&input_set);
        for(int j = 1; j < this->layers->size(); j++) {
            pnet->addLayer(this->layers->at(j)->layer_neuron_count);
        }
        //set random weights on a new network
        for(int ii = 0; ii < pnet->layers->size(); ii++) {
            common_layer = dynamic_cast<CommonLayer*>((*pnet->layers)[ii]);
            if(common_layer != NULL) {
                for(int jj = 0; jj < common_layer->outputs->size(); jj++) {
                    for(int kk = 0; kk < common_layer->inputs->size(); kk++) {
                        common_layer->weights->at(jj)[kk] = randMToN(-1, 1);
                    }
                }
            }
        }
        //add new network to population
        population.push_back(pnet);
    }
    
    double min_mistake = 10, max_out, diff;
    int index, min_index, first_parent_index, second_parend_index;
    Network *pfirst;
    Network *psecond;
    for(int i = 0; i < input_data->size(); i++) {
        for(int j = 0; j < input_set.size(); j++) {
            input_set[j] = input_data->at(i)->at(j);
        }
        index = 0;
        //forming output and searching for a first parent at the same time
        for(Network* pnetwork : population) {
            pnetwork->calculateOutput();
            max_out = 0;
            for(int ii = 0; ii < pnetwork->getOutput().size(); ii++) {
                diff = abs(answers->at(i)->at(ii) - pnetwork->getOutput()[ii]);
                if(diff > max_out) max_out = diff;
            }
            mistakes[index] = max_out;
            if(max_out < min_mistake) {
                min_mistake = max_out;
                min_index = index;
            }
            index++;
        }
        first_parent_index = min_index;
        //searching for the next parent
        index = 0;
        min_mistake = 10;
        for(Network* pnetwork : population) {
            if(index != first_parent_index) {
                if(mistakes[index] < min_mistake) {
                    min_mistake = mistakes[index];
                    min_index = index;
                }
            }
            index++;
        }
        second_parend_index = min_index;
        //forming a new population
        for(Network* pnetwork : population) {
            if(pnetwork != population[first_parent_index] && pnetwork != population[second_parend_index]) {
                int genom_type = rand() % 4;
                switch(genom_type) {
                    case 0: 
                        pfirst = population[first_parent_index];
                        psecond = population[second_parend_index];
                        break;
                    case 1:
                        pfirst = population[second_parend_index];
                        psecond = population[first_parent_index];
                        break;
                    case 2:
                        pfirst = population[first_parent_index];
                        psecond = population[first_parent_index];
                        break;
                    default:
                        pfirst = population[second_parend_index];
                        psecond = population[second_parend_index];
                }
                for(int ii = 0; ii < pnetwork->layers->size(); ii++) {
                    common_layer = dynamic_cast<CommonLayer*>((*pnetwork->layers)[ii]);
                    CommonLayer* parent_layer;
                    if(ii < pnetwork->layers->size()/2) {
                        parent_layer = dynamic_cast<CommonLayer*>((*pfirst->layers)[ii]);
                    } else {
                        parent_layer = dynamic_cast<CommonLayer*>((*psecond->layers)[ii]);
                    }
                    if(parent_layer == NULL) {
                        //TODO: exception
                    }
                    if(common_layer != NULL) {
                        for(int jj = 0; jj < common_layer->outputs->size(); jj++) {
                            for(int kk = 0; kk < common_layer->inputs->size(); kk++) {
                                common_layer->weights->at(jj)[kk] = parent_layer->weights->at(jj)[kk] + randMToN(-0.1, 0.1);
                            }
                        }
                    }
                }
            }
        }
    }
    for(int ii = 0; ii < this->layers->size(); ii++) {
        common_layer = dynamic_cast<CommonLayer*>((*this->layers)[ii]);
        CommonLayer* parent_layer = dynamic_cast<CommonLayer*>((*population[first_parent_index]->layers)[ii]);
        if(common_layer != NULL) {
            for(int jj = 0; jj < common_layer->outputs->size(); jj++) {
                for(int kk = 0; kk < common_layer->inputs->size(); kk++) {
                    common_layer->weights->at(jj)[kk] = parent_layer->weights->at(jj)[kk];
                }
            }
        }
    }
    for(Network* pnetwork : population) {
        delete pnetwork;
    }
}