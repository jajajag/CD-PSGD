#include <iostream>
#include <fstream>
#include <cstdio>
#include "data_manager.hpp"

int main() {
    std::ifstream fp;
    //fp.open("../datasets/real-sim_test");
    fp.open("test.txt");
    DataManager dm(fp);
    fp.close();
    std::pair<Eigen::SparseMatrix<double>, std::vector<int> > ret = dm.sample(5);
    /*
    for (int i = 0; i < ret.first.rows(); ++i) {
        int count = 0;
        for (int j = 0; j < ret.first.cols(); ++j) {
            if (ret.first.coeffRef(i, j) != 0)
                //std::cout << ret.first.coeffRef(i, j) << std::endl;
                //printf("%.20f\n", ret.first.coeffRef(i, j));
                //count += 1;
        }
        return 0;
        std::cout << count << " " << ret.second[i] << std::endl;
    }
     * */
}
