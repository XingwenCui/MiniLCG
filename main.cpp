#include <iostream>
#include <minisat/core/Solver.h>
#include "domain.h"
#include "Solver.h"




int main() {
    Minisat::Solver slv;
//    Minisat::Var nv = slv.newVar();
//    Minisat::Var nv2 = slv.newVar();
//    std::cout << "Hello, MiniSAT! var = " <<Minisat::toLit( toInt(Minisat::mkLit(nv,true))).x << ", next = " << toInt(Minisat::mkLit(nv2,true)) << std::endl;
//    std::cout<<nv<<" "<<nv2<<std::endl;

    elDomain d(&slv,2,10);
    elDomain d1(&slv,4,7);
    d.printDom();
    d1.printDom();





    return 0;
}
