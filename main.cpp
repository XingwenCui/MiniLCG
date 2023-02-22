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

    std::cout<<"\n"<<x[0].min()<<std::endl;
    std::cout<<x[0].toInt(0,false)<<"\n"<<x[0].getEqVector()[0]<<std::endl;

    x[0].updateLb(5);
    x[0].updateUb(8);
    std::cout<<"The lower bound is: "<<x[0].getLb()<<std::endl;
    std::cout<<"The upper bound is: "<<x[0].getUb()<<std::endl;
    int xx = x[0].getEqVector()[0];
    std::cout<<xx<<std::endl;
    for (int i = 0; i < x[0].size(); i++){
        std::cout<<x[0].getEqVector()[i]<<" ";
    }


}

void SatTest(){
    using Minisat::mkLit;
    using Minisat::lbool;

    //create sat solver
    Minisat::Solver solver;

    //create variables
    auto A = solver.newVar();
    auto B = solver.newVar();
    auto C = solver.newVar();

    //create clauses A\/B\/C; -A\/B\/C; A\/-B\/C;A\/B\/-C;
    solver.addClause(mkLit(A), mkLit(B), mkLit(C));
    solver.addClause(~mkLit(A), mkLit(B), mkLit(C));
    solver.addClause(mkLit(A), ~mkLit(B), mkLit(C));
    solver.addClause(mkLit(A), mkLit(B), ~mkLit(C));
//    std::cout<<(solver.modelValue(A)==Minisat::l_True)<<std::endl;
    //check for solution and retrieve model if found
    auto sat = solver.solve();
    if (sat){
        std::cout<<"SAT\n"<<"Model found:\n";
        std::cout<<"A:="<<(solver.modelValue(A) == Minisat::l_True)<<"\n";
        std::cout<<"B:="<<(solver.modelValue(B) == Minisat::l_True)<<"\n";
        std::cout<<"C:="<<(solver.modelValue(C) == Minisat::l_True)<<"\n";
    } else {
        std::cout<<"UNSAT\n";
    }
}

//MINILCG sparseset follow MINIcp api
//reason x: ge(4,{y:ge(3)})

int main() {
    Minisat::Solver slv;
    Minisat::Var nv = slv.newVar();
    Minisat::Var nv2 = slv.newVar();

    minilcg_test();
//    return 0;
//    domain_test();
//    SatTest();
    std::cout << "Hello, MiniSAT! var = " << toInt(Minisat::mkLit(nv,true)) << ", next = " << toInt(Minisat::mkLit(nv2,true)) << std::endl;
    std::cout<<nv<<" "<<nv2<<std::endl;




    return 0;
}
