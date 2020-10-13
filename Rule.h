#ifndef RULE_H_
#define RULE_H_
#include "Predicate.h"
using namespace std;

class Rule {
public:
    Rule(){  }
    ~Rule(){  }
    Predicate headPredicate;
    vector<Predicate> predList;
    void addHead(Predicate a) {
        headPredicate = a;
    }
    void addPred(Predicate x) {
        predList.push_back(x);
    }
    void addPred(vector<Predicate> v) {
        predList.insert(predList.end(), v.begin(), v.end());
    }
    string toString() {
        string output = headPredicate.toString() + " :- ";
        for(unsigned int i = 0; i < predList.size()-1; i++) {
            output += predList[i].toString() + ",";
        }
        output += predList[predList.size()-1].toString();
        return output;
    }
};



#endif /* RULE_H_ */