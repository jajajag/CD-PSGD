#include <string>
#include <tuple>
#include <vector>
#include <iostream>
#include "data_manager.hpp"

/* Initialize the DataManager with a file pointer. */
DataManager::DataManager(std::ifstream &fp, int seed) {
    /* Save each index : num pair into a tuple: (line, index, num). */
    std::vector<std::tuple<int, int, double> > raw_data;
    int index, ret, line_count = 0, features_count = 0;
    double num;
    std::string word;
    srand(seed);
    //std::ios::sync_with_stdio(false);

    /* Read raw data from the file. */
    while (fp >> word) {
        ret = sscanf(word.c_str(), "%d:%lf", &index, &num);
        if (ret == 2) {
            /* Read index:num pair. */
            std::tuple<int, int, double> elem(line_count - 1, index, num);
            raw_data.push_back(elem);
            /* Mark down the number of features. */
            features_count = features_count < index ? index : features_count;
        } else if (ret == 1) {
            /* Read the label at the beginning. */
            std::tuple<int, int, double> elem(line_count++, 0, index);
            raw_data.push_back(elem);
        }
    }

    /* Form the data into matrix and vector. */
    data.resize(line_count, features_count + 1);
    labels.resize(line_count);
    int line_num;
    for (const auto &it : raw_data) {
        line_num = std::get<0>(it);
        index = std::get<1>(it);
        num = std::get<2>(it);
        if (index == 0) {
            data.coeffRef(line_num, index) = 1;
            labels(line_num) = num;
        } else {
            data.coeffRef(line_num, index) = num;
        }
    }
}

DataManager::~DataManager() {
    /* Release memory for data. */
    data.resize(0, 0);
    labels.resize(0);
}

/* Randomly select a sample from the whole dataset. */
std::pair<Eigen::SparseMatrix<double>, double> DataManager::sample() {
    /* Generate random index. */
    int index = rand() % num_data();

    /* Assign selected row of the data. */
    auto ret_data = data.middleRows(index, 1);
    int ret_label = labels(index);
    return std::pair<Eigen::SparseMatrix<double>, double>(ret_data, ret_label);
}

std::pair<Eigen::SparseMatrix<double>,
    Eigen::VectorXd> DataManager::full_data() {
    return std::pair<Eigen::SparseMatrix<double>,
           Eigen::VectorXd>(data, labels);
}

int DataManager::num_data() {
    return data.rows();
}

int DataManager::num_features() {
    return data.cols();
}

void DataManager::set_seed(int seed) {
    srand(seed);
}
