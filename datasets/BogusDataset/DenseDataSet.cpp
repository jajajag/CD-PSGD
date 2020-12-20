/*
 * DenseDataSet.cpp
 *
 *  Created on: Sep 15, 2019
 *      Author: tomcheng
 */

#include "DenseDataSet.h"
#include <memory>
#include "stdlib.h"
#include "time.h"
#include <iostream>
namespace ParallelSGD {


DenseDataSet::DenseDataSet(int num_sample, int num_feature) {
	// TODO Auto-generated constructor stub
	_data=std::make_shared<std::vector<std::vector<double>>>();
	this->resize(num_sample,num_feature);
}

DenseDataSet::~DenseDataSet() {
	// TODO Auto-generated destructor stub
}


void DenseDataSet::resize(int num_sample,int num_feature){
	//random num setting
	srand(time(NULL));

	if(this->_data.get()){
		this->_data = std::make_shared<std::vector<std::vector<double>>>();
		this->_label = std::make_shared<std::vector<int>>();
	}

	this->_data->resize(num_sample);
	this->_label->resize(num_sample,0);//Build Label

	for(int i = 0 ; i < num_sample ; i++)
	{
		this->_data->at(i).clear();//This line is to destroy the vectors which contain nonzero elements
		this->_data->at(i).resize(num_feature,0);
	}
}

void DenseDataSet::PutValue(int sample, int pos, double value){
	(*(this->_data))[sample][pos]=value;
}

void DenseDataSet::ShowContent(){
	for(unsigned int i=0; i < _data->size();i++){
		std::cout<<"Sample ID:	"<<i<<"	"<<"Lable:	"<<_label->at(i)<<" Content:	";
		for(unsigned int j = 0 ; j < (_data->at(i)).size();j++){
			std::cout<<(*_data)[i][j]<<"	";
		}
		std::cout<<std::endl;
	}
}



void DenseDataSet::OfferSample(std::vector<double> &SampleVect, int &label){

	int pick =  rand()%(this->_data->size());
	label = _label->at(pick);
	if(SampleVect.size()!=(_data->at(0)).size()){
		SampleVect.clear();
		SampleVect.resize((_data->at(0)).size() );
	}
	for(unsigned int i = 0 ; i < SampleVect.size() ;i++){
		SampleVect[i] = (_data->at(0))[i];
	}

}


} /* namespace ParallelSGD */
