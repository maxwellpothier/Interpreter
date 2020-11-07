#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#include "Parser.h"
#include "Database.h"
using namespace std;

class Interpreter {
private:
    Parser p;
    Database data;
public:
    Interpreter(){  }
    ~Interpreter(){  }
    void interpret(string);
    vector<Scheme> schemesList;
    vector<Scheme> factsList;
    vector<string> domain;
    vector<Rule> rulesList;
    vector<Predicate> queryList;
};


#endif /* INTERPRETER_H_ */