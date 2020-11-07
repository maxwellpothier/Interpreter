#ifndef SCHEME_H_
#define SCHEME_H_
#include <string>
#include <vector>
using namespace std;

class Scheme {
public:
    Scheme(string n) {
        name = n;
    }
    Scheme() {  }
    ~Scheme() {  }
    string name;
    vector<string> parameterList;
    void addName(string n) {
        name = n;
    }
    void addParameter(string parameter) {
        parameterList.push_back(parameter);
    }
    void addParameter(vector<string> parameters) {
        parameterList.insert(parameterList.end(), parameters.begin(), parameters.end());
    }
    void editParameter(int position, string value) {
        parameterList[position] = value;
    }
    string toString() {
        string out;
        out = name + "(";
        for (int i = 0; i < parameterList.size() - 1; i++) {
            out = out + parameterList[i] + ",";
        }
        out += parameterList[parameterList.size() - 1] + ")";
        return out;
    }
};


#endif /* SCHEME_H_ */