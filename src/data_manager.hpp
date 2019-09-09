#ifndef _DATA_MANAGER
#define _DATA_MANAGER
#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <utility>
#include <fstream>

class DataManager {
public:
    DataManager(std::ifstream &fp, int seed = 0);
    ~DataManager();
    std::pair<Eigen::SparseMatrix<double>, double> sample();
    std::pair<Eigen::SparseMatrix<double>, Eigen::VectorXd> full_data();
    void set_seed(int seed);
    int num_data();
    int num_features();

private:
    /* raw_data is stored like {0 : 1, 3 : 0.1, 5 : 0.7}*/
    Eigen::SparseMatrix<double> data;
    Eigen::VectorXd labels;
};
#endif
