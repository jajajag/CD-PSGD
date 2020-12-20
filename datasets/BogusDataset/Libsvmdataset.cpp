/*
 * Libsvmdataset.cpp
 *
 *  Created on: Sep 10, 2019
 *      Author: tomcheng
 */

#include "Libsvmdataset.h"
#include "string_splitter.h"
#include "string_splitter_inl.h"
#include <string>
#include <fstream>
#include "DenseDataSet.h"
#include <vector>
#include <iostream>



namespace ParallelSGD {

Libsvmdataset::Libsvmdataset(int sample,int feature, std::string filename):DenseDataSet(sample,feature){
	// TODO Auto-generated constructor stub
	this->_filename = filename;
}



void Libsvmdataset::FillMatrix_OneLine(std::string &line, int sample){

	butil::StringSplitter s_head(line.c_str(),' ') , s_end(line.c_str(),' ');
	++s_end;
	int pos = -1;
	double value = -1;

	//split label

	s_head.to_int(&(this->_label->at(sample)));

	++s_end;
	++s_head;

	//split and fill data matrix
    for (; s_head; ++s_end,++s_head) {

    	this->SplitOneItem(s_head.field(),s_end.field(),pos,value);
    	this->PutValue(sample,pos,value);

    }
}


void Libsvmdataset::SplitOneItem(const char* begin, const char* end, int &pos, double &value){
	butil::StringSplitter s_head(begin,end,':'),s_end(begin,end,':');
	s_end++;


	s_head.to_int(&pos);
	s_end.to_double(&value);
}


void Libsvmdataset::LoadData(std::string filename){
	this->_filename = filename;
	std::ifstream input;
	input.open(filename.c_str());
	std::string contain;
	contain.clear();


	int sample_id = 0;
	while(!input.eof())
	{
		std::getline(input,contain);
		this->FillMatrix_OneLine(contain,sample_id);
		sample_id++;
	}


}

void Libsvmdataset::OfferSample(std::vector<double> &Sample, int &label){
	this->DenseDataSet::OfferSample(Sample,label);
}




Libsvmdataset::~Libsvmdataset() {
	// TODO Auto-generated destructor stub
}

} /* namespace ParallelSGD */
