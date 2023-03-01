
#include "domain.h"
//elDomain
elDomain::elDomain(sat_solver *solver, int min, int max)
    : _min(min), _max(max), _size(max-min+1), eqVector(_size), geVector(_size-2),_n(max-min+1){
    for (int i = 0; i < _size; i++){
        eqVector[i] = solver->newVar();
    }
    for (int j = 0; j < _size; j++){
        if (j == 0) {
            geVector[j] = eqVector[0];
            solver->setPolarity(geVector[j],Minisat::l_True);
            _lb = geVector[j];
        }
        else if (j == _size-1) {
            geVector[j] = eqVector[_size - 1];
            solver->setPolarity(geVector[j],Minisat::l_True);
            _ub = geVector[j];
        }
        else
            geVector[j] = solver->newVar();
    }
}

void elDomain::assign(sat_solver *s, int v, reason *r) {
    updateLb(s,v,r);
    updateUb(s,v,r);
    s->setPolarity(eqVector[v-_ofs],Minisat::l_True);
}

void elDomain::updateLb(sat_solver *s, int lb, reason *r) {
    checkInDomain(lb);
    assert(lb<=_ub);
    // Set original lower bound to l_Undef
    s->setPolarity(_lb,Minisat::l_Undef);

    if(lb == _min)  // lower bound == min
        _lb = eqVector[0] + _ofs;
    else if (lb == _ub)  //lower bound == upper bound
        _lb = _ub;
    else { // lower bound <lower bound < upper bound
        int gap = lb-_min; // the gap of lower bound - min value;
        _lb = geVector[gap - 1] + _ofs - _n + 1; //point to greater equal list
    }
    //set original lower bound to l_true
    s->setPolarity(_lb,Minisat::l_True);
}

void elDomain::updateUb(sat_solver *s, int ub, reason *r) {
    checkInDomain(ub);
    assert(ub>=_lb);
    //Set original ub to l_undef
    s->setPolarity(_ub, Minisat::l_Undef);

    if(ub == _max)  // lower bound == min
        _ub = eqVector[_n - 1] + _ofs;
    else if (ub == _lb)  //lower bound == upper bound
        _ub = _lb;
    else { // lower bound <lower bound < upper bound
        int gap = _max - ub; // the gap of lower bound - min value;
        _ub = geVector[_size - 2 - gap] + _ofs - _n + 1; //point to greater equal list
    }
    //Set new _ub to lTure
    s->setPolarity(_ub, Minisat::l_True);

}

int elDomain::findVar(int val, bool eq) {
    //input a value in domain, return the sar value of the sat var;
    checkInDomain(val);
    if (eq){
        return val+_ofs;
    } else {
        if (val == min() || val == max()){
            return val + _ofs;
        }
        else{
            return val + _ofs + size();
        }
    }
}

int elDomain::findIdx(int val, bool eq) {
    checkInDomain(val);
    if (eq||val == min() && val == max()){
        return val - min();
    } else {
        return val - min() - 1;
    }
}

int elDomain::toInt(int idx, bool isEq) {
    assert(idx<=_n-1);
    if (isEq){
        return eqVector[idx] + _ofs;
    } else {
        return geVector[idx] + _ofs - _n + 1;
    }
}

