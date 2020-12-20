/*
 * LinearSparsityBogusDataset.h
 *
 *  Created on: Sep 16, 2019
 *      Author: tomcheng
 */

#ifndef LINEARSPARSITYBOGUSDATASET_H_
#define LINEARSPARSITYBOGUSDATASET_H_

#include "BogusDataSet.h"
#include <vector>
#include <random>
#include <memory>
namespace ParallelSGD {

class LinearSparsityBogusDataSet: public BogusDataSet {
protected:

	//this distribution may be used into making normal distribution into a normal process.
	std::shared_ptr<std::uniform_real_distribution<double>> _Uni_distribution;
	//this distribution is used to determine this feature is zero/non-zero feature
	std::shared_ptr<std::bernoulli_distribution> _Bernoulli_distribution;
	//this distribution is used to determine the normal distribution
	std::shared_ptr<std::normal_distribution<double>> _Normal_distribution;
	double _bernoulli_p;
	double _normal_mean;
	double _normal_var;
	double _uni_min;
	double _uni_max;
	//if the dataset has only one sample, _isSingle is true.
	bool _isSingle;

public:
	LinearSparsityBogusDataSet(int num_feature);
	virtual ~LinearSparsityBogusDataSet();
	virtual int Prophet(std::vector<double> &input) override;
	virtual void OfferSample(std::vector<double> &SampleVect, int &label) override;
	virtual void LoadData(std::string filename) override;
	void SetParameters(double bernoulli_p, double normal_mean, double normal_var, double uni_min, double uni_max);
	void LoadData(){LoadData("");};
	void isSingle(){_isSingle=true;}
	void reset(double bernoulli_p, double normal_mean, double normal_var, double uni_min, double uni_max);
};

} /* namespace ParallelSGD */

#endif /* LINEARSPARSITYBOGUSDATASET_H_ */
