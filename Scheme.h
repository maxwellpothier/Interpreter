#ifndef SCHEME_H_
#define SCHEME_H_
#include <string>
using namespace std;

class Scheme {
public:
    Scheme(string n) {
        name = n;
    }
    ~Scheme(){  }
    string name;
    vector<string> parameterList;
    void addParameter(string param) {
        parameterList.push_back(param);
    }
    void addParameter(vector<string> params) {
        parameterList.insert(parameterList.end(),params.begin(), params.end());
    }

    string toString() {
        string output;
        output = name + "(";
        for(unsigned int i = 0; i < parameterList.size()-1; i++) {
            output = output + parameterList[i] + ",";
        }
        output += parameterList[parameterList.size()-1] + ")";
        return output;
    }
};



#endif /* SCHEME_H_ */