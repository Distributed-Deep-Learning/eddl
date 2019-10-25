/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.1
* copyright (c) 2019, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: October 2019
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/


#include "cpu_hw.h"

void cpu_range(Tensor *A, float min, float step){
    float v=min;

    //#pragma omp parallel for
    for(int i=0; i<A->size; i++){
        A->ptr[i] = v;
        v+=step;
    }
}

void cpu_eye(Tensor *A){
    #pragma omp parallel for
    for(int i=0; i<A->size; i++){

        if (i/A->shape[0] == i%A->shape[1]){ A->ptr[i] = 1.0f; }
        else { A->ptr[i] = 0.0f; }
    }
}
