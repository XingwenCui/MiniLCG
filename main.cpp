#include <iostream>
#include <minisat/core/Solver.h>
#include "minicpp/solver.hpp"
#include "minicpp/intvar.hpp"
#include "minicpp/constraint.hpp"
#include "minicpp/search.hpp"


int main() {
    Minisat::Solver slv;
    Minisat::Var nv = slv.newVar();
    Minisat::Var nv2 = slv.newVar();
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
    return 0;

    std::cout << "Hello, MiniSAT! var = " << nv << ", next = " << nv2 << std::endl;


    return 0;
}
