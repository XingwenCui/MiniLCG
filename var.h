

#ifndef MINILCG_VAR_H
#define MINILCG_VAR_H

#include "minisat/core/Solver.h"
#include "minicpp/intvar.hpp"
#include "minicpp/solver.hpp"
#include "domain.h"

#include "iostream"
#include "algorithm"

namespace MiniLCG {

    typedef Minisat::Lit Lit;
    typedef Minisat::Solver sat_solver;
    typedef Minisat::Var sat_var;


    class intvar_el {
    public:
        intvar_el();

        int min() const {return _min;}
        int max() const {return _max;}
        int size() const {return _max-_min+1;}
        std::vector<sat_var> getEqLits() const {return EqLits;}
        std::vector<sat_var> getGeLits() const {return GeLits;}

        void changeMin(int newMin) { assert(newMin>=this->_min); this->_min = newMin;}
        void changeMax(int newMax) { assert(newMax<=this->_max); this->_max = newMax;}

    private:
        int _min;
        int _max;
        std::vector<sat_var> EqLits;
        std::vector<sat_var> GeLits;
        var<int>::Ptr intvar;
    };

}
#endif //MINILCG_VAR_H
