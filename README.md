# ECD-PSGD
Trivial implementation of ECD-PSGD (Extrapolation Compression Decentralized
Parallel Stochastic Gradient Descent) for *my own* testing purpose. 

# Usage


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

