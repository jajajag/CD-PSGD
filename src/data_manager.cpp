#include <string>
#include <cstdio>
#include <sstream>
#include <iostream>
#include "data_manager.hpp"

/* Initialize the DataManager with a file pointer. */
DataManager::DataManager(std::ifstream &fp) {
    std::string line;
    /* Read each line. */
    while (std::getline(fp, line)) {
        std::istringstream ss(line);
        std::string word;
        std::vector<std::pair<int, double> > pair_vec;
        int index;
        double num;
        /* Read each index/number pair. */
        while (ss >> word) {
            if (sscanf(word.c_str(), "%d:%lf", &index, &num) == 2) {
                std::pair<int, double> ind_num_pair(index, num);
                pair_vec.push_back(ind_num_pair);
                /* Update feature size. */
                num_features = num_features < index ? index : num_features;
            } else {
                /* Put the label to pos 0. */
                std::pair<int, double> ind_num_pair(0,
                        static_cast<double>(index));
                pair_vec.push_back(ind_num_pair);
            }
        }
        /* If the line is not empty. */
        if (!pair_vec.empty()) {
            data.push_back(pair_vec);
        }
    }
}

DataManager::~DataManager() {}

std::pair<Eigen::SparseMatrix<double>,
          std::vector<int> > DataManager::sample(int size) {
    /* Initialize sparse matrix and labels vector. */
    size = size <= 0 ? 1 : size;
    size = size < data.size() ? size : data.size();
    Eigen::SparseMatrix<double> mat(size, num_features);
    std::vector<int> labels(size);
    /* Randomly select indices. */
    std::vector<int> indices(data.size());
    for (int i = 0; i < data.size(); ++i) {
        indices[i] = i;
    }
    random_shuffle(indices.begin(), indices.end());
    for (int i = 0; i < size; ++i) {
        /* Assign the labels. */
        labels[i] = static_cast<int>(data[indices[i]][0].second);
        /* Assign the matrix with data. */
        for (int j = 1; j < data[indices[i]].size(); ++j) {
            mat.coeffRef(i, data[indices[i]][j].first - 1) = \
                           data[indices[i]][j].second;
        }
    }
    std::pair<Eigen::SparseMatrix<double>, std::vector<int> > ret(mat, labels);
    return ret;
}
