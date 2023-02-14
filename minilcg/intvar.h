

#ifndef MINILCG_INTVAR_H
#define MINILCG_INTVAR_H

//#include
#include<iostream>
#include<vector>
using namespace std;

typedef int Var;
//class BitSet{
//public:
//    BitSet(int n){
//
//    };
//};

struct Lit {
    int     x;

    // Use this as a constructor:
    friend Lit mkLit(Var var, bool sign = false);

    bool operator == (Lit p) const { return x == p.x; }
    bool operator != (Lit p) const { return x != p.x; }
    bool operator <  (Lit p) const { return x < p.x;  } // '<' makes p, ~p adjacent in the ordering.
};

class intvar {
public:
    int n;
    vector<bool> eq; // [x=0,x=1,..,x=n-1]
    vector<bool> le; // [x<=0,x<=1,...,x<=n-1]

    intvar(int size){
        /*
         *  generate a variable's earger bool representation
         *  Int varibale initial domain is [0..n-1]
         *  The boolean representation has 2*n elements:
         *  [x=0,x=1,..,x=n-1];[x<=0,x<=1,..,x<=n-1] -> [1,1,..,1];[0,0,..,0,1]
         */
        eq = vectore<bool>(size,true);
        le = vectore<bool>(size-1,false);
        le.push_back(true);
    }

    int size(intvar i){
        int size = 0;
        for()
    }



};


#endif //MINILCG_INTVAR_H
