//
// Created by Xingwen Cui on 20/2/2023.
//

#include "Solver.h"

MiniLCG::Solver ::Solver() {}


void MiniLCG::Solver ::addnewVar(int min, int max) {
    elDomain var(&this->satSolver, min, max);
    varList.push_back(var);
}