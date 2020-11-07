#ifndef PARSER_H_
#define PARSER_H_
#include "Scanner.h"
#include "Scheme.h"
#include "DatalogProgram.h"

class Parser {
private:
    vector<Token> tokenList;
    DatalogProgram program;
    Scanner lexer;
public:
    Parser() {  }
    ~Parser() {  }

    void parse(string);
    Token getToken();
    void match(tokenType t);
    void error();
    void toString();
    void parseScheme();
    void parseSchemeList();
    void parseFactList();
    void parseFact();
    void parseRuleList();
    void parseRule();
    Predicate headPredicate();
    Predicate parsePredicate();
    vector<Predicate> parsePredicateList();
    Parameter parseParameter();
    vector<Parameter> parseParameterList();
    string parseExpression();
    string parseOperator();
    void parseQuery();
    void parseQueryList();
    vector<string> idList();
    vector<string> stringList();

    Token tkn;
    vector<Scheme> schemesList;
    vector<Scheme> factsList;
    vector<string> domain;
    vector<Rule> rulesList;
    vector<Predicate> queryList;
};


#endif /* PARSER_H_ */