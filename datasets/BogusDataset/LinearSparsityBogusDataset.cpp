/*
 * LinearSparsityBogusDataset.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: tomcheng
 */

#include "LinearSparsityBogusDataset.h"
#include <random>
#include <iostream>
namespace ParallelSGD {

LinearSparsityBogusDataSet::LinearSparsityBogusDataSet(int num_feature):BogusDataSet(num_feature) {
	// TODO Auto-generated constructor stub
	_bernoulli_p = 0;
	_normal_mean = 0;
	_normal_var = 0;
	_uni_min = 0;
	_uni_max = 0;
	_isSingle = false;

}

LinearSparsityBogusDataSet::~LinearSparsityBogusDataSet() {
	// TODO Auto-generated destructor stub
}

int LinearSparsityBogusDataSet::Prophet(std::vector<double> &input){
	int sum = 0,flag = -1;
	for(unsigned int i = 0 ; i < input.size();i++){
		sum = sum + flag*input[i]*i;
		flag = flag * -1;
	}
	if(sum>0){
		return 1;
	}
	return -1;
}
void LinearSparsityBogusDataSet::SetParameters(double bernoulli_p, double normal_mean, double normal_var, double uni_min, double uni_max){
	_bernoulli_p=bernoulli_p;
	_normal_mean=normal_mean;
	_normal_var=normal_var;
	_uni_min=uni_min;
	_uni_max=uni_max;
}

void LinearSparsityBogusDataSet::reset(double bernoulli_p, double normal_mean, double normal_var, double uni_min, double uni_max){

	SetParameters(bernoulli_p, normal_mean, normal_var, uni_min, uni_max);
	if(_isSingle) _normal_var = 0;

	 this->_Bernoulli_distribution = std::make_shared<std::bernoulli_distribution>(_bernoulli_p);
	 this->_Normal_distribution=std::make_shared<std::normal_distribution<double>>(_normal_mean,_normal_var);
	 this->_Uni_distribution=std::make_shared<std::uniform_real_distribution<double>>(_uni_min,_uni_max);
}


 void LinearSparsityBogusDataSet::OfferSample(std::vector<double> &SampleVect, int &label) {
	 SampleVect.clear();
	 SampleVect.resize(_num_feature,0);

	 // to make sample more colorful
	 if(!_isSingle){
		 _normal_mean=(*_Uni_distribution)(random_generator);
		 _normal_var=(*_Uni_distribution)(random_generator);
		 this->_Normal_distribution=std::make_shared<std::normal_distribution<double>>(_normal_mean,_normal_var);
	 }

	 for(unsigned int i = 0 ; i < SampleVect.size() ; i++){
		 if((*_Bernoulli_distribution)(this->random_generator)){
			 SampleVect[i]=(*_Normal_distribution)(this->random_generator);
		 }
	 }

	 label=Prophet(SampleVect);
 }

 void LinearSparsityBogusDataSet::LoadData(std::string filename) {
	 this->_filename = "bogusdataset";
	 reset(_bernoulli_p, _normal_mean, _normal_var, _uni_min, _uni_max);
 }

} /* namespace ParallelSGD */
