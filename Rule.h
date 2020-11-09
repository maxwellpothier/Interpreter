#ifndef RULE_H_
#define RULE_H_
#include "Predicate.h"
using namespace std;

class Rule {
public:
    Rule() {  }
    ~Rule() {  }
    Predicate headPredicate;
    vector<Predicate> predicateList;
    void addHead(Predicate head) {
        headPredicate = head;
    }
    void addPredicate(Predicate toAdd) {
        predicateList.push_back(toAdd);
    }
    void addPredicate(vector<Predicate> predicateVector) {
        predicateList.insert(predicateList.end(), predicateVector.begin(), predicateVector.end());
    }
    string toString() {
        string out = headPredicate.toString() + " :- ";
        for (unsigned int i = 0; i < predicateList.size() - 1; i++) {
            out += predicateList[i].toString() + ",";
        }
        out += predicateList[predicateList.size() - 1].toString();
        return out;
    }
};


#endif /* RULE_H_ */
