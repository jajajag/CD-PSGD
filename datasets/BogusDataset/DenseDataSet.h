/*
 * DenseDataSet.h
 *
 *  Created on: Sep 15, 2019
 *      Author: tomcheng
 */

#ifndef DENSEDATASET_H_
#define DENSEDATASET_H_

#include "dataset.h"
#include <string>
#include <vector>
#include <memory>

namespace ParallelSGD {

class DenseDataSet: public dataset {

protected:
std::shared_ptr<std::vector<std::vector<double>>> _data;
std::shared_ptr<std::vector<int>> _label;

public:
	DenseDataSet(int num_sample, int feature);
	void resize(int num_sample,int feature);
	std::shared_ptr<std::vector<std::vector<double>>> GatData(){return _data;}
	void PutValue(int sample, int pos, double value);
	void ShowContent();
	virtual ~DenseDataSet();
	virtual void OfferSample(std::vector<double> &SampleVect, int &label) override;
	virtual void LoadData(std::string filename) override{}
};

} /* namespace ParallelSGD */

#endif /* DENSEDATASET_H_ */
