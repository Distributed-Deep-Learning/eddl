
/////////////////////////////////////////////////////////////////////////////
// This file is part of EDDLL an European Distributed Deep Learning Library.
// Developed within the DeepHealth project.
// Boosting AI in Europe.
//
// Main authors and developers:
//      Salva Carrión: salcarpo@prhlt.upv.es
//      Roberto Paredes: rparedes@prhlt.upv.es
//      Joan Ander Gómez: jon@prhlt.upv.es
//
//
// Collaborators:
//      Mario Parreño: maparla@prhlt.upv.es
//
//
// To collaborate please contact rparedes@prhlt.upv.es
//
/////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "eddl.h"


using namespace std;

////////////////////////////////////////////////////////
///// EDDL is a wrapper class to ease and define the API
////////////////////////////////////////////////////////

tensor T(const vector<int> &shape) {
    return new LTensor(shape, DEV_CPU);
}

tensor T(const vector<int> &shape,float *ptr) {
    return new LTensor(shape, ptr, DEV_CPU);
}

tensor T_load(string fname) {
    return new LTensor(fname);
}

float * T_getptr(tensor T)
{
  return T->input->ptr;
}

void div(tensor t, float v) {
    t->input->div(v);
}

// ---- Operator Layers ----
layer Abs(layer l) {
    return new LAbs(l, "", DEV_CPU);
}

layer Diff(layer l1, layer l2) {
    return new LDiff(l1, l2, "", DEV_CPU);
}

layer Diff(layer l1, float k) {
    return new LDiff(l1, k, "", DEV_CPU);
}

layer Div(layer l1, layer l2) {
    return new LDiv(l1, l2, "", DEV_CPU);
}

layer Div(layer l1, float k) {
    return new LDiv(l1, k, "", DEV_CPU);
}

layer Exp(layer l) {
    return new LExp(l, "", DEV_CPU);
}

layer Log(layer l) {
    return new LLog(l, "", DEV_CPU);
}

layer Log2(layer l) {
    return new LLog2(l, "", DEV_CPU);
}

layer Log10(layer l) {
    return new LLog10(l, "", DEV_CPU);
}

layer Mult(layer l1, layer l2) {
    return new LMult(l1, l2, "", DEV_CPU);
}

layer Mult(layer l1, float k) {
    return new LMult(l1, k, "", DEV_CPU);
}

layer Pow(layer l1, layer l2) {
    return new LPow(l1, l2, "", DEV_CPU);
}

layer Pow(layer l1, float k) {
    return new LPow(l1, k, "", DEV_CPU);
}

layer Sqrt(layer l) {
    return new LSqrt(l, "", DEV_CPU);
}

layer Sum(layer l1, layer l2) {
    return new LSum(l1, l2, "", DEV_CPU);
}

layer Sum(layer l1, float k) {
    return new LSum(l1, k, "", DEV_CPU);
}


// ---- Reduction Layers ----
layer ReduceMean(layer l) {
    return ReduceMean(l, {0}, false);
}

layer ReduceMean(layer l, const vector<int> axis) {
    return ReduceMean(l, axis, false);
}

layer ReduceMean(layer l, bool keepdims) {
    return ReduceMean(l, {0}, keepdims);
}

layer ReduceMean(layer l, const vector<int> axis, bool keepdims) {
    return new LRMean(l, axis, keepdims, "", DEV_CPU);
}

layer ReduceVar(layer l) {
    return ReduceVar(l, {0});
}

layer ReduceVar(layer l, const vector<int> axis) {
    return ReduceVar(l, axis, false);
}

layer ReduceVar(layer l, bool keepdims) {
    return ReduceVar(l, {0}, keepdims);
}

layer ReduceVar(layer l, const vector<int> axis, bool keepdims) {
    return new LRVar(l, axis, keepdims, "", DEV_CPU);
}

layer ReduceSum(layer l) {
    return ReduceSum(l, {0});
}

layer ReduceSum(layer l, vector<int> axis) {
    return ReduceSum(l, axis, false);
}

layer ReduceSum(layer l, bool keepdims) {
    return ReduceSum(l, {0}, keepdims);
}

layer ReduceSum(layer l, const vector<int> axis, bool keepdims) {
    return new LRSum(l, axis, keepdims, "", DEV_CPU);
}

layer ReduceMax(layer l) {
    return ReduceMax(l, {0});
}

layer ReduceMax(layer l, vector<int> axis) {
    return ReduceMax(l, axis, false);
}

layer ReduceMax(layer l, bool keepdims) {
    return ReduceMax(l, {0}, keepdims);
}

layer ReduceMax(layer l, const vector<int> axis, bool keepdims) {
    return new LRMax(l, axis, keepdims, "", DEV_CPU);
}

layer ReduceMin(layer l) {
    return ReduceMin(l, {0});
}

layer ReduceMin(layer l, vector<int> axis) {
    return ReduceMin(l, axis, false);
}

layer ReduceMin(layer l, bool keepdims) {
    return ReduceMin(l, {0}, keepdims);
}

layer ReduceMin(layer l, const vector<int> axis, bool keepdims) {
    return new LRMin(l, axis, keepdims, "", DEV_CPU);
}

// ---- Generator Layers ----
layer GaussGenerator(float mean, float stdev, vector<int> size) {
    return new LGauss(mean, stdev, size, "", DEV_CPU);
}

layer UniformGenerator(float low, float high, vector<int> size) {
    return new LUniform(low, high, size, "", DEV_CPU);
}

//////////////////////////////////////////////////////


layer Activation(layer parent, string activation, string name) {
    return new LActivation(parent, activation, name, DEV_CPU);
}
//////////////////////////////////////////////////////


layer BatchNormalization(layer parent, float momentum, float epsilon, bool affine, string name){
    return new LBatchNorm(parent, momentum, epsilon, affine, name, DEV_CPU);
}

//////////////////////////////////////////////////////



layer Conv(layer parent, int filters, const vector<int> &kernel_size,
                 const vector<int> &strides, string padding, int groups, const vector<int> &dilation_rate,
                 bool use_bias, string name) {
    return new LConv(parent, filters, kernel_size, strides, padding, groups, dilation_rate, use_bias, name, DEV_CPU);
}
//////////////////////////////////////////////////////


layer ConvT(layer parent, int filters, const vector<int> &kernel_size,
                  const vector<int> &output_padding, string padding, const vector<int> &dilation_rate,
                  const vector<int> &strides, bool use_bias, string name){
    return new LConvT(parent, filters, kernel_size, output_padding, padding, dilation_rate, strides, use_bias, name, DEV_CPU);
}
/////////////////////////////////////////////////////////


layer Dense(layer parent, int ndim, bool use_bias, string name){
    return new LDense(parent, ndim, use_bias, name, DEV_CPU);
}
//////////////////////////////////////////////////////


layer Dropout(layer parent, float rate, string name) {
    return new LDropout(parent, rate, name, DEV_CPU);
}

//////////////////////////////////////////////////////
layer Embedding(int input_dim, int output_dim, string name){
    return new LEmbedding(input_dim, output_dim, name, DEV_CPU);
}

//////////////////////////////////////////////////////
layer GaussianNoise(layer parent, float stdev, string name){
    return new LGaussianNoise(parent, stdev, name, DEV_CPU);
}

//////////////////////////////////////////////////////


layer Input(const vector<int> &shape, string name) {
    tshape s=vector<int>(shape.begin(), shape.end());
    s.insert(s.begin(), 1);
    return new LInput(new Tensor(s), name, DEV_CPU);
}

//////////////////////////////////////////////////////

layer UpSampling(layer parent, const vector<int> &size, string interpolation, string name){
    return new LUpSampling(parent, size, interpolation, name, DEV_CPU);
}

//////////////////////////////////////////////////////
layer AveragePool(layer parent, const vector<int> &pool_size) {
    return AveragePool(parent, pool_size, pool_size);
}

layer AveragePool(layer parent, const vector<int> &pool_size, const vector<int> &strides, string padding, string name){
    //TODO: Implement
    return new LAveragePool(parent, pool_size, strides, padding, name, DEV_CPU);
}

//////////////////////////////////////////////////////

layer GlobalMaxPool(layer parent, string name){
    //TODO: Implement
    //return new LGlobalMaxPool(parent, PoolDescriptor({1,1}, {1,1}), name, DEV_CPU);
    return nullptr;
}

//////////////////////////////////////////////////////

layer GlobalAveragePool(layer parent, string name){
    //TODO: Implement
    //return new LGlobalAveragePool(parent,  PoolDescriptor({1,1}, {1,1}, "none"), name, DEV_CPU);
    return nullptr;
}


//////////////////////////////////////////////////////

layer MaxPool(layer parent, const vector<int> &pool_size, string padding, string name){
    return new LMaxPool(parent, pool_size, pool_size, padding, name, DEV_CPU);
}

layer MaxPool(layer parent, const vector<int> &pool_size, const vector<int> &strides, string padding, string name){
    return new LMaxPool(parent, pool_size, strides, padding, name, DEV_CPU);
}

//////////////////////////////////////////////////////

layer RNN(layer parent, int units, int num_layers, bool use_bias, float dropout, bool bidirectional, string name){
    return new LRNN(parent, units, num_layers, use_bias, dropout, bidirectional, name, DEV_CPU);
}

//////////////////////////////////////////////////////

layer LSTM(layer parent, int units, int num_layers, bool use_bias, float dropout, bool bidirectional, string name){
    return new LLSTM(parent, units, num_layers, use_bias, dropout, bidirectional, name, DEV_CPU);
}
//////////////////////////////////////////////////////

layer Reshape(layer parent, const vector<int> &shape, string name) {
    tshape s=vector<int>(shape.begin(), shape.end());
    s.insert(s.begin(), 1);
    return new LReshape(parent, s, name, DEV_CPU);
}
/////////////////////////////////////////////////////////

layer Transpose(layer parent, const vector<int> &dims, string name){
    return new LTranspose(parent, dims, name, DEV_CPU);
}
/////////////////////////////////////////////////////////


loss LossFunc(string type){
    if(type == "mse" || type == "mean_squared_error"){
        return new LMeanSquaredError();
    } else if(type == "cross_entropy"){
        return new LCrossEntropy();
    } else if (type == "soft_cross_entropy"){
        return new LSoftCrossEntropy();
    }
    return nullptr;
}
/////////////////////////////////////////////////////////


metric MetricFunc(string type){
    if(type == "mse" || type == "mean_squared_error"){
        return new MMeanSquaredError();
    } else if(type == "categorical_accuracy" || type == "accuracy"){
        return new MCategoricalAccuracy();
    }
    return nullptr;
}
/////////////////////////////////////////////////////////



layer Add(const vector<layer> &layers, string name) {
    return new LAdd(layers, name, DEV_CPU);
}

////////////////////////////////////////////////////////

layer Average(const vector<layer> &layers, string name){
    //TODO: Implement
    return new LAverage(layers, name, DEV_CPU);
}

/////////////////////////////////////////////////////////

layer Subtract(const vector<layer> &layers, string name) {
    return new LSubtract(layers, name, DEV_CPU);
}

////////////////////////////////////////////////////////

layer Concat(const vector<layer> &layers, string name) {
    return new LConcat(layers, name, DEV_CPU);
}

////////////////////////////////////////////////////////

layer MatMul(const vector<layer> &layers, string name){
    return new LMatMul(layers, name, DEV_CPU);
}

////////////////////////////////////////////////////////

layer Maximum(const vector<layer> &layers, string name){
    return new LMaximum(layers, name, DEV_CPU);
}

////////////////////////////////////////////////////////

layer Minimum(const vector<layer> &layers, string name){
    return new LMinimum(layers, name, DEV_CPU);
}


////////////////////////////////////////////////////////

optimizer adadelta(float lr, float rho, float epsilon, float weight_decay){
    //Todo: Implement
    return new AdaDelta(lr, rho, epsilon, weight_decay);
}
optimizer adam(float lr, float beta_1, float beta_2, float epsilon, float weight_decay, bool amsgrad){
    //Todo: Implement
    return new Adam(lr, beta_1, beta_2, epsilon, weight_decay, amsgrad);
}
optimizer adagrad(float lr, float epsilon, float weight_decay){
    //Todo: Implement
    return new Adagrad(lr, epsilon, weight_decay);
}
optimizer adamax(float lr, float beta_1, float beta_2, float epsilon, float weight_decay){
    //Todo: Implement
    return new Adamax(lr, beta_1, beta_2, epsilon, weight_decay);
}
optimizer nadam(float lr, float beta_1, float beta_2, float epsilon, float schedule_decay){
    //Todo: Implement
    return new Nadam(lr, beta_1, beta_2, epsilon, schedule_decay);
}
optimizer rmsprop(float lr, float rho, float epsilon, float weight_decay){
    //Todo: Implement
    return new RMSProp(lr, rho, epsilon, weight_decay);
}

optimizer sgd(float lr, float momentum, float weight_decay, bool nesterov){
    return new SGD(lr, momentum, weight_decay, nesterov);
}

void change(optimizer o, vector<float> &params){
    o->change(params);
}

////////////////////////////////////////////////////////
initializer Constant(float value){
    //Todo: Implement
    return new IConstant(value);
}

initializer Identity(float gain){
    //Todo: Implement
    return new IIdentity(gain);
}
initializer GlorotNormal(float seed) {
    //Todo: Implement
    return new IGlorotNormal(seed);
}
initializer GlorotUniform(float seed){
    //Todo: Implement
    return new IGlorotUniform(seed);
}
initializer RandomNormal(float mean, float stdev, int seed){
    //Todo: Implement
    return new IRandomNormal(mean, stdev, seed);
}
initializer RandomUniform(float minval, float maxval, int seed){
    //Todo: Implement
    return new IRandomUniform(minval, maxval, seed);
}
initializer Orthogonal(float gain, int seed){
    //Todo: Implement
    return new IOrthogonal(gain, seed);
}


/////////////////////////////////////////////////////////
model Model(vlayer in, vlayer out) {
    return new Net(in, out);
}

///////////
compserv CS_CPU(int th) {
    return new CompServ(th, {}, {});
}

compserv CS_GPU(const vector<int> &g) {
    return new CompServ(0, g, {});
}

compserv CS_FGPA(const vector<int> &f) {
    return new CompServ(0, {}, f);
}


////////////

string summary(model m) {
    return m->summary();
}

void save(model m,string fname)
{
  FILE *fe = fopen(fname.c_str(), "wb");
  if (fe == nullptr) {
      fprintf(stderr, "Not able to write to %s \n", fname.c_str());
      exit(1);
  }

  fprintf(stderr, "writting bin file\n");

  m->save(fe);

  fclose(fe);

}

void load(model m,string fname)
{
  FILE *fe = fopen(fname.c_str(), "rb");
  if (fe == nullptr) {
      fprintf(stderr, "Not able to read from %s \n", fname.c_str());
      exit(1);
  }

  fprintf(stderr, "reading bin file\n");

  m->load(fe);

  fclose(fe);

}
void plot(model m, string fname) {
    m->plot(fname);
}

void build(model net, optimizer o, const vector<string> &lo, const vector<string> &me) {
    build(net, o, lo, me, new CompServ(std::thread::hardware_concurrency(), {}, {}));
}

void build(model net, optimizer o, const vector<string> &lo, const vector<string> &me, CompServ *cs) {
    vector<Loss*> l;
    vector<Metric*> m;

    // Replace string by functions
    for(const auto & li : lo){
        l.push_back(LossFunc(li));
    }
    for(const auto & mi : me){
        m.push_back(MetricFunc(mi));
    }

    net->build(o, l, m, cs);
}


void fit(model net, const vector<LTensor *> &in, const vector<LTensor *> &out, int batch, int epochs) {
    vtensor tin;
    for (int i = 0; i < in.size(); i++)
        tin.push_back(in[i]->input);

    vtensor tout;
    for (int i = 0; i < out.size(); i++)
        tout.push_back(out[i]->input);


    net->fit(tin, tout, batch, epochs);
}


void evaluate(model net, const vector<LTensor *> &in, const vector<LTensor *> &out) {
    vtensor tin;
    for (int i = 0; i < in.size(); i++)
        tin.push_back(in[i]->input);

    vtensor tout;
    for (int i = 0; i < out.size(); i++)
        tout.push_back(out[i]->input);


    net->evaluate(tin, tout);
}

void predict(model net, const vector<LTensor *> &in, const vector<LTensor *> &out) {
    vtensor tin;
    for (int i = 0; i < in.size(); i++)
        tin.push_back(in[i]->input);

    vtensor tout;
    for (int i = 0; i < out.size(); i++)
        tout.push_back(out[i]->input);


    net->predict(tin, tout);
}


void set_trainable(layer l){
    //Todo: Implement

}


layer get_layer(model m, string layer_name){
    //Todo: Implement
    return nullptr;
}


model load_model(string fname){
    //Todo: Implement
    return nullptr;
}

void save_model(model m, string fname){
    //Todo: Implement
}


void set_trainable(model m){
    //Todo: Implement
}

model zoo_models(string model_name){
    //Todo: Implement
    return nullptr;
}


bool exist(string name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    }
    return false;
}


//////
void download_mnist() {
    // TODO: Too big, we should use the one in the PyEDDL
    // TODO: Need for "to_categorical" method
    string cmd;
    string trX = "trX.bin";
    string trY = "trY.bin";
    string tsX = "tsX.bin";
    string tsY = "tsY.bin";

    if ((!exist(trX)) || (!exist(trY)) || (!exist(tsX)) || (!exist(tsY))) {
        cmd = "wget https://www.dropbox.com/s/khrb3th2z6owd9t/trX.bin";
        int status = system(cmd.c_str());
        if (status < 0) {
            msg("wget must be installed", "eddl.download_mnist");
            exit(1);
        }

        cmd = "wget https://www.dropbox.com/s/m82hmmrg46kcugp/trY.bin";
        status = system(cmd.c_str());
        if (status < 0) {
            msg("wget must be installed", "eddl.download_mnist");
            exit(1);
        }
        cmd = "wget https://www.dropbox.com/s/7psutd4m4wna2d5/tsX.bin";
        status = system(cmd.c_str());
        if (status < 0) {
            msg("wget must be installed", "eddl.download_mnist");
            exit(1);
        }
        cmd = "wget https://www.dropbox.com/s/q0tnbjvaenb4tjs/tsY.bin";
        status = system(cmd.c_str());
        if (status < 0) {
            msg("wget must be installed", "eddl.download_mnist");
            exit(1);
        }

    }
}


model get_model_mlp(int batch_size){
    // Temp. for debugging
    // network
    layer in=Input({batch_size, 784});
    layer l=in;

    for(int i=0;i<3;i++)
        l=Activation(Dense(l,1024),"relu");

    layer out=Activation(Dense(l,10),"softmax");

    // net define input and output layers list
    model net=Model({in},{out});

    return net;
}

model get_model_cnn(int batch_size){
    // Temp. for debugging
    // network
    layer in=Input({batch_size, 784});
    layer l=in;

    l=Reshape(l,{batch_size, 1,28,28});
    l=MaxPool(Activation(Conv(l, 16, {3,3}),"relu"),{2,2});
    l=MaxPool(Activation(Conv(l, 32, {3,3}),"relu"),{2,2});
    l=MaxPool(Activation(Conv(l, 64, {3,3}),"relu"),{2,2});
    l=MaxPool(Activation(Conv(l, 128, {3,3}),"relu"),{2,2});

    l=Reshape(l,{batch_size,-1});

    l=Activation(Dense(l,32),"relu");

    layer out=Activation(Dense(l,10),"softmax");

    // net define input and output layers list
    model net=Model({in},{out});
    return net;
}
