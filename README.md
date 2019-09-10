# ECD-PSGD
Trivial implementation of ECD-PSGD (Extrapolation Compression Decentralized
Parallel Stochastic Gradient Descent) for **my own** testing purpose. 
We aim at testing the properties of datasets by different parallel
algorithms.

# Usage

To compile the executable file, simply run (This requires the user to
install both OpenMPI and Eigen).

```
make
```

in src/ folder. Then, the executable *main* file will be in the src/ folder.
Run

```
make clean
```

The .o files will be removed and the main file will be moved to the root
folder. Then, run the main file by mpirun:

```
mpirun -n main file_name [iterations] [learning_rate] [verbose]
```
I use mpi to handle the communication between nodes. Thus, we need to use
mpirun instead of ./main. The file\_name is the name of the dataset. The
file should be in LibSVM format and all negative labels should be 0 instead
of -1. The #iteration is the number of iterations T in SGD. Simply make
the number of arguments greater or equal to 4. The program will output the
log\_loss of the training set on node 0 by each iteration.

# Results

The results will be posted here one the experiment is done.

# Alogrithm
The main algorithm for ECD-PSGD is in Hanlin Tang's paper
[Decentralization Meets Quantization](https://arxiv.org/abs/1803.06443v2).
The decentralized SGD is for quantization purpose. Here, I implement the 
same algorithm to test the efficiency of the parallelism. 

The main algorithm of ECD-PSGD is included in a whole loop. In each
iteration t, the algorithm do similar work as:

* Randomly choose one sample from the data.
* Compute the weights by neighbors' estimated value: x' = sum(y) / n.
* Update new local model: x' = x' - learning\_rate * gradient.
* Compute z value: z = (1 - t / 2) * x + t / 2 * x'.
* Compress z value and send the values to neighbors.
* Estimate the predicted value for neighbors by: y = (1 - 2 / t) * y + 2 *
/ t * C(z)

Because I do not implement quantization here, the z value is not compressed.
Thus, the noise for z value is also 0. After T iterations, we compute the
average average value of x.

# Structure

In this implementation, we have two classes DataManager in data\_manager.hpp
and ECD\_SGD in ecd\_sgd.hpp.

The DataManager read dataset *slowly* into an Eigen Sparse Matrix data and
an Eigen double VectorXd labels. It can also randomly choose one sample by
function sample() or return the full data.

On the other hand, the ECD\_SGD do the main algorithm of ECD-PSGD. The class
uses DataManager as one input. ECD\_SGD will train each batch and communicate
with other nodes in a ring by OpenMPI. Each node will compute the y\_value
for left and right node. The class should output 0/1 labels by probability
and compute log\_loss for the training set in each iteration.
