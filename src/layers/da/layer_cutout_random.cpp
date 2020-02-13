/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.3
* copyright (c) 2019, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: October 2019
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "layer_da.h"


using namespace std;

int LCutoutRandom::total_layers = 0;

LCutoutRandom::LCutoutRandom(Layer *parent, vector<float> factor_x, vector<float> factor_y, float constant, string name, int dev, int mem) : LDataAugmentation(parent, name, dev, mem) {
    if(name.empty()) this->name = "cutout_random" + to_string(++total_layers);

    output = new Tensor(input->shape, dev);

    // Params
    this->factor_x = std::move(factor_x);
    this->factor_y = std::move(factor_y);
    this->constant = constant;

    parent->addchild(this);
    addparent(parent);
}


void LCutoutRandom::forward() {
    Tensor::cutout_random(this->input, this->output, this->factor_x, this->factor_y, this->constant);
}

void LCutoutRandom::backward() {

}


Layer *LCutoutRandom::share(int c, int bs, vector<Layer *> p) {
    auto *n = new LCutoutRandom(p[0], this->factor_x, this->factor_y, this->constant, "share_" + to_string(c) + this->name, this->dev, this->mem_level);
    n->orig = this;

    return n;
}

Layer *LCutoutRandom::clone(int c, int bs, vector<Layer *> p, int todev) {
    auto *n = new LCutoutRandom(p[0], this->factor_x, this->factor_y, this->constant, "clone_" + to_string(todev) + name, todev, this->mem_level);
    n->orig = this;

    return n;
}


string LCutoutRandom::plot(int c) {
    string s;

    if (c) s = name + " [label=" + "\"" + name + "\",style=filled,fontsize=12,fillcolor=bisque4,shape=box]";
    else s = name + " [label=" + "\"" + name + "\",style=filled,fontsize=12,fillcolor=White,shape=box]";

    return s;
}
