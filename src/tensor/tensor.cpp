
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
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

#include "tensor.h"
#include "../utils.h"

#ifdef cGPU
#include "../hardware/gpu/tensor_cuda.h"
#include "../hardware/gpu/tensor_cuda_op.h"
#endif

using namespace std;

int initcuda[MAX_GPUS] = {0, 0, 0, 0, 0, 0, 0, 0};
int linpos;

extern ostream &operator<<(ostream &os, const vector<int> shape);

void msg(string s, string s2) {
    cout << "\n" << s << " (" << s2 << ")\n";
    exit(0);
}


void msg(string s) { msg(s, ""); }

int Tensor::isCPU() { return (device == DEV_CPU); }

int Tensor::isGPU() { return ((device >= DEV_GPU) && (device < DEV_FPGA)); }

int Tensor::isFPGA() { return (device >= DEV_FPGA); }


///////////////////////////////////////////////////////
//// Tensor constructors
///////////////////////////////////////////////////////
Tensor::Tensor() : device(DEV_CPU), ndim(0), size(0) {}

// From shape, pointer (sharing) and device
Tensor::Tensor(const vector<int> &shape, float *fptr, int dev)
{
  #ifndef cGPU
      if ((dev > DEV_CPU)&&(dev<DEV_FPGA)) {
          fprintf(stderr, "Not compiled for GPU\n");
          exit(0);
      }
  #endif
  #ifndef cFPGA
      if (dev >= DEV_FPGA) {
          fprintf(stderr, "Not compiled for FPGA\n");
          exit(0);
      }
  #endif

      this->device = dev;
      this->ndim = shape.size();
      this->shape = shape;

      size = 1;
      for (int i = 0; i < ndim; ++i) size *= shape[i];

      int s=size;
      for(int i=0;i<ndim;i++) {
        s/=shape[i];
        stride.push_back(s);
      }

      if (isCPU()) {
          if (fptr==nullptr) ptr = get_fmem(size,"Tensor::Tensor");
          else  ptr=fptr;

          if (ndim == 2) {
            ptr2=(Eigen::MatrixXf*)new Eigen::Map<Eigen::MatrixXf>(ptr, shape[1], shape[0]);
          }
      }
  #ifdef cGPU
      else if (isGPU())
        {
          gpu_device=device-DEV_GPU;
          if (!initcuda[gpu_device])
            {
              gpu_init(gpu_device);
              initcuda[gpu_device]=1;
            }
          if (fptr==NULL) ptr=gpu_create_tensor(gpu_device,size);
          else ptr=fptr;

        }
  #endif
  #ifdef cFPGA
      else {
        // create FPGA Tensor
      }
  #endif

      tsem = new mutex();
}



// From shape and device
Tensor::Tensor(const vector<int> &shape, int dev):Tensor(shape,nullptr,dev){}

// From shape and Tensor (sharing ptr)
Tensor::Tensor(const vector<int> &shape, Tensor *T):Tensor(shape,T->ptr,T->device) {}

Tensor* Tensor::zeros(const vector<int> &shape, int dev){
    auto t = new Tensor(shape, nullptr, dev);
    t->set(0.0f);
    return t;
}

Tensor* Tensor::ones(const vector<int> &shape, int dev){
    auto t = new Tensor(shape, nullptr, dev);
    t->set(1.0f);
    return t;
}

Tensor* Tensor::full(const vector<int> &shape, float value, int dev){
    auto t = new Tensor(shape, nullptr, dev);
    t->set(value);
    return t;
}


Tensor* raw_range(float min, float step, int size, int dev){
    auto t = new Tensor(vector<int>{size}, nullptr, dev);
    float v=min;
    for(int i=0; i<size; i++){
        t->ptr[i] = v;
        v+=step;
    }
    return t;
}

Tensor* Tensor::arange(float min, float max, float step, int dev){
    // Returns a 1-D tensor of size floor(end - start)/ + 1 with values from start to end with step step.
    // Step is the gap between two values in the tensor.
    int size = std::ceilf((max-min)/step);
    return raw_range(min, step, size, dev);
}

Tensor* Tensor::range(float min, float max, float step, int dev){
    int size = std::floorf((max-min)/step) + 1;
    return raw_range(min, step, size, dev);
}

Tensor* Tensor::linspace(float start, float end, int steps, int dev){
    float step = (end-start)/((float)steps-1);
    return Tensor::range(start, end, step, dev);
}

Tensor* Tensor::logspace(float start, float end, int steps, float base, int dev){
    float step = (end-start)/((float)steps-1);
    auto t = Tensor::range(start, end, step, dev);
    for(int i=0; i<steps; i++){
        t->ptr[i] = std::pow(base, t->ptr[i]);
    }
    return t;
}

Tensor* Tensor::eye(int size, int dev){
    auto t = new Tensor(vector<int>{size, size}, nullptr, dev);
    //t->set(0.0f);
    for(int i=0; i<size; i++){
        t->ptr[i*size+i] = 1.0f;
    }
    return t;
}

Tensor* Tensor::randn(const vector<int> &shape, int dev){
    auto t = new Tensor(shape, nullptr, dev);
    t->rand_normal(0.0f, 1.0f, false);
    return t;
}

///////////////////////////////////////////
// Tensor destructor
///////////////////////////////////////////
Tensor::~Tensor() {
    if (isCPU()) {
        delete ptr;
    }
#ifdef cGPU
    else if (isGPU())
      {
        gpu_delete_tensor(gpu_device,ptr);
      }
#endif
#ifdef cFPGA
    else {
      // delete FPGA Tensor
    }
#endif
    delete tsem;
}


///////////////////////////////////////////
// Other methods
///////////////////////////////////////////
void Tensor::save(string fname) {
    if (!isCPU())
        msg("Only save CPU Tensors", "Tensor::save");

    int i, j;
    FILE *fe;
    float fv;

    fe = fopen(fname.c_str(), "wb");
    if (fe == nullptr) {
        fprintf(stderr, "Not abel to write %s \n", fname.c_str());
        exit(1);
    }

    fprintf(stderr, "writting bin file\n");

    fwrite(&ndim, sizeof(int), 1, fe);
    for (i = 0; i < ndim; ++i)
        fwrite(&shape[i], sizeof(int), 1, fe);

    fwrite(ptr, sizeof(float), size, fe);

    fclose(fe);
}

///////////////////////////////////////////
void Tensor::save(FILE *fe) {
    if (!isCPU())
        msg("Only save CPU Tensors", "Tensor::save");

    fwrite(ptr, sizeof(float), size, fe);
}
void Tensor::load(FILE *fe) {
    if (!isCPU())
        msg("Only save CPU Tensors", "Tensor::save");

    fread(ptr, sizeof(float), size, fe);
}


///////////////////////////////////////////
vector<int> Tensor::getShape() {
    return vector<int>(this->shape);
}


///////////////////////////////////////////
void Tensor::info() {
    int i;

    fprintf(stdout, "DIM=%d\n", ndim);
    fprintf(stdout, "(");
    for (i = 0; i < ndim - 1; i++)
        fprintf(stdout, "%d,", shape[i]);
    fprintf(stdout, "%d)\n", shape[i]);

    fprintf(stdout, "Total bytes=%ld\n", size * sizeof(float));
    if (isCPU()) fprintf(stdout, "Device=CPU\n");
    else if (isGPU()) fprintf(stdout, "Device=GPU (%d)\n", gpu_device);
    else fprintf(stdout, "Device=FPGA\n");
}




///////////////////////////////////////////

void Tensor::print() {

    if (isCPU()) {
        if (ndim == 1)
            for (int i = 0; i < shape[0]; ++i)
                printf("%f ", ptr[i]);
        else if (ndim == 2) {
            cout << (*ptr2).transpose() << "\n";
        } else {
            int i;
            for (i = 0; i < size; ++i)
                printf("%f ", ptr[i]);
            printf("\n");
        }
    }
#ifdef cGPU
    else if (isGPU())
      {
        gpu_set_device(gpu_device);
        float *v= get_fmem(size,"Tensor::Tensor");
        cudaMemcpy(v,ptr,size*sizeof(float),cudaMemcpyDeviceToHost);
        if (ndim==2)
          {
            int i,j,p=0;
            for(i=0;i<shape[0];++i)
              {
                for(j=0;j<shape[1];++j,++p)
                  printf("%f ",v[p]);
                  printf("\n");
              }
          }
        else
          {
            int i;
            for(i=0;i<size;++i)
              printf("%f ",v[i]);
              printf("\n");
          }
          delete v;
      }
#endif
#ifdef cFPGA
    else {

    }
#endif
    cout << "\n";
}


///////////////////////////////////////////
void Tensor::point2data(const vector<int>& s, float *newptr){
    this->size = 1;
    this->shape = s;
    for (int i : s) this->size *= i;  // Compute size
    int sz=size;
    for(int i=0;i<ndim;i++) {
      sz/=shape[i];
      stride.push_back(sz);
    }
    this->ptr = newptr;  // Point to new data
}

void Tensor::copydata(const vector<int>& s, float *newptr){
    this->size = 1;
    this->shape = s;
    for (int i : s) this->size *= i;  // Compute size
    int sz=size;
    for(int i=0;i<ndim;i++) {
      sz/=shape[i];
      stride.push_back(sz);
    }

    // Allocate memory and fill tensor
    this->ptr = new float[size];
    std::copy(newptr, newptr+size, this->ptr);
}
