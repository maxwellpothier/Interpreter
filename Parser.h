#ifndef PARSER_H_
#define PARSER_H_
#include "Scanner.h"
#include "scheme.h"
#include "DatalogProgram.h"

class Parser {
private:
    vector<Token> tokenList;
    DatalogProgram program;
    Scanner lexer;
    Token tkn;
public:
    Parser(string inputFile) {
        lexer.scan(inputFile);
        tokenList = lexer.getVector();
        tkn = tokenList[0];
        tokenList.erase(tokenList.begin());
    }
    ~Parser(){  }
    void parse();
    void match(tokenType);
    void error();
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
};






#endif /* PARSER_H_ */