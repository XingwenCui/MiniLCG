//
// Created by Xingwen Cui on 19/2/2023.
//

#ifndef MINILCG_DOMAIN_H
#define MINILCG_DOMAIN_H
#include "minicpp/domain.hpp"
#include "minisat/core/Solver.h"
#include "reason.h"
#include "iostream"

typedef Minisat::Solver sat_solver;
typedef Minisat::Var satvar;

struct intNotifier   {
    virtual void empty() = 0;
    virtual void bind() = 0;
    virtual void change() = 0;
    virtual void changeMin() = 0;
    virtual void changeMax() = 0;
};


class elDomain{
private:
    int _min, _max, _size, _n, _ofs;
    std::vector<satvar> eqVector, geVector;
    satvar _lb, _ub;
    bool checkInDomain(int value) const { assert(value <= _max && value >= _min); return true;}
public:
    elDomain(sat_solver * solver, int min, int max);

    int min() const {return this->_min;}
    int max() const {return this->_max;}
    int size() const {return this->_size;}
    std::vector<satvar> getEqVector() const {return eqVector;}
    std::vector<satvar> getGeVector() const {return geVector;}
    int getOfs() const {return _ofs;}
    void setOfs(int ofs) {_ofs=ofs;}

    bool isFix() const {return size() == 1;}
    bool isEmpty() const {return size() == 0;}
    satvar getLb() const {return _lb;}
    satvar getUb() const {return _ub;}
    int toInt(int idx, bool isEq);

    void assign(sat_solver *s, int v, reason *r = NULL);
    void remove(sat_solver *s, int v, reason *r = NULL);
    void updateLb(sat_solver *s, int lb,  reason *r = NULL);
    void updateUb(sat_solver *s, int ub,  reason *r = NULL);

    int findVar(int val, bool eq = true);
    int findIdx(int val, bool eq = true);

    //print to test the domain
    void printDom(){
        std::cout<<"The equal vector's vars are: ";
        for (int i = 0; i < _size; i++){
            std::cout<<eqVector[i]<<" ";
        }
        std::cout<<std::endl;
        std::cout<<"The greater vector's vars are: ";
        for (int i = 0; i < _size; i++){
            std::cout<<geVector[i]<<" ";
        }
    }
};


#endif //MINILCG_DOMAIN_H
