//
// Created by Xingwen Cui on 19/2/2023.
//

#ifndef MINILCG_DOMAIN_H
#define MINILCG_DOMAIN_H
#include "minicpp/domain.hpp"
#include "minisat/core/Solver.h"
#include "iostream"

typedef Minisat::Solver sat_solver;
typedef Minisat::Var satvar;
class sparseSet {
    int _min, _max, _size, _ofs, _n;
    std::vector<int> _values;
    std::vector<int> _indexes;
    void exchangePositions(int val1,int val2);
    bool checkVal(int val) const { assert(val <= (int)_values.size()-1); return true;}
    bool internalContains(int val) const {
        if (val < 0 || val >= _n)
            return false;
        else return _indexes[val] < _size;
    }
    void updateBoundsValRemoved(int val);
    void updateMaxValRemoved(int val);
    void updateMinValRemoved(int val);
public:
    sparseSet(int n, int ofs)
    : _values(n),_indexes(n), _size(n),_min(0),_max(n-1),_ofs(ofs),_n(n)
    {
        for (int i = 0; i < n; i++)
            _values[i] = _indexes[i] = i;
    }

    bool isEmpty() const {return _size == 0;}
    int size() const {return _size;}
    int min() const {return _min + _ofs;}
    int max() const {return _max + _ofs;}
    bool contains(int val) const
    {
        val -= _ofs;
        if (val<0||val>=_n) return false;
        return _indexes[val] < _size; //the idx of value should be less than size, if large, it was removed
    }
    void removeAll() {_size = 0;}
    bool remove(int val);
    void removeAllBut(int val);
    void removeBelow(int val);
    void removeAbove(int val);
};

class sparseSetDomain {
    sparseSet _dom;
public:
    sparseSetDomain(int min, int max) : _dom(max-min+1, min){}
    int min() const { return _dom.min();}
    int max() const { return _dom.max();}
    int size() const { return _dom.size();}
    bool member(int v) const { return _dom.contains(v);}
    bool isBound() const { return _dom.size() == 1;}

    void remove(int v);
    void removeBelow(int newMin);
    void removeAbove(int newMax);
};

class elDomain{
private:
    int _min, _max, _size, _n, _ofs;
    std::vector<satvar> eqVector, geVector;
    satvar * lbptr, * ubptr;
    bool checkInDomain(int value) const { assert(value <= _max && value >= _min); return true;}
public:
    elDomain(int min, int max);

    int min() const {return this->_min;}
    int max() const {return this->_max;}
    int size() const {return this->_size;}
    std::vector<satvar> getEqVector() const {return eqVector;}
    std::vector<satvar> getGeVector() const {return geVector;}

    void setOfs(int ofs) {_ofs=ofs;}
    void setEqVector(int idx, int satVar) {eqVector[idx] = satVar;}
    void setGeVector(int idx, int satVar) {geVector[idx] = satVar;}
    void updateLb(int lb);
    void updateUb(int ub);

    int findVar(int val, bool eq = true);
    int findIdx(int val, bool eq = true);
};


#endif //MINILCG_DOMAIN_H
