#include "QuantumComputation.hpp"
#include "algorithms/QFT.hpp"
#include "algorithms/Grover.hpp"
#include "algorithms/GoogleRandomCircuitSampling.hpp"

using namespace std;

void printMap(const qc::permutationMap &map) {
    for(auto rit = map.rbegin(); rit != map.rend(); ++rit) {
        cout<<rit->first<<':'<<rit->second<<endl;
    }
}

int main(int argc, char *argv[]) {

    clock_t start;

    //读取real文件
	std::string fileName = "./circuits/test.real";
	if(argc==1)
    {
		std::cout<<"没有输入参数,使用默认电路"<<std::endl;

 	}
	else fileName = argv[1];

	// std::cout << std::endl << std::endl << "********************" << std::endl << "电路：" << fileName << std::endl;
	qc::QuantumComputation qc(fileName);

    auto dd = make_unique<dd::Package>(); // create an instance of the DD package
    start=clock();
    // auto functionality = qc.buildFunctionality(dd);
    // pair<dd::Edge, dd::Edge> func(functionality, functionality);
    pair<dd::Edge, pair<uint32_t, uint32_t>> func, func2;
    qc::permutationMap inMap;
    // func = qc.buildFunDyn(dd, inMap, dd::dynBuildStrat::None);
    // func = qc.buildFunctionalityFlat(dd, inMap);
    func = qc.buildFunctionality(dd, inMap);
    auto origalSize = dd->size(func.first);

    /////test
    /////////////test
    std::clog<<origalSize<<' '<<dd->naiveCount(func.first)<<std::endl;
    // exit(0);
    ////////////////
    //////

    // clog<<origalSize<<endl;
    // func.first = qc.buildFunDynLinSift(dd, inMap);
    // auto f1 = qc.buildFunFlatDyn(dd, dd::dynBuildStrat::None);
    // func.first = f1.first;


    // dd->dynLinearSifting(func.first, func.second, true);
    // dd->dynSifting(func.first, func.second);
    

    // auto oldroot = func.first;
    // func.first = dd->renormalize(func.first);
    // dd->decRef(oldroot);
    // dd->incRef(func.first);
    // dd->sifting(func.first, func.second);
    dd->lbLinearAndSiftingAux(func.first, inMap);
    // dd->linearAndSiftingAux(func.first, inMap, true);

    // dd->printIndToVar(inMap);
    auto preSize = 0;
    // while(preSize != dd->size(func.first)) {
    //     preSize = dd->size(func.first);
    //     dd->dynSifting(func.first, inMap);
    //     // dd->dynLinearSifting(func.first, inMap, true);
    //     // dd->dynLinearSifting(func.first, inMap);
    // }
    auto siftingSize = dd->size(func.first);
    auto siftingTime = (double)(clock()-start)/CLOCKS_PER_SEC;

    preSize = 0;
    // while(preSize != dd->size(func.first)) {
    //     preSize = dd->size(func.first);
    //     // dd->dynSifting(func.first, inMap);
    //     // dd->sifting(func.first, inMap);
    //     // dd->dynLinearSifting(func.first, inMap, true);
    //     // dd->dynLinearSifting(func.first, inMap);
    //     dd->lbLinearAndSiftingAux(func.first, inMap);
    // }
    auto s_lsSize = preSize;
    auto s_lsTime = (double)(clock()-start)/CLOCKS_PER_SEC;

	// auto endtime1=(double)(clock()-start)/CLOCKS_PER_SEC;
    // cout<<dd->size(func.first)<<" time:"<<endtime<<endl;
    // auto func2 = qc.buildFunctionality(dd, func.second);
    // cout<<dd->size(func2)<<endl;

    // auto dd2 = make_unique<dd::Package>(); // create an instance of the DD package
    // start=clock();
    // // func2 = qc.buildFunDyn(dd2, inMap, dd::dynBuildStrat::InOrder);
    // func2 = qc.buildFunctionality(dd2, inMap);

    // // preSize = 0;
    // // while(preSize != dd2->size(func2.first)) {
    // //     preSize = dd2->size(func2.first);
    // //     // dd2->dynSifting(func.first, inMap);
    // //     // dd2->dynLinearSifting(func.first, inMap, true);
    // //     dd2->dynLinearSifting(func2.first, inMap);
    // // }

	// auto endtime2=(double)(clock()-start)/CLOCKS_PER_SEC;
    // // cout<<dd2->size(f2.first)<<" time:"<<endtime<<endl;
    // // auto f22 = qc.buildFunctionality(dd2, f2.second);
    // // cout<<dd->size(f22)<<endl;

    cout<<fileName<<' '<<func.second.first<<' '<<func.second.second<<' '<<origalSize<<' '<<siftingSize<<' '<<siftingTime<<' '<<s_lsSize<<' '<<s_lsTime<<endl;
    // cout<<fileName<<' '<<dd->size(func.first)<<' '<<endtime1<<endl;
    // cout<<fileName<<' '<<dd2->size(func2.first)<<' '<<endtime2<<endl;
    return 0;
}