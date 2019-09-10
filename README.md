# ECD-PSGD
Trivial implementation of ECD-PSGD (Extrapolation Compression Decentralized
Parallel Stochastic Gradient Descent) for **my own** testing purpose. 
We aim at testing the properties of datasets by different parallel
algorithms.

# Usage

To compile the executable file, simply run

```
make
```

in src/ folder. Then, the executable *main* file will be in the src/ folder.
Run

```
make clean
```

The .o files will be removed and the main file will be moved to the root
folder.

```
mpirun -n main file_name [iterations] [learning_rate] [verbose]
```
I use mpi to handle the communication between nodes. Thus, 

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

