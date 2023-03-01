

#ifndef MINILCG_INTVAR_H
#define MINILCG_INTVAR_H
#include "domain.h"

class IntVar {
private:
    elDomain * dom;
    sat_solver * solver;

public:
    IntVar(sat_solver& slv, int min, int max);
    IntVar(sat_solver& slv, int n) : IntVar(slv, 0, n-1){}

    int min() const {return dom->min();}
    int max() const {return dom->max();}
    int size() const {return dom->size();}
    bool isBound(int v) const {return dom->isFix();}

};


#endif //MINILCG_INTVAR_H
