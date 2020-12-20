//============================================================================
// Name        : batchSGD.cpp
// Author      : ChengDaning
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "string_splitter.h"
#include <string>
#include "stdlib.h"
#include <iostream>
#include "Libsvmdataset.h"
#include "LinearSparsityBogusDataset.h"
#include "RelativeLinearSparsityBogusDataSet.h"
using namespace std;


void test_split(){
	     string the_string_to_split = "123:0.5 234:0.6 521:0.7";
	     butil::StringSplitter s(the_string_to_split.c_str(), ' '),s1(the_string_to_split.c_str(), ' ');
	     s1++;

	     for( ; s ; ++s,++s1) {
	    	 int pos = -1;
	    	 double value = -1;
	    	 butil::StringSplitter s_inner(s.field(),s1.field(),':');
	    	 s_inner.to_int(&pos);
	    	 ++s_inner;
	    	 s_inner.to_double(&value);

	         cout<<endl<<endl<<pos<<" "<<value<<endl<<endl;
	     }
}
void test_libsvmdataset(){
	string filename="/home/tomcheng/workspace/batchSGD/dataset/libsvm_test.dat";
	ParallelSGD::Libsvmdataset dataset(5,9,filename);
	dataset.LoadData(filename);
	dataset.ShowContent();
}
void test_LinearSparsityBogusDataSet(){
	ParallelSGD::LinearSparsityBogusDataSet  LSBS(20);
	//LSBS.SetParameters(0.5,500,1000000,20,1,10000);
	LSBS.SetParameters(0.3,0,10000,3,1000);
	LSBS.LoadData();
	std::vector<double> samplevec;

	for(unsigned int cnt = 0;cnt<100;cnt++){
		int label;
		LSBS.OfferSample(samplevec,label);
		cout<<label<<endl<<flush;
		for(unsigned int i = 0 ; i < samplevec.size() ; i++){
			cout<<samplevec[i]<<" "<<flush;
		}
		cout<<endl<<flush;
	}


}
void test_RelativeLinearSparsityBogusDataSet(){
	ParallelSGD::RelativeLinearSparsityBogusDataSet  LSBS(20);
	//LSBS.SetParameters(0.5,500,1000000,20,1,10000);
	LSBS.SetParameters(0.3,0,10000,3,1000);
	LSBS.LoadData();
	std::vector<double> samplevec;

	for(unsigned int cnt = 0;cnt<100;cnt++){
		int label;
		LSBS.OfferSample(samplevec,label);
		cout<<label<<endl<<flush;
		for(unsigned int i = 0 ; i < samplevec.size() ; i++){
			cout<<samplevec[i]<<" "<<flush;
		}
		cout<<endl<<flush;
	}


}
int main(){
	test_LinearSparsityBogusDataSet();
}
