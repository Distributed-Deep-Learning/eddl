/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.2
* copyright (c) 2019, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: October 2019
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <utility>

#include "layer_operators.h"


using namespace std;

int LSelect::total_layers = 0;

/**
  @brief Computes the absolute value of a Layer

  @param l a Layer.
  @param name a name for the operation (predefined as 'abs+TotaLSelectLayers')
  @param dev which computing service utilize

  @returns the absolute value of each element in l

  */
LSelect::LSelect(Layer *parent, vector<string> str_indices, string name, int dev): OperatorLayer(name, dev) {
    // Set default name
    if(name.empty()) this->name = "select_" + to_string(++total_layers);

    // Set defaults
    this->str_indices = std::move(str_indices);

    // Set input
    input=parent->output;

    // Compute range of indices (with fake batch)
    vector<string> idxs_temp = this->str_indices;
    idxs_temp.insert(idxs_temp.begin(), ":");
    this->idxs_range = parse_indices(idxs_temp, input->shape);

    // Get output shape (without batch)
    vector<int> oshape = indices2shape(idxs_range);

    // Set flow tensors
    output=new Tensor(oshape, dev);
    delta=new Tensor(output->shape, dev);

    parent->addchild(this);
    addparent(parent);
}

void LSelect::resize(int b){
    Layer::resize(b);

    // Update batch of range
    this->idxs_range[0][1] = b-1;

    // Compute index translation (output=>input)
    this->addresses = this->input->ranges2indices(this->idxs_range);
}

void LSelect::forward(){
    Tensor::select(this->input, this->output, this->addresses);
}

void LSelect::backward(){
    Tensor::select_back(this->delta, this->parent[0]->delta, this->addresses);
}


Layer *LSelect::share(int c, int bs, vector<Layer *> p) {
    return clone(c,bs,p,dev);
}

Layer *LSelect::clone(int c, int bs, vector<Layer *> p, int todev) {
    LSelect *n = new LSelect(p[0], this->str_indices, "share_" + to_string(c) + name, todev);
    n->orig = this;
    return n;
}
