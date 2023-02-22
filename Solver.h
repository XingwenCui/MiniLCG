//
// Created by Xingwen Cui on 20/2/2023.
//

#ifndef MINILCG_SOLVER_H
#define MINILCG_SOLVER_H
#include "var.h"
#include "domain.h"

namespace MiniLCG{
    typedef Minisat::Lit Lit;



    class Solver {
    public:
        sat_solver satSolver;
        std::vector<elDomain> varList;

        Solver();

        std::vector<elDomain> getVarList() const {return varList;}
        void addnewVar(int min, int max);







    };
}



#endif //MINILCG_SOLVER_H
