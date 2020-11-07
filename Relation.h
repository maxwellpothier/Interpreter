#ifndef RELATION_H_
#define RELATION_H_
#include "Tuple.h"
#include <iostream>
#include <set>
using namespace std;

class Relation {
public:
    Relation() {  }
    ~Relation() {  }

    void setScheme(Scheme);
    void addTuple(Tuple);
    string toString();
    Relation select(int, string);
    Relation select(int, int);
    Relation project(vector<int>);
    string printResult();
    set<Tuple> tupleList;
    Scheme scheme;
};


#endif /* RELATION_H_ */