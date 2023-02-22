//
// Created by Xingwen Cui on 20/2/2023.
//

#include "Solver.h"

MiniLCG::Solver ::Solver() {}


void MiniLCG::Solver ::addnewVar(int min, int max) {
    elDomain val(min,max);
    for (int idx = 0; idx < val.size(); idx++){
        int satVar = satSolver.newVar();
        val.setEqVector(idx,satVar);
        if (idx == 0){
            val.setOfs(val.min()-satVar); //if Var list is [1,2,3], orginal domain is [7,8,9]
        }
    }
    for (int idx = 0; idx < val.size()-2; idx++) {
        int satVar = satSolver.newVar();
        val.setGeVector(idx,satVar);
    }
    val.initBound();
    varList.push_back(val);
}