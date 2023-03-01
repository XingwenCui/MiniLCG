#include <iostream>
#include <minisat/core/Solver.h>
#include "domain.h"
#include "Solver.h"
#include "IntVar.h"



int main() {
    Minisat::Solver slv;
//    Minisat::Var nv = slv.newVar();
//    Minisat::Var nv2 = slv.newVar();
//    std::cout << "Hello, MiniSAT! var = " <<Minisat::toLit( toInt(Minisat::mkLit(nv,true))).x << ", next = " << toInt(Minisat::mkLit(nv2,true)) << std::endl;
//    std::cout<<nv<<" "<<nv2<<std::endl;

//    elDomain d(&slv,2,10);
//    elDomain d1(&slv,4,7);
//    d.printDom();
//    d1.printDom();
//    std::cout<<d1.getOfs()<<std::endl;

    MiniLCG::Solver s;
    elDomain dom(s.getSatSolver(),2,10);
    dom.printDom();
    elDomain dom2(s.getSatSolver(),3,6);
    dom2.printDom();

    IntVar v1(&s,2,10);
    v1.getDom()->printDom();


    return 0;
}
