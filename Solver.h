
#ifndef MINILCG_SOLVER_H
#define MINILCG_SOLVER_H
#include "iostream"
#include "minisat/core/Solver.h"
#include "IntVar.h" //Cant include this

namespace MiniLCG{
    typedef Minisat::Lit Lit;

    class Solver {
    private:
        Minisat::Solver *satSolver;
//        std::vector<IntVar> varList;
    public:
        Solver() : satSolver(new Minisat::Solver()) {}
//        std::vector<IntVar> getVarList() const {return varList;}
        Minisat::Solver *getSatSolver() const {return satSolver;}

//        void addNewVar(int min, int max);

    };
}



#endif //MINILCG_SOLVER_H
