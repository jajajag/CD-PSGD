/*
 * BogusDataSet.h
 *
 *  Created on: Sep 16, 2019
 *      Author: tomcheng
 */

#ifndef BOGUSDATASET_H_
#define BOGUSDATASET_H_

#include "dataset.h"
#include <random>
#include <memory>
namespace ParallelSGD {

class BogusDataSet: public dataset {

protected:
	//for different bogusdataset may want have different random seq number, thus random generator use static variable
	static std::default_random_engine random_generator;
	unsigned int _num_feature;
public:
	BogusDataSet(int num_feature);
	//this function is used to compute the label of input vector
	virtual int Prophet(std::vector<double> &input)=0;
	virtual ~BogusDataSet();
	virtual void OfferSample(std::vector<double> &SampleVect, int &label) override{}
	virtual void LoadData(std::string filename) override{}
};

} /* namespace ParallelSGD */

#endif /* BOGUSDATASET_H_ */
