/*
 * RelativeLinearSparsityBogusDataSet.h
 *
 *  Created on: Sep 17, 2019
 *      Author: tomcheng
 */

#ifndef RELATIVELINEARSPARSITYBOGUSDATASET_H_
#define RELATIVELINEARSPARSITYBOGUSDATASET_H_

#include "LinearSparsityBogusDataset.h"

namespace ParallelSGD {

class RelativeLinearSparsityBogusDataSet: public LinearSparsityBogusDataSet {
public:
	RelativeLinearSparsityBogusDataSet(int num_feature);
	virtual ~RelativeLinearSparsityBogusDataSet();
	virtual void OfferSample(std::vector<double> &SampleVect, int &label) override;
};

} /* namespace ParallelSGD */

#endif /* RELATIVELINEARSPARSITYBOGUSDATASET_H_ */
