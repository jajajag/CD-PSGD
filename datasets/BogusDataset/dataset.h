/*
 * dataset.h
 *
 *  Created on: Sep 10, 2019
 *      Author: tomcheng
 */

#ifndef DATASET_H_
#define DATASET_H_
#include <vector>
#include <string>

namespace ParallelSGD {

class dataset {
protected:
	std::string _filename;
public:
	void SetFilename(std::string filename){
		_filename=filename;
	}
	dataset();
	virtual ~dataset();
	virtual void OfferSample(std::vector<double> &SampleVect, int &label)=0;
	virtual void LoadData(std::string filename)=0;
	void LoadData(){
		this->LoadData(this->_filename);
	}

};

} /* namespace ParallelSGD */

#endif /* DATASET_H_ */
