/*
 * BogusDataSet.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: tomcheng
 */

#include "BogusDataSet.h"
#include "time.h"
namespace ParallelSGD {
 std::default_random_engine BogusDataSet::random_generator;
BogusDataSet::BogusDataSet(int num_feature) {
	// TODO Auto-generated constructor stub
	random_generator.seed(time(NULL));
	this->_num_feature = num_feature;
}

BogusDataSet::~BogusDataSet() {
	// TODO Auto-generated destructor stub
}

} /* namespace ParallelSGD */
