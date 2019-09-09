#include <mpi.h>
#include "ecd_sgd.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>

ECD_SGD::ECD_SGD(DataManager *dm, double learning_rate) {
    /* Initialize MPI. */
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    /* Initialize DataManager. */
    data_manager = dm;
    dm->set_seed(world_rank);
    this->learning_rate = learning_rate;

    /* 1. Input: Initial point x_1 = x_1, initial estimate y_1 = x_1,
     * iteration step length gamma, weighted matrix W, and number of total
     * iterations T.*/
    /* The value should be initialized as 0 here! */
    x_value = Eigen::VectorXd::Zero(data_manager->num_features());
    x_value_old = Eigen::VectorXd::Zero(data_manager->num_features());
    y_value_left = Eigen::VectorXd::Zero(data_manager->num_features());
    y_value_right = Eigen::VectorXd::Zero(data_manager->num_features());
    z_value = Eigen::VectorXd::Zero(data_manager->num_features());
    z_value_left = Eigen::VectorXd::Zero(data_manager->num_features());
    z_value_right = Eigen::VectorXd::Zero(data_manager->num_features());
}

ECD_SGD::~ECD_SGD() {
    //delete data_manager;
	x_value_old.resize(0);
	x_value.resize(0);
	y_value_left.resize(0);
	y_value_right.resize(0);
	z_value.resize(0);
	z_value_left.resize(0);
	z_value_right.resize(0);
    MPI_Finalize();
}

void ECD_SGD::train(int T, bool verbose) {
    if (verbose) {
        std::cout << "Rank Iteration Loss" << std::endl;
    }
    /* for t = 1,2,...,T do */
    for (int t = 1; t <= T; ++t) {
        train_batch(t);
        //std::cout << x_value.transpose() << std::endl;
        //auto predict_labels = predict_proba();
        if (verbose) {
            std::cout << world_rank << " " << t << " " << 
                log_loss() << std::endl;
        }
    }
}

void ECD_SGD::train_batch(int t) {
    /* 3. Randomly sample S from local data of the ith node. */
    auto sample = data_manager->sample();
    Eigen::SparseMatrix<double> data = sample.first;
    double label = sample.second;

    /* 4. Compute a local stochastic gradient based on x_t and current
     * optimization variable x_t. */
    double theta = ECD_SGD::sigmoid((data * x_value)(0));
    /* Label here should be either 0 or 1. */
    auto delta = (theta - label) * data;

    /* 5. Compute the neighborhood weighted average by using the estimate
     * value of the connected neighbors. */
    x_value = (y_value_left + y_value_right) / 2;

    /* 6. Update the local model. */
    //learning_rate = learning_rate * 0.99;
    /* The gradient should be initialized as VectorXd.  */
    x_value = x_value - Eigen::VectorXd(learning_rate * delta.transpose());

    /* 7. Each node computes the z-value of itself. */
    z_value = (1 - t / 2.0) * x_value_old + t / 2.0 * x_value;
    communicate();
    x_value_old = x_value;

    /* 8. Each node updates the estimate for its connected neighbors.  */
    y_value_left = (1 - 2.0 / t) * y_value_left + 2.0 / t * z_value_left;
    y_value_right = (1 - 2.0 / t) * y_value_right + 2.0 / t * z_value_right;
}

void ECD_SGD::communicate() {
    /* Compress z value here. */

    /* Send z-value to right node (Consider we are in a clock). */
    /* 0-1, 1-2, 2-3, 3-0. */
    if (world_rank != 0) {
        MPI_Recv(z_value_left.data(), z_value.size(), MPI_DOUBLE,
                world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    if (world_size != 1) {
        MPI_Send(z_value.data(), z_value.size(), MPI_DOUBLE,
                (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
    }
    if (world_rank == 0 && world_size != 1) {
        MPI_Recv(z_value_left.data(), z_value.size(), MPI_DOUBLE,
                world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    /* Send z-value to left node (Consider we are in a clock). */
    /* 0-3, 3-2, 2-1, 1-0. */
    if (world_rank != 0) {
        MPI_Recv(z_value_right.data(), z_value.size(), MPI_DOUBLE,
                (world_rank + 1) % world_size, 0, MPI_COMM_WORLD,
                MPI_STATUS_IGNORE);
    }
    if (world_size != 1) {
        MPI_Send(z_value.data(), z_value.size(), MPI_DOUBLE,
                (world_rank + world_size - 1) % world_size, 0, MPI_COMM_WORLD);
    }
    if (world_rank == 0 && world_size != 1) {
        MPI_Recv(z_value_right.data(), z_value.size(), MPI_DOUBLE,
                1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}


Eigen::VectorXd ECD_SGD::predict_proba() {
    /* Use full data to compute the proba.  */
    auto full_data = data_manager->full_data();
    Eigen::VectorXd predict_labels = sigmoid(full_data.first * x_value);

    return predict_labels;
}

double ECD_SGD::log_loss() {
    /* First calculate the labels. */
    auto full_data = data_manager->full_data();
    Eigen::VectorXd predict_labels = sigmoid(full_data.first * x_value);

    /* Calculate the Log Loss:
     * loss = -((y)log(theta) + (1 - y)log(1 - theta)) / N. */
    Eigen::VectorXd ones = Eigen::VectorXd::Ones(predict_labels.size());
    Eigen::VectorXd theta_log = predict_labels.array().log();
    Eigen::VectorXd theta_logone = (ones - predict_labels).array().log();
    double loss = -(full_data.second.transpose() * theta_log)(0) - \
                  ((ones - full_data.second).transpose() * theta_logone)(0);
    loss = loss / predict_labels.size();

    return loss;
}
