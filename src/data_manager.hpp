#include <Eigen/Sparse>
#include <vector>
#include <utility>
#include <fstream>

class DataManager {
public:
    DataManager(std::ifstream &fp);
    ~DataManager();
    std::pair<Eigen::SparseMatrix<double>, std::vector<int> > sample(int size);

private:
    std::vector<std::vector<std::pair<int, double> > > data;
    int num_features;
};
