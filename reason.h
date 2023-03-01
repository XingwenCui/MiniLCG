//
// Created by Xingwen Cui on 23/2/2023.
//

#ifndef MINILCG_REASON_H
#define MINILCG_REASON_H
#include "minisat/core/Solver.h"
#include "iostream"
#include "vector"




using Minisat::Lit;

class reason {
    private:
        std::vector<Lit> reasonLit;
        Lit outcome;

    public:
        reason(){};
        reason(Lit outcome, std::vector<Lit> reasonList) : outcome(outcome), reasonLit(reasonList){}

        std::vector<Lit> toClause() {
            std::vector<Lit> clauseList;
            for (int i = 0; i < reasonLit.size(); i++) {
                clauseList.push_back(~reasonLit[i]);
            }
            clauseList.push_back(outcome);
            return clauseList;
        }
    };



#endif //MINILCG_REASON_H
