#ifndef _DCD_PSGD
#define _DCD_PSGD
#include <Eigen/Dense>
#include "data_manager.hpp"

class DCD_PSGD {
public:
    DCD_PSGD(DataManager *dm, double learning_rate = 0.1);
    ~DCD_PSGD();
    void train(int T, bool verbose = false);
    void train_batch(int t);
    void communicate();
    Eigen::VectorXd communicate_reduce();
    Eigen::VectorXd predict_proba(Eigen::VectorXd x_value_avg);
    double log_loss(Eigen::VectorXd x_value_avg);

private:
    int world_size;
    int world_rank;
    double learning_rate;

    DataManager *data_manager;

    /* x_t and x_t+1. */
    Eigen::VectorXd x_value;
    Eigen::VectorXd x_value_old;
    /* Suppose all nodes are in a ring. Save y-value for left and right
     * nodes. */
    Eigen::VectorXd x_value_left;
    Eigen::VectorXd x_value_right;
    Eigen::VectorXd z_value;
    Eigen::VectorXd z_value_left;
    Eigen::VectorXd z_value_right;


    static double sigmoid(double dot) {
        return 1 / (1 + exp(-dot));
    }

    static Eigen::VectorXd sigmoid(Eigen::VectorXd dot) {
        return 1 / (1 + (-dot).array().exp());
    }
};

#endif
