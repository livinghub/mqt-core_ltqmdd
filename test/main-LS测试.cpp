/*
 * This file is part of IIC-JKU QFR library which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum/ for more information.
 */

#include "QuantumComputation.hpp"
#include "algorithms/QFT.hpp"
#include "algorithms/Grover.hpp"
#include "algorithms/GoogleRandomCircuitSampling.hpp"

using namespace std;
using namespace chrono;

int main(int argc, char *argv[]) {

	//读取real文件
	std::string fileName = "./circuits/test.real";
	if(argc==1)
    {
		std::cout<<"没有输入参数,使用默认电路"<<std::endl;

 	}
	else fileName = argv[1];

	std::cout << std::endl << std::endl << "********************" << std::endl << "电路：" << fileName << std::endl;
	qc::QuantumComputation qc(fileName);

	auto dd = make_unique<dd::Package>(); // create an instance of the DD package
	auto functionality = qc.buildFunctionality(dd);
	//qc.printMatrix(dd, functionality, std::cout); //输出矩阵
	dd::export2Dot(functionality, "test-real.dot"); //输出QMDD表示文件
	std::cout << "原始dd大小：" << dd->size(functionality) << std::endl; //输出原始dd的大小

	auto ddmin = make_unique<dd::Package>(); // create an instance of the DD package
	auto functionalitymin = qc.buildFunctionalityMin(ddmin);
	//qc.printMatrix(dd, functionality, std::cout); //输出矩阵
	dd::export2Dot(functionalitymin, "test-real-min.dot"); //输出QMDD表示文件
	std::cout << "原始dd大小：" << dd->size(functionalitymin) << std::endl; //输出原始dd的大小

/*	qc::permutationMap varMap = qc.initialLayout; //复制电路的初始变量映射
	qc::permutationMap ltvarMap = varMap;
	qc.printPermutationMap(varMap); //打印初始映射

	// 调用sifting重排算法
	auto reorderdd = dd->dynamicReorder(functionality, varMap, dd::DynamicReorderingStrategy::Sifting);
	//qc.printMatrix(dd, reorderdd, std::cout); //输出矩阵
	dd::export2Dot(reorderdd, "reorderdd.dot"); //输出QMDD表示文件
	int sifting_size = dd->size(reorderdd);
	std::cout << "Sifting后dd大小：" << sifting_size << std::endl; //输出重排后dd的大小
	qc.printPermutationMap(varMap); //输出重排后的变量映射关系

	//sifting 到收敛
	for(int convs=0; convs!=sifting_size;)
	{
		convs=sifting_size;
		reorderdd = dd->dynamicReorder(functionality, varMap, dd::DynamicReorderingStrategy::Sifting);
		sifting_size = dd->size(reorderdd);
	}
	std::cout << "Sifting收敛后dd大小：" << sifting_size << std::endl; //输出重排后dd的大小
	qc.printPermutationMap(varMap); //输出重排后的变量映射关系

	//新建一个dd
	//qc::QuantumComputation qc2(fileName);
	auto dd_new = make_unique<dd::Package>(); // create an instance of the DD package
	auto functionality_new = qc.buildFunctionality(dd_new);

	// 调用lt重排算法
	auto ltreod = dd_new->dynamicReorder(functionality_new, ltvarMap, dd::DynamicReorderingStrategy::linearSift);
	//qc.printMatrix(dd, reorderdd, std::cout); //输出矩阵
	dd::export2Dot(ltreod, "ltreod.dot"); //输出QMDD表示文件
	int lt_size = dd_new->size(ltreod);
	std::cout << "linearSifting后dd大小：" << lt_size << std::endl; //输出重排后dd的大小
	qc.printPermutationMap(ltvarMap); //输出重排后的变量映射关系

	//sifting 到收敛
	for(int convs=0; convs!=lt_size;)
	{
		convs=lt_size;
		ltreod = dd_new->dynamicReorder(functionality_new, ltvarMap, dd::DynamicReorderingStrategy::linearSift);
		lt_size = dd_new->size(ltreod);
	}
	std::cout << "Sifting收敛后dd大小：" << lt_size << std::endl; //输出重排后dd的大小
	qc.printPermutationMap(ltvarMap); //输出重排后的变量映射关系

	//输出lt次数
	std::cout << "ex-count:" << dd_new->exchange_base_cases << ";	lt-count:" << dd_new->linear_in_place << std::endl;
	std::cout << "有效LT次数： " << dd_new->valid_LT_Num << std::endl;
	
	//打印lt矩阵
/*	for(int i=0; i<dd::MAXN; ++i)
	{
		for(int j=0; j<dd::MAXN; ++j) std::cout << dd->xorMat[i][j] << " ";
		std::cout<<std::endl;
	}	
*/
	//判断重排前后dd是否一致
	//std::cout << "重排电路是否一致： " << dd->equals(functionality, reorderdd) << std::endl;

	

	return 0;
}
