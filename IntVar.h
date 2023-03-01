
#ifndef MINILCG_INTVAR_H
#define MINILCG_INTVAR_H
#include "domain.h"
#include "Solver.h"

class IntVar {
private:
    elDomain * dom;
    MiniLCG::Solver * solver;
public:
    IntVar(MiniLCG::Solver *slv, int min, int max){
        solver = slv;
        dom = new elDomain(solver->getSatSolver(),min,max);
    }
    IntVar(MiniLCG::Solver *slv, int n) : IntVar(slv, 0, n-1){}

    elDomain* getDom() const {return dom;}
    MiniLCG::Solver *getSolver() const {return solver;}

    int min() const {return dom->min();}
    int max() const {return dom->max();}
    int size() const {return dom->size();}
    bool isBound(int v) const {return dom->isFix();}
    bool contain(int v) const {return dom->contain(v);}

    void assign(int v, reason *r=NULL) {dom->assign(solver->getSatSolver(),v,r);}
    void remove(int v, reason *r=NULL) {dom->remove(solver->getSatSolver(),v,r);}
    void updateLB(int v, reason *r=NULL) {dom->updateLb(solver->getSatSolver(),v,r);}
    void updateUB(int v, reason *r=NULL) {dom->updateUb(solver->getSatSolver(),v,r);}


};


#endif //MINILCG_INTVAR_H
