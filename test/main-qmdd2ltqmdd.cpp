/*
 * This file is part of IIC-JKU QFR library which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum/ for more information.
 */


/* QMDD to LTQMDD test */

#include "QuantumComputation.hpp"
#include "algorithms/QFT.hpp"
#include "algorithms/Grover.hpp"
#include "algorithms/GoogleRandomCircuitSampling.hpp"
#include <ctime>

using namespace std;
using namespace chrono;


void test_qmdd2ltqmdd(std::string fileName) {

	qc::QuantumComputation qc(fileName);
	
	// ***********************************************
	//创建一个dd实例
	auto dd = make_unique<dd::Package>(); // create an instance of the DD package
	auto functionality = qc.buildFunctionality(dd);
	//qc.printMatrix(dd, functionality, std::cout); //输出矩阵
	//dd::export2Dot(functionality, "test-real.dot"); //输出QMDD表示文件
	std::cout << "原始dd大小：" << dd->size(functionality) << std::endl; //输出原始dd的大小

	qc::permutationMap varMap = qc.initialLayout; //复制电路的初始变量映射
	// qc.printPermutationMap(varMap); //打印初始映射

	// 调用linear sifting重排算法
	dd->xorInit(varMap);
	auto reorderdd = dd->dynamicReorder(functionality, varMap, dd::DynamicReorderingStrategy::linearSift);
	int sifting_size = dd->size(reorderdd);
	std::cout << std::endl << "Linear Sifting后dd大小：" << sifting_size << std::endl; //输出重排后dd的大小
	// qc.printPermutationMap(varMap); //输出重排后的变量映射关系
	// dd->printLTMap(varMap);
	// dd->printLTMat(varMap);

	//linearsifting 到收敛
	for(int convs=0; convs!=sifting_size;)
	{
		convs=sifting_size;
		auto ltreod = dd->dynamicReorder(functionality, varMap, dd::DynamicReorderingStrategy::linearSift);
		sifting_size = dd->size(ltreod);
	}
	std::cout << "Linear Sifting收敛后dd大小：" << sifting_size << std::endl; //输出重排后dd的大小
	// qc.printPermutationMap(varMap); //输出重排后的变量映射关系
	// dd->printLTMap(varMap);


	//**************************************************
	//新建一个dd_new实例
	qc::permutationMap ltvarMap = qc.initialLayout;
	auto dd_new = make_unique<dd::Package>(); // create an instance of the DD package
	auto functionality_new = qc.buildFunctionality(dd_new, ltvarMap);
	// functionality_new = dd->dynamicReorder(functionality_new, ltvarMap, dd::DynamicReorderingStrategy::linearSift);

	
	bool xmat[128][128]{};
	//qmdd ----(movetab)---> ltqmdd
	// for(auto &i:dd->opSeq) cout<<i<<' ';
	dd_new->opSeq = dd->opSeq;
	dd_new->qmdd2ltqmdd(functionality_new, ltvarMap, xmat);

	auto mycpy = dd->depthCopyDD(functionality_new);

	dd_new->printDD(functionality_new, 100);
	dd->printDD(functionality, 100);
	dd->printDD(mycpy, 100);


	auto tmp = dd->multiply(mycpy, functionality);
	std::clog<<dd->size(tmp)<<std::endl;

	
	if(!dd->equals(functionality, mycpy)) {throw logic_error("dd不等");	}
	unsigned int lt_size = dd_new->size(functionality_new);
	std::cout << std::endl << "qmdd --(movetab)--> ltqmdd后dd大小：" << lt_size << std::endl; //输出重排后dd的大小
	// qc.printPermutationMap(ltvarMap); //输出重排后的变量映射关系
	// dd->printLTMap(ltvarMap, xmat);
}

void test_ltqmdd2qmdd(std::string fileName) {
	qc::QuantumComputation qc(fileName);
	
	// ***********************************************
	//创建一个dd实例
	auto dd = make_unique<dd::Package>(); // create an instance of the DD package
	auto functionality = qc.buildFunctionality(dd);
	std::cout << "原始dd大小：" << dd->size(functionality) << std::endl; //输出原始dd的大小

	qc::permutationMap varMap = qc.initialLayout; //复制电路的初始变量映射
	qc.printPermutationMap(varMap); //打印初始映射

	// 调用linear sifting重排算法
	auto reorderdd = dd->dynamicReorder(functionality, varMap, dd::DynamicReorderingStrategy::linearSift);
	int sifting_size = dd->size(reorderdd);
	std::cout << std::endl << "Linear Sifting后dd大小：" << sifting_size << std::endl; //输出重排后dd的大小
	// qc.printPermutationMap(varMap); //输出重排后的变量映射关系
	dd->printLTMap(varMap);

	//dd->printMovetab(dd->Movetab);
	dd->ltqmdd2qmdd(reorderdd, varMap, dd->xorMat);
	int new_size = dd->size(reorderdd);
	std::cout << std::endl << "ltqmdd->qmdd后的dd大小：" << new_size << std::endl; //输出重排后dd的大小
	// qc.printPermutationMap(varMap); //输出重排后的变量映射关系
	dd->printLTMap(varMap);
}


// 测试qmdd2ltqmdd
int main(int argc, char *argv[]) {
	//读取real文件
	std::string fileName = "./circuits/test.real";
	if(argc==1)	std::cout<<"没有输入参数,使用默认电路"<<std::endl;
	else fileName = argv[1];

	std::cout << std::endl << std::endl << "********************" << std::endl << "电路：" << fileName << std::endl;
	
	test_qmdd2ltqmdd(fileName);
	// test_ltqmdd2qmdd(fileName);

	return 0;
}



