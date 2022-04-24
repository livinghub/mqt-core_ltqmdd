/*	动态最小化测试
 * This file is part of IIC-JKU QFR library which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum/ for more information.
 */

#include "QuantumComputation.hpp"
#include "algorithms/QFT.hpp"
#include "algorithms/Grover.hpp"
#include "algorithms/GoogleRandomCircuitSampling.hpp"
#include <ctime>

using namespace std;
using namespace chrono;


int main(int argc, char *argv[]) {

	
	clock_t start,end;
	double endtime;

	//读取real文件
	std::string fileName = "./circuits/test.real";
	if(argc==1)
    {
		std::cout<<"没有输入参数,使用默认电路"<<std::endl;

 	}
	else fileName = argv[1];

	// std::cout << std::endl << std::endl << "********************" << std::endl << "电路：" << fileName << std::endl;
	qc::QuantumComputation qc(fileName);
	//qc::QFT qc(16);

	//*********************对比动态最小化
	// auto dd = make_unique<dd::Package>(); // create an instance of the DD package
	// auto functionality = qc.buildFunctionality(dd);
	// std::cout << "原始dd大小：" << dd->size(functionality) << std::endl;

	//动态最小化
	std::cout <<fileName<<"    ";
	auto ddmin = make_unique<dd::Package>(); // create an instance of the DD package
	qc::permutationMap varMap{};
	start=clock();
	auto functionalitymin = qc.buildFunDynLinSift(ddmin, varMap);
	// auto functionalitymin = qc.buildFunDynSift(ddmin, varMap);
	end=clock();
	endtime=(double)(end-start)/CLOCKS_PER_SEC;
	//auto functionalitymin = qc.buildFunctionality(ddmin);
	//qc.printMatrix(dd, functionality, std::cout); //输出矩阵
	//dd::export2Dot(functionalitymin, "test-real-min.dot"); //输出QMDD表示文件
	std::cout << "动态ls大小 :" << ddmin->size(functionalitymin) <<"    Total time:"<<endtime; //输出原始dd的大小
	//qc::permutationMap varMap = qc.initialLayout;
	//auto reorderdd = ddmin->dynamicReorder(functionalitymin, varMap, dd::DynamicReorderingStrategy::Sifting);
	// int sifting_size = ddmin->size(functionalitymin);
	// std::cout << "min接着Sifting后dd大小：" << sifting_size << std::endl; //输出重排后dd的大小

	// // auto dd = make_unique<dd::Package>(); // create an instance of the DD package
	// auto functionality = qc.buildFunctionality(ddmin, varMap);
	// if(!ddmin->equals(functionality, functionalitymin)) {
	// 	std::cout <<"    DD不等    "<<ddmin->size(functionality);
	// }
	// // std::cout << "原始dd大小：" << dd->size(functionality) << std::endl;
	
	std::cout<<std::endl;
	return 0;
}

