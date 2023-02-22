#include <iostream>
#include <minisat/core/Solver.h>
#include "minicpp/solver.hpp"
#include "minicpp/intvar.hpp"
#include "minicpp/constraint.hpp"
#include "minicpp/search.hpp"
#include "var.h"
#include "domain.h"
#include "Solver.h"


void minicpp_test(){
    using namespace Factory;
    using namespace std;
    const int n = 12;

    CPSolver::Ptr cp = Factory::makeSolver();
    auto q = Factory::intVarArray(cp,n,1,n);
    cp->post(Factory::allDifferentAC(q));
    cp->post(Factory::allDifferentAC(Factory::intVarArray(cp,n,[q](int i) {
        return q[i] + i;
    })));
    cp->post(Factory::allDifferentAC(Factory::intVarArray(cp,n,[q](int i) {
        return q[i] - i;
    })));
    DFSearch search(cp,[=]() {
        auto x = selectMin(q,
                           [](const auto& x) { return x->size() > 1;},
                           [](const auto& x) { return x->size();});
        if (x) {
            int c = x->min();
            return  [=] { cp->post(x == c);}
                    | [=] { cp->post(x != c);};
        } else return Branches({});
    });

    //search.onSolution([&q]() { cout << "sol = " << q << endl;});

    auto stat = search.solve();
    /*
    auto stat = search.solve([](const SearchStatistics& s) {
                                return RuntimeMonitor::elapsedSince(s.startTime()) > 100;
                             });
    */
    cout << stat << endl;

    cp.dealloc();
}


void minilcg_test() {
    MiniLCG::Solver slv;
    slv.addnewVar(3,10);
    slv.addnewVar(2,5);

    auto x = slv.getVarList();
    for (int i = 0; i < x[0].size(); i++){
        std::cout<<Minisat::mkLit(x[0].getEqVector()[i], true).x<<" ";
    }
    std::cout<<std::endl;
    for (int i = 0; i < x[0].size()-2; i++){
        std::cout<<~Minisat::mkLit(x[0].getGeVector()[i],true).x<<" ";
    }
}

//MINILCG sparseset follow MINIcp api
//reason x: ge(4,{y:ge(3)})

int main() {
    Minisat::Solver slv;
    Minisat::Var nv = slv.newVar();
    Minisat::Var nv2 = slv.newVar();

//    minilcg_test();
//    return 0;
//    domain_test();

    std::cout << "Hello, MiniSAT! var = " << toInt(Minisat::mkLit(nv,true)) << ", next = " << toInt(Minisat::mkLit(nv2,true)) << std::endl;
    std::cout<<nv<<" "<<nv2<<std::endl;



    return 0;
}
