/*
 * RelativeLinearSparsityBogusDataSet.cpp
 *
 *  Created on: Sep 17, 2019
 *      Author: tomcheng
 */

#include "RelativeLinearSparsityBogusDataSet.h"

namespace ParallelSGD {

RelativeLinearSparsityBogusDataSet::RelativeLinearSparsityBogusDataSet(int num_feature):LinearSparsityBogusDataSet(num_feature)  {
	// TODO Auto-generated constructor stub

}

RelativeLinearSparsityBogusDataSet::~RelativeLinearSparsityBogusDataSet() {
	// TODO Auto-generated destructor stub
}

void RelativeLinearSparsityBogusDataSet::OfferSample(std::vector<double> &SampleVect, int &label) {

	if(SampleVect.size() != _num_feature)
	{
		SampleVect.clear();
		SampleVect.resize(_num_feature,0);
	}

	 for(unsigned int i = 0 ; i < SampleVect.size() ; i++){
		 if((*_Bernoulli_distribution)(this->random_generator)){
			 SampleVect[i]=(*_Normal_distribution)(this->random_generator);
		 }
	 }

	 label=Prophet(SampleVect);
}


} /* namespace ParallelSGD */
