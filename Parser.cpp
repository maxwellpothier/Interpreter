#include "Parser.h"
#include "Rule.h"
#include "Parameter.h"
#include <algorithm>
#include <iostream>

void Parser::parse(string inFile) {
    lexer.scan(inFile);
    tokenList = lexer.getVector();
    tkn = tokenList[0];
    tokenList.erase(tokenList.begin());

    match(SCHEMES);
    match(COLON);
    parseScheme();
    parseSchemeList();

    match(FACTS);
    match(COLON);
    parseFactList();
    program.makeDomain();

    match(RULES);
    match(COLON);
    parseRuleList();

    match(QUERIES);
    match(COLON);
    parseQuery();
    parseQueryList();

    schemesList = program.schemesList;
    factsList = program.factsList;
    domain = program.domain;
    rulesList = program.rulesList;
    queryList = program.queryList;
}

void Parser::match(tokenType t) {
    if (tkn.type == t) {
        tkn = tokenList[0];
        tokenList.erase(tokenList.begin());
    }
    else {
        error();
    }
}

void Parser::error() {
    cout << "Failure!\n  " << tkn.print() << endl;
    exit(EXIT_SUCCESS);
}

void Parser::parseScheme() {
    Scheme newScheme(tkn.value);
    match(ID);
    match(LEFT_PAREN);
    newScheme.addParameter(tkn.value);
    match(ID);
    newScheme.addParameter(idList());
    match(RIGHT_PAREN);

    program.addScheme(newScheme);
}

void Parser::parseSchemeList() {
    if (tkn.type != FACTS) {
        parseScheme();
        parseSchemeList();
    }
}

void Parser::parseFact() {
    Scheme newFact(tkn.value);
    match(ID);
    match(LEFT_PAREN);
    newFact.addParameter(tkn.value);
    match(STRING);
    newFact.addParameter(stringList());
    match(RIGHT_PAREN);
    match(PERIOD);

    program.addFact(newFact);
}

void Parser::parseFactList() {
    if (tkn.type != RULES) {
        parseFact();
        parseFactList();
    }
}

void Parser::parseRuleList() {
    if (tkn.type != QUERIES) {
        parseRule();
        parseRuleList();
    }
}

void Parser::parseRule() {
    Rule newRule;
    newRule.addHead(headPredicate());
    match(COLON_DASH);
    newRule.addPredicate(parsePredicate());
    newRule.addPredicate(parsePredicateList());
    match(PERIOD);

    program.addRule(newRule);
}

Predicate Parser::headPredicate() {
    Predicate newHead(tkn.value);
    Parameter initial;
    vector<Parameter> pList;
    vector<string> temp;
    match(ID);
    match(LEFT_PAREN);
    initial.value = tkn.value;
    initial.type = ID;
    newHead.addParameter(initial);
    match(ID);
    temp = idList();
    for (int i = 0; i < temp.size(); i++) {
        Parameter a;
        a.value = temp[i];
        a.type = ID;
        pList.push_back(a);
    }
    newHead.addParameter(pList);
    match(RIGHT_PAREN);
    return newHead;
}

Predicate Parser::parsePredicate() {
    Predicate newPred(tkn.value);
    match(ID);
    match(LEFT_PAREN);
    newPred.addParameter(parseParameter());
    newPred.addParameter(parseParameterList());
    match(RIGHT_PAREN);
    return newPred;
}

vector<Predicate> Parser::parsePredicateList() {
    vector<Predicate> newPredList;
    if (tkn.type != PERIOD && tkn.type != QUERIES) {
        match(COMMA);
        newPredList.push_back(parsePredicate());
        vector<Predicate> temp = parsePredicateList();
        newPredList.insert(newPredList.end(), temp.begin(), temp.end());
    }
    return newPredList;
}

Parameter Parser::parseParameter() {
    Parameter newParameter;
    if (tkn.type == STRING) {
        newParameter.value = tkn.value;
        newParameter.type = STRING;
        match(STRING);
    }
    else if (tkn.type == ID) {
        newParameter.value = tkn.value;
        newParameter.type = ID;
        match(ID);
    }
    else {
        newParameter.value = parseExpression();
        newParameter.value = ID;
    }
    return newParameter;
}

vector<Parameter> Parser::parseParameterList() {
    vector<Parameter> newParameterList;
    if (tkn.type != RIGHT_PAREN) {
        match(COMMA);
        newParameterList.push_back(parseParameter());
        vector<Parameter> temp = parseParameterList();
        newParameterList.insert(newParameterList.end(), temp.begin(), temp.end());
    }
    return newParameterList;
}

string Parser::parseExpression() {
    string exp = "(";
    match(LEFT_PAREN);
    exp += parseParameter().value + " ";
    exp += parseOperator() + " ";
    exp += parseParameter().value;
    match(RIGHT_PAREN);
    exp += ")";
    return exp;
}

string Parser::parseOperator() {
    if (tkn.type == ADD) {
        match(ADD);
        return "+";
    }
    else if (tkn.type == MULTIPLY) {
        match(MULTIPLY);
        return "*";
    }
    else {
        error();
    }
}

void Parser::parseQuery() {
    program.addQuery(parsePredicate());
    match(Q_MARK);
}

void Parser::parseQueryList() {
    if (tkn.type != END) {
        parseQuery();
        parseQueryList();
    }
}

vector<string> Parser::idList() {
    vector<string> myList;
    if (tkn.type != RIGHT_PAREN) {
        match(COMMA);
        myList.push_back(tkn.value);
        match(ID);
        vector<string> temp = idList();
        myList.insert(myList.end(), temp.begin(), temp.end());
    }
    return myList;
}

vector<string> Parser::stringList() {
    vector<string> myList;
    if (tkn.type != RIGHT_PAREN) {
        match(COMMA);
        myList.push_back(tkn.value);
        match(STRING);
        vector<string> temp = stringList();
        myList.insert(myList.end(), temp.begin(), temp.end());
    }
    return myList;
}