# EDDL Backend Development Status
---
&nbsp;

✅: DONE

🔵: PROGRESS

❌: TODO

&nbsp;

---
# LAYERS

### CORE

| Functionality | CPU  | GPU  | Comments |
| ------------- |------| -----| ---------|
| Tensor        | ✅ | ✅ |  |
| Dense         | ✅ | ✅ |  |
| Activation    | 🔵 | 🔵 | Sigmoid, LReLu ...
| BatchNorm     | ❌ | ❌ |
| Embedding     | ❌ | ❌ |
| Input         | ✅ | ✅ |  |
| Reshape       | ✅ | ✅ |  |
| Transpose     | ❌ | ❌ |
| Drop          | ✅ | ✅ |


### CONV and POOL

| Functionality | CPU  | GPU  | Comments |
| ------------- |------| -----| ---------|
|  Conv2D       | 🔵  | ❌ | Dilated, Groups...
|  Conv2DT      | ❌ | ❌ |
|  Upsampling   | ❌ | ❌ |
|  AvgPool   | ❌ | ❌ |
|  GlobalMaxPool   | ❌ | ❌ |
|  MaxPool  |  ✅ | ❌ |



### MERGE

| Functionality | CPU  | GPU  | Comments |
| ------------- |------| -----| ---------|
|  Add    |  ✅ | ❌ |
|  Average    | ❌ | ❌ |
|  Concat    | ❌ | ❌ |
|  MatMul    | ❌ | ❌ |
|  Max    | ❌ | ❌ |
|  Merge    | ❌ | ❌ |
|  Min    | ❌ | ❌ |
|  Substract    | ❌ | ❌ |


### NOISE

| Functionality | CPU  | GPU  | Comments |
| ------------- |------| -----| ---------|
|  Gaussian    | ✅ | ✅ |



### OPERATORS

| Functionality | CPU  | GPU  | Comments |
| ------------- |------| -----| ---------|
|  Abs    |  ✅ |  ❌ |
|  Diff   |  ✅ |  ✅ |
|  Div    |  ✅ |  ✅ |
|  Exp    |  ✅ |  ✅ |
|  Log    |  ✅ |  ✅ |
|  Log10    |  ✅ |  ❌|
|  Log2    |  ✅ |  ❌ |
|  Mean    | ✅| ❌ | still test properly
|  Mult    |  ✅ |  ✅|
|  Pow    | ❌ | ❌ |
|  Sqrt    | ❌ | ❌ |
|  Sum    |  ✅ |  ✅ |
|  Var    |  ✅| ❌ | still test properly

### RECURRENT


| Functionality | CPU  | GPU  | Comments |
| ------------- |------| -----| ---------|
|  LSTM    | ❌ | ❌ |
|  RNN    | ❌ | ❌ |

&nbsp;

---

# INITIALIZERS

| Functionality | CPU  | GPU  | Comments |
| ------------- |------| -----| ---------|
| Constant      | ❌ | ❌ |
| GlorotNormal  | ❌ | ❌ |
| GlorotUniform | ❌ | ❌ |
| Identity      | ❌ | ❌ |
| Orthogonal    | ❌ | ❌ |
| RandomNormal  | ❌ | ❌ |
| RandomUniform | ❌ | ❌ |

&nbsp;

---
## LOSSES

| Functionality | CPU  | GPU  | Comments |
| ------------- |------| -----| ---------|
| CrossEntropy  | ✅ | ✅ |
| MSE           | ✅ | ✅ |
| SoftCE        | ✅ | ✅ |

&nbsp;

---
# OPTIMIZERS

| Functionality | CPU  | GPU  | Comments |
| ------------- |------| -----| ---------|
| Adadelta      | ❌ | ❌ |
| Adagrad       | ❌ | ❌ |
| Adam          | ❌ | ❌ |
| Adamax        | ❌ | ❌ |
| Nadam         | ❌ | ❌ |
| RMSProp       | ❌ | ❌ |
| SGD           | ✅ | ✅ |

&nbsp;

---
# METRICS

| Functionality | CPU  | GPU  | Comments |
| ------------- |------| -----| ---------|
| CategoricalAcc | ✅ | ✅ |
| MSE            | ✅ | ✅ |
