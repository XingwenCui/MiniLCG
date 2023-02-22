//
// Created by Xingwen Cui on 19/2/2023.
//

#include "domain.h"


// sparseSet
void sparseSet::exchangePositions(int val1, int val2) {
    int i1 = _indexes[val1], i2 = _indexes[val2];
    _values[i1] = val2; _values[i2] = val1;
    _indexes[val1] = i2; _indexes[val2] = i1;
}

void sparseSet::updateMinValRemoved(int val) {
    if (!isEmpty() && _min == val){ //confirm not empty
        assert(!internalContains(val));
        //the min is removed, search the new one
        for (int v=val+1; v <= _max; v++){
            if (internalContains(v)){ //update from _min, if in the domain, change min to v
                _min = v;
                return;
            }
        }
    }
}

void sparseSet::updateMaxValRemoved(int val) {
    if (!isEmpty() && _max == val) {
        assert(!internalContains(val));
        //the max is removed, search the new one
        for (int v = val-1; v >= _min; v--) {
            if (internalContains(v)){
                _max = v;
                return;
            }
        }

    }
}

void sparseSet::updateBoundsValRemoved(int val) {
    updateMaxValRemoved(val);
    updateMinValRemoved(val);
}

bool sparseSet::remove(int val){
    if (!contains(val)){
        return false;
    }
    val -= _ofs;
    assert(checkVal(val)); //val in the set
    int s = _size; //exchange the val to the last index->s
    exchangePositions(val, _values[s-1]);
    _size = s - 1;
    updateBoundsValRemoved(val); // if is bound, change it
    return true;
}

void sparseSet::removeAllBut(int val) {
    assert(contains(val));
    val -= _ofs;
    assert(checkVal(val));
    exchangePositions(val, _values[0]);
    _min = val; _max = val; _size = 1;
}

void sparseSet::removeBelow(int val) {
    if (max()<val) removeAll();
    else{
        for (int v = min(); v<val; v++)
            remove(v);
    }
}

void sparseSet::removeAbove(int val) {
    if (min()>val) removeAll();
    else{
        for (int v = val+1; v <= max(); v++){
            remove(v);
        }
    }
}


// SparseSetDomain
void sparseSetDomain::remove(int v){
    _dom.remove(v);
}

void sparseSetDomain::removeAbove(int newMax) {
    _dom.removeAbove(newMax);
}

void sparseSetDomain::removeBelow(int newMin) {
    _dom.removeBelow(newMin);
}

//elDomain
elDomain::elDomain( int min, int max)
    : _min(min), _max(max), _size(max-min+1), eqVector(_size), geVector(_size-2),_n(max-min+1){}

void elDomain::updateLb(int lb) {
    checkInDomain(lb);
    assert(lb<=_ub);
    if(lb == _min)  // lower bound == min
        _lb = eqVector[0] + _ofs;
    else if (lb == _ub)  //lower bound == upper bound
        _lb = _ub;
    else { // lower bound <lower bound < upper bound
        int gap = lb-_min; // the gap of lower bound - min value;
        _lb = geVector[gap - 1] + _ofs - _n + 1; //point to greater equal list
    }
}

void elDomain::updateUb(int ub) {
    checkInDomain(ub);
    assert(ub>=_lb);
    if(ub == _max)  // lower bound == min
        _ub = eqVector[_n - 1] + _ofs;
    else if (ub == _lb)  //lower bound == upper bound
        _ub = _lb;
    else { // lower bound <lower bound < upper bound
        int gap = _max - ub; // the gap of lower bound - min value;
        _ub = geVector[_size - 2 - gap] + _ofs - _n + 1; //point to greater equal list
    }
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

