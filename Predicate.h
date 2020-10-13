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
    Predicate(){  }
    ~Predicate(){  }
    string name;
    vector<Parameter> parameterList;
    void addParameter(Parameter param) {
        parameterList.push_back(param);
    }
    void addParameter(vector<Parameter> params) {
        parameterList.insert(parameterList.end(),params.begin(), params.end());
    }
    string toString() {
        string output;
        output = name + "(";
        for(int i = 0; i < parameterList.size()-1; i++) {
            output = output + parameterList[i].value + ",";
        }
        output += parameterList[parameterList.size()-1].value + ")";
        return output;
    }
};



#endif /* PREDICATE_H_ */