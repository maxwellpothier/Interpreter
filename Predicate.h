#ifndef PREDICATE_H_
#define PREDICATE_H_
#include <string>
#include <vector>
#include "Parameter.h"
using namespace std;

class Predicate {
public:
    Predicate(string n) {
        name = n;
    }
    Predicate() {  }
    ~Predicate() {  }
    string name;
    vector<Parameter> parameterList;
    void addParameter(Parameter parameter) {
        parameterList.push_back(parameter);
    }
    void addParameter(vector<Parameter> parameters) {
        parameterList.insert(parameterList.end(),parameters.begin(), parameters.end());
    }
    string toString() {
        string out;
        out = name + "(";
        for (unsigned int i = 0; i < parameterList.size() - 1; i++) {
            out = out + parameterList[i].value + ",";
        }
        out += parameterList[parameterList.size() - 1].value + ")";
        return out;
    }
};


#endif /* PREDICATE_H_ */
