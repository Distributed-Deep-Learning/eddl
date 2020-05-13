/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.5
* copyright (c) 2020, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: April 2020
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include <cmath>

//#include <omp.h>

#include "eddl/initializers/initializer.h"
#include "eddl/tensor/tensor.h"
#include "eddl/tensor/tensor_reduction.h"
#include "eddl/tensor/nn/tensor_nn.h"
#include "eddl/regularizers/regularizer.h"
#include "eddl/tensor/nn/tensor_nn.h"
#include "eddl/hardware/cpu/nn/cpu_tensor_nn.h"
#include "eddl/apis/eddl.h"

using namespace std;
using namespace eddl;

int main(int argc, char **argv) {
    cout << "Tests for development. Ignore." << endl;

    // Overload operations
    Tensor t1 = *Tensor::full({5,5}, 1.0f);
    Tensor t2 = *Tensor::full({5,5}, 2.0f);
    Tensor t3 = ((t1 / t1) + (t2 * t2)) + 10;

    t1.print();
    t2.print();
    t3.print();

    // Mixed
    t3 = ((t1 / t1) + (t2 * t2));

    // Tensor op Scalar
    t3 = t3 + 10;
    t3 = t3 - 10;
    t3 = t3 * 10;
    t3 = t3 / 10;

    // Scalar op Tensor
    t3 = 10 + t3;
    t3 = 10 - t3;
    t3 = 10 * t3;
    t3 = 10 / t3;

    // Tensor op= Tensor
    t3 += t2;
    t3 -= t2;
    t3 *= t2;
    t3 /= t2;

    // Tensor op= Scalar
    t3 += 5;
    t3 -= 5;
    t3 *= 5;
    t3 /= 5;


    // Test concat
    Tensor* t5 = Tensor::range(1, 0+3*2*2, 1.0f); t5->reshape_({3, 2, 2}); t5->print();
    Tensor* t6 = Tensor::range(11, 10+3*2*2, 1.0f); t6->reshape_({3, 2, 2}); t6->print();
    Tensor* t7 = Tensor::range(101, 100+3*2*2, 1.0f); t7->reshape_({3, 2, 2}); t7->print();

    // Concat
    Tensor* t8 = Tensor::concat({t5, t6, t7}, 2);
    t8->print();

     Tensor::concat_back(t8, {t5, t6, t7}, 2);
     t5->print();
     t6->print();
     t7->print();
}
