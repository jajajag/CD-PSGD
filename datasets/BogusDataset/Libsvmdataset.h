/*
 * Libsvmdataset.h
 *
 *  Created on: Sep 10, 2019
 *      Author: tomcheng
 */

#ifndef LIBSVMDATASET_H_
#define LIBSVMDATASET_H_

#include "dataset.h"
#include "DenseDataSet.h"
#include <string>
#include <vector>
namespace ParallelSGD {

class Libsvmdataset: public  DenseDataSet {
protected:
	//This function is used to split "pos:value" string item
	void SplitOneItem(const char* begin, const char* end, int &pos, double &value);
	void FillMatrix_OneLine(std::string &oneline, int sample);
public:
	Libsvmdataset(int sample,int feature, std::string filename);
	virtual ~Libsvmdataset();
	virtual void OfferSample(std::vector<double> &SampleVect, int &label) override;
	virtual void LoadData(std::string filename) override;
};

} /* namespace ParallelSGD */

#endif /* LIBSVMDATASET_H_ */
