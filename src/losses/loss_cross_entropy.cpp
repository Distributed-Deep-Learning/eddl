
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

#include "loss.h"

using namespace std;


LCrossEntropy::LCrossEntropy() : Loss("cross_entropy"){}

void LCrossEntropy::delta(Tensor *T, Tensor *Y, Tensor *D) {
    // delta: t/y - (1-t)/(1-y)
    if (aux1==NULL) aux1 = new Tensor(T->getShape(), T->device);
    if (aux2==NULL) aux2 = new Tensor(T->getShape(), T->device);
    if (one==NULL) one = new Tensor(T->getShape(), T->device);

    one->set(1.0);

    //  (1-t)/(1-y)
    Tensor::sum(1, one, -1, T, aux1, 0);
    Tensor::sum(1, one, -1, Y, aux2, 0);
    Tensor::el_div(aux1, aux2, aux2, 0);

    // t/y
    Tensor::el_div(T, Y, aux1, 0);

    Tensor::sum(1, aux1, -1, aux2, D, 0);

}

float LCrossEntropy::value(Tensor *T, Tensor *Y) {
    float f;

    if (aux1==NULL) aux1 = new Tensor(T->getShape(), T->device);
    Tensor::cent(T, Y, aux1);
    f = aux1->total_sum();

    return f;
}
