
/////////////////////////////////////////////////////////////////////////////
// This file is part of EDDLL an European Distributed Deep Learning Library.
// Developed within the DeepHealth project.
// Boosting AI in Europe.
//
// Main authors and developers:
//      Roberto Paredes: rparedes@prhlt.upv.es
//      Joan Ander Gómez: jon@prhlt.upv.es
//
//
// Collaborators:
//      Salva Carrión: salcarpo@prhlt.upv.es
//      Mario Parreño: maparla@prhlt.upv.es
//
//
// To collaborate please contact rparedes@prhlt.upv.es
//
/////////////////////////////////////////////////////////////////////////////



#include <stdio.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "layer_recurrent.h"


using namespace std;

int LLSTM::total_layers = 0;

LLSTM::LLSTM(Layer *parent, int units, int num_layers, bool use_bias, float dropout, bool bidirectional, string name, int dev) : LinLayer(name, dev) {

    this->units = units;
    this->num_layers = num_layers;
    this->use_bias = use_bias;
    this->dropout = dropout;
    this->bidirectional = bidirectional;

    // TODO: Implement
}


// virtual
void LLSTM::forward() {
    // TODO: Implement
}

void LLSTM::backward() {
    // TODO: Implement
}


Layer *LLSTM::share(int c, int bs, vector<Layer *> p) {
    LLSTM *n = new LLSTM(p[0], units, num_layers, use_bias, dropout, bidirectional, "share_" + to_string(c) + name, dev);
    n->orig = this;

    // TODO: Implement

    return n;
}

Layer *LLSTM::clone(int c, int bs, vector<Layer *> p, int todev) {
    LLSTM *n = new LLSTM(p[0], units, num_layers, use_bias, dropout, bidirectional, "clone_" + to_string(todev) + name, todev);
    n->orig = this;

    // TODO: Implement

    return n;
}


string LLSTM::plot(int c) {
    string s;

    if (c) s = name + " [label=" + "\"" + name + "\",style=filled,fontsize=12,fillcolor=bisque4,shape=box]";
    else s = name + " [label=" + "\"" + name + "\",style=filled,fontsize=12,fillcolor=White,shape=box]";

    return s;
}
