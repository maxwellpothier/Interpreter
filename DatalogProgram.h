#ifndef DATALOGPROGRAM_H_
#define DATALOGPROGRAM_H_
#include <vector>
#include "Scheme.h"
#include "Rule.h"
using namespace std;

class DatalogProgram {
private:
    vector<Scheme> schemesList;
    vector<Scheme> factsList;
    vector<string> domain;
    vector<Rule> rulesList;
    vector<Predicate> queryList;
public:
    DatalogProgram(){  }
    ~DatalogProgram(){  }
    void addScheme(Scheme);
    void addFact(Scheme);
    void addRule(Rule);
    void addQuery(Predicate);
    void makeDomain();
    string toString();
    string intToString(int);
};


#endif /* DATALOGPROGRAM_H_ */