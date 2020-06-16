/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.7
* copyright (c) 2020, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: April 2020
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/

#include <cstdio>
#include <cuda.h>
#include <cuda_runtime_api.h>
#include <cublas_v2.h>

#include <thrust/device_ptr.h>
//#include <thrust/transform.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>
#include <thrust/extrema.h>

#include "eddl/hardware/gpu/gpu_tensor.h"
#include "eddl/hardware/gpu/gpu_kernels.h"
#include "eddl/hardware/gpu/gpu_hw.h"

#include "eddl/tensor/tensor.h"
#include "eddl/descriptors/descriptors.h"

// GPU: Structs for Thrust ********************************************

template<typename T>
struct absolute_value : public unary_function<T,T>
{
    __host__ __device__ T operator()(const T &x) const
    {
        return x < T(0) ? -x : x;
    }
};


/*
 * @struct varianceshifteop
 * @brief a unary function that shifts input data
 * by their mean and computes the squares of them
 */
struct variance_shift_sum : std::unary_function<float, float>{
    const float mean;

    variance_shift_sum(float m) : mean(m) { /* empty */ }

    __host__ __device__ float operator()(float x) const {
        float tmp = x - mean;
        return tmp*tmp;
    }
};

// GPU: Math (in-place) ********************************************
void gpu_abs(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_abs<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "abs");
}

void gpu_acos(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_acos<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "acos");
}

void gpu_add(Tensor *A, Tensor *B, float v) {
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_add<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size, v);
    check_cuda(cudaDeviceSynchronize(), "add");
}

void gpu_asin(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_asin<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "asin");
}

void gpu_atan(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_atan<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "atan");
}

void gpu_ceil(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_ceil<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "ceil");
}

void gpu_clamp(Tensor *A, Tensor *B, float min, float max){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_clamp<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size, min, max);
    check_cuda(cudaDeviceSynchronize(), "clamp");
}

void gpu_cos(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_cos<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "cos");
}

void gpu_cosh(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_cosh<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "cosh");
}

void gpu_exp(Tensor *A, Tensor *B){

    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_exp<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(),"exp");

}

void gpu_floor(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_floor<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "floor");
}


void gpu_log(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_log<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "log");

}


void gpu_log2(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_log2<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(),"log2");
}


void gpu_log10(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_log10<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(),"log10");
}


void gpu_logn(Tensor *A, Tensor *B, float n){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_logn<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size, n);
    check_cuda(cudaDeviceSynchronize(), "logn");
};

void gpu_mod(Tensor *A, Tensor *B, float v){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_mod<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size, v);
    check_cuda(cudaDeviceSynchronize(), "mod");
}

void gpu_inv(Tensor *A, Tensor *B, float v){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_inv<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size, v);
    check_cuda(cudaDeviceSynchronize(),"inv");
}

void gpu_mult(Tensor *A, Tensor *B, float v){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_mult<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size, v);
    check_cuda(cudaDeviceSynchronize(),"mult");

}

void gpu_normalize(Tensor *A, Tensor *B, float min, float max){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    float min_ori = gpu_min(A);
    float max_ori = gpu_max(A);

    gpu_normalize<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size, min_ori, max_ori, min, max);
    check_cuda(cudaDeviceSynchronize(), "normalize");
}

void gpu_pow(Tensor *A, Tensor *B, float v){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_pow<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size, v);
    check_cuda(cudaDeviceSynchronize(), "pow");
}

void gpu_powb(Tensor *A, Tensor *B, float v){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_powb<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size, v);
    check_cuda(cudaDeviceSynchronize(), "powb");
}

void gpu_remainder(Tensor *A, Tensor *B, float v){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_remainder<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size, v);
    check_cuda(cudaDeviceSynchronize(), "remainder");
}

void gpu_round(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_round<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "round");
}

void gpu_rsqrt(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_rsqrt<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "rsqrt");
}

void gpu_sigmoid(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_sigmoid<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "sigmoid");
}

void gpu_sign(Tensor *A, Tensor *B, float zero_sign){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_sign<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size, zero_sign);
    check_cuda(cudaDeviceSynchronize(), "sign");
}

void gpu_sin(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_sin<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "sin");
}

void gpu_sinh(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_sinh<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "sinh");
}


void gpu_sqr(Tensor *A, Tensor *B){

    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_sqr<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(),"sqr");

}

void gpu_sqrt(Tensor *A, Tensor *B){

    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_sqrt<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(),"sqrt");
}

void gpu_tan(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_tan<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "tan");
}

void gpu_tanh(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_tanh<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "tanh");
}

void gpu_trunc(Tensor *A, Tensor *B){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_trunc<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "trunc");
}

// CPU: Math (static) ********************************************


void gpu_add(float scA,Tensor *A, float scB,Tensor *B, Tensor *C,int incC){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_add<<<dimGrid,dimBlock>>>(scA,A->ptr,scB,B->ptr,C->ptr,incC,A->size);
    check_cuda(cudaDeviceSynchronize(),"addc");
}


void gpu_mult2D(Tensor *A, int tA, Tensor *B, int tB, Tensor *C,int incC){
    int device=A->gpu_device;
    cudaSetDevice(device);

    float alfa=1.0;
    float beta=(float)incC;

    cublasOperation_t trA = CUBLAS_OP_N;
    cublasOperation_t trB = CUBLAS_OP_N;

    int ldA=A->shape[1];
    int ldB=B->shape[1];
    int ldC=B->shape[1];
    int m=B->shape[1];
    int n=A->shape[0];
    int k=B->shape[0];


    if (tA)
    {
        trA = CUBLAS_OP_T;
        n=A->shape[1];
    }
    if (tB)
    {
        trB = CUBLAS_OP_T;
        m=B->shape[0];
        k=B->shape[1];
        ldC=B->shape[0];
    }

    check_cublas(cublasSgemm(hcublas[device],trB,trA,m,n,k,&alfa,B->ptr,ldB,A->ptr,ldA,&beta,C->ptr,ldC),"mult2D");

}


void gpu_el_div(Tensor *A, Tensor *B, Tensor *C, int incC){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_el_div<<<dimGrid,dimBlock>>>(A->ptr,B->ptr,C->ptr,incC,A->size);

    check_cuda(cudaDeviceSynchronize(),"gpu_el_div");
}


void gpu_el_mult(Tensor *A, Tensor *B, Tensor *C, int incC){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_el_mult<<<dimGrid,dimBlock>>>(A->ptr,B->ptr,C->ptr,incC,A->size);

    check_cuda(cudaDeviceSynchronize(),"gpu_el_mult");
}


void gpu_sum2D_rowwise(Tensor *A, Tensor *B, Tensor *C){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);


    gpu_sum2D_rowwise<<<dimGrid,dimBlock>>>(A->ptr,B->ptr,C->ptr,A->shape[0],A->shape[1]);

    check_cuda(cudaDeviceSynchronize(),"sum2D_rowwise");

}


void gpu_sum2D_colwise(Tensor *A, Tensor *B, Tensor *C){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_sum2D_colwise<<<dimGrid,dimBlock>>>(A->ptr,B->ptr,C->ptr,A->shape[0],A->shape[1]);

    check_cuda(cudaDeviceSynchronize(),"sum2D_rowwise");

}

void gpu_maximum(Tensor* A, Tensor* B, float v){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_maximum<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, v, A->size);
    check_cuda(cudaDeviceSynchronize(), "maximum");
}

void gpu_maximum(Tensor* A, Tensor* B, Tensor* C){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_maximum<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, C->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "maximum");
}

void gpu_minimum(Tensor* A, Tensor* B, float v){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_minimum<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, v, A->size);
    check_cuda(cudaDeviceSynchronize(), "minimum");
}

void gpu_minimum(Tensor* A, Tensor* B, Tensor* C){
    int device=A->gpu_device;
    cudaSetDevice(device);

    setDims(A);

    gpu_minimum<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, C->ptr, A->size);
    check_cuda(cudaDeviceSynchronize(), "minimum");
}


// GPU: Should be reductions ***************************
float gpu_max(Tensor *A){
    int device=A->gpu_device;
    cudaSetDevice(device);

    thrust::device_ptr<float> dev_ptr = thrust::device_pointer_cast(A->ptr);
    return *thrust::max_element(dev_ptr, dev_ptr + A->size);
}

void gpu_max(Tensor *A, Tensor *B, ReduceDescriptor2 *rd){

}

int gpu_argmax(Tensor *A){

}

void gpu_argmax(Tensor *A, Tensor *B, ReduceDescriptor2 *rd){

}

std::tuple<float, int> gpu_max(float *ptr, int size, int *map){

}

float gpu_min(Tensor *A){
    int device=A->gpu_device;
    cudaSetDevice(device);

    thrust::device_ptr<float> dev_ptr = thrust::device_pointer_cast(A->ptr);
    return *thrust::min_element(dev_ptr, dev_ptr + A->size);
}


float gpu_sum(Tensor *A){
    int device=A->gpu_device;

    cudaSetDevice(device);

    thrust::device_ptr<float> dev_ptr = thrust::device_pointer_cast(A->ptr);
    return thrust::reduce(dev_ptr, dev_ptr + A->size);
}

void gpu_sum(Tensor *A, Tensor *B, ReduceDescriptor2 *rd){
    int device=A->gpu_device;
    cudaSetDevice(device);

    gpu_initialize_rd(rd, A, B); // Walk through the source tensor

    setDims(A);
    gpu_sum<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, rd->gpu_addresses, A->size);
    check_cuda(cudaDeviceSynchronize(),"reduce_sum");
}


float gpu_sum_abs(Tensor *A){
    int device=A->gpu_device;
    cudaSetDevice(device);

    thrust::device_ptr<float> dev_ptr = thrust::device_pointer_cast(A->ptr);
    return thrust::transform_reduce(dev_ptr, dev_ptr + A->size, absolute_value<float>(), 0.0f, thrust::plus<float>());
}

void gpu_sum_abs(Tensor *A, Tensor *B, ReduceDescriptor2 *rd){
    int device=A->gpu_device;
    cudaSetDevice(device);

    gpu_initialize_rd(rd, A, B);

    setDims(A); // Walk through the source tensor
    gpu_sum_abs<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, rd->gpu_addresses, A->size);
    check_cuda(cudaDeviceSynchronize(),"reduce_sum_abs");
}

float gpu_prod(Tensor *A){
    int device=A->gpu_device;
    cudaSetDevice(device);

    thrust::device_ptr<float> dev_ptr = thrust::device_pointer_cast(A->ptr);
    float prod=thrust::reduce(dev_ptr, dev_ptr + A->size, 1.0f, thrust::multiplies<float>());

    return prod;
}

void gpu_prod(Tensor *A, Tensor *B, ReduceDescriptor2 *rd){
    int device=A->gpu_device;
    cudaSetDevice(device);

    gpu_initialize_rd(rd, A, B, true);

    setDims(B);  // Walk through reduced tensor
    gpu_prod<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, rd->gpu_addresses, B->size, rd->size_reduction);
    check_cuda(cudaDeviceSynchronize(),"reduce_prod");
}


float gpu_mean(Tensor *A){
    int device=A->gpu_device;

    cudaSetDevice(device);

    thrust::device_ptr<float> dev_ptr = thrust::device_pointer_cast(A->ptr);
    return thrust::reduce(dev_ptr, dev_ptr + A->size)/(float)A->size;
}

void gpu_mean(Tensor *A, Tensor *B, ReduceDescriptor2 *rd){
    int device=A->gpu_device;
    cudaSetDevice(device);

    gpu_initialize_rd(rd, A, B, true);

    setDims(B);  // Walk through reduced tensor
    gpu_mean<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, rd->gpu_addresses, B->size, rd->size_reduction);
    check_cuda(cudaDeviceSynchronize(),"reduce_gpu_mean");
}


float gpu_var(Tensor *A, bool unbiased){
    int device=A->gpu_device;
    cudaSetDevice(device);

    thrust::device_ptr<float> dev_ptr = thrust::device_pointer_cast(A->ptr);
    float mean = thrust::reduce(dev_ptr, dev_ptr + A->size,0.0f, thrust::plus<float>()) / A->size;
    float sum = thrust::transform_reduce(dev_ptr, dev_ptr + A->size, variance_shift_sum(mean), 0.0f, thrust::plus<float>());

    if(unbiased){return sum/(A->size-1.0f);}
    else {return sum/(A->size);}
}

void gpu_var(Tensor *A, Tensor *B, ReduceDescriptor2 *rd, bool unbiased){
    int device=A->gpu_device;
    cudaSetDevice(device);

    gpu_initialize_rd(rd, A, B, true);

    setDims(B);  // Walk through reduced tensor
    gpu_mean<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, rd->gpu_addresses, B->size, rd->size_reduction);
    gpu_var<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, rd->gpu_addresses, B->size, rd->size_reduction, unbiased);
    check_cuda(cudaDeviceSynchronize(),"reduce_gpu_var");
}

float gpu_std(Tensor *A, bool unbiased){
    return ::sqrtf(gpu_var(A, unbiased));
}

void gpu_std(Tensor *A, Tensor *B, ReduceDescriptor2 *rd, bool unbiased){
    int device=A->gpu_device;
    cudaSetDevice(device);

    gpu_initialize_rd(rd, A, B, true);

    setDims(B);  // Walk through reduced tensor
    gpu_mean<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, rd->gpu_addresses, B->size, rd->size_reduction);
    gpu_var<<<dimGrid,dimBlock>>>(A->ptr, B->ptr, rd->gpu_addresses, B->size, rd->size_reduction, unbiased);
    gpu_sqrt<<<dimGrid,dimBlock>>>(B->ptr, B->ptr, B->size);
    check_cuda(cudaDeviceSynchronize(),"reduce_gpu_std");
}


float gpu_median(Tensor *A){
    int device=A->gpu_device;
    cudaSetDevice(device);

    int size;
    int midpoint = A->size / 2.0f;
    if(A->size % 2==1 && A->size>1) { size = 1; }
    else{ size = 2; midpoint -=1; }

    // Copy (minimum) data to host
    auto *host_array = new float[size];
    check_cuda(cudaMemcpy(host_array, A->ptr+midpoint, size*sizeof(float),cudaMemcpyDeviceToHost),"gpu_median");

    // Compute median
    float median = 0.0f;
    for(int i=0; i<size; i++){median+=host_array[i];}
    median = median/size;

    delete[] host_array;
    return median;
}

int gpu_mode(Tensor *A){
    // TODO: Not implemented for GPU
}


// GPU: Reduction ***************************
void gpu_sum2D(float scA,Tensor *A, float scB,Tensor *B, Tensor *C,int incC){
    int device=A->gpu_device;
    cudaSetDevice(device);

    int m=A->shape[1];
    int n=B->shape[0];
    int ldA=A->shape[1];
    int ldB=B->shape[1];
    int ldC=A->shape[1];

    float alfa=scA;
    float beta=scB;
    float one=1.0;

    if (incC){
        check_cublas(cublasSgeam(hcublas[device],CUBLAS_OP_N,CUBLAS_OP_N, m,n,&alfa,A->ptr,ldA,&one,C->ptr,ldB,C->ptr,ldC),"sum2D");
        check_cublas(cublasSgeam(hcublas[device],CUBLAS_OP_N,CUBLAS_OP_N, m,n,&alfa,B->ptr,ldA,&one,C->ptr,ldB,C->ptr,ldC),"sum2D");
    }
    else {
        check_cublas(
                cublasSgeam(hcublas[device], CUBLAS_OP_N, CUBLAS_OP_N, m, n, &alfa, A->ptr, ldA, &beta, B->ptr, ldB,
                            C->ptr, ldC), "sum2D");
    }
}


void gpu_initialize_rd(ReduceDescriptor2 *rd, Tensor *A, Tensor *B, bool reverse){
    // TODO: TEMP! I don't like this approach
    if(rd->gpu_addresses == nullptr){
        int size = A->size;

        // Build cpu map (if needed)
        if(rd->cpu_addresses == nullptr){
            rd->build_map(reverse);
        }

        check_cuda(cudaMalloc((void**)&(rd->gpu_addresses), size*sizeof(int)),"create map");
        check_cuda(cudaDeviceSynchronize(), "create");

        check_cuda(cudaMemcpy(rd->gpu_addresses, rd->cpu_addresses, size*sizeof(int),cudaMemcpyHostToDevice),"copy map");
        check_cuda(cudaDeviceSynchronize(), "copy");

        // Delete cpu
//        if(rd->cpu_addresses != nullptr){
//            delete rd->cpu_addresses;
//            rd->cpu_addresses = nullptr;
//        }
    }
}