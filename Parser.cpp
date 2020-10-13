#include "Parser.h"
#include "Rule.h"
#include "Parameter.h"
#include <algorithm>
#include <iostream>

void Parser::parse() {
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

    cout << "Success!\n" << program.toString();
}

void Parser::match(tokenType t) {
    if(tkn.type == t) {
        tkn = tokenList[0];
        tokenList.erase(tokenList.begin());
    }
    else
        error();
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
    if(tkn.type != FACTS) {
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
    if(tkn.type != RULES) {
        parseFact();
        parseFactList();
    }
}

void Parser::parseRuleList() {
    if(tkn.type != QUERIES) {
        parseRule();
        parseRuleList();
    }
}

void Parser::parseRule() {
    Rule newRule;
    newRule.addHead(headPredicate());
    match(COLON_DASH);
    newRule.addPred(parsePredicate());
    newRule.addPred(parsePredicateList());
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
    newHead.addParameter(initial);
    match(ID);
    temp = idList();
    for(unsigned int i = 0; i < temp.size(); i++) {
        Parameter a;
        a.value = temp[i];
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
    if(tkn.type != PERIOD && tkn.type != QUERIES) {
        match(COMMA);
        newPredList.push_back(parsePredicate());
        vector<Predicate> temp = parsePredicateList();
        newPredList.insert(newPredList.end(), temp.begin(), temp.end());
    }
    return newPredList;
}

Parameter Parser::parseParameter() {
    Parameter newParam;
    if(tkn.type == STRING) {
        newParam.value = tkn.value;
        match(STRING);
    }
    else if(tkn.type == ID) {
        newParam.value = tkn.value;
        match(ID);
    }
    else {
        newParam.value = parseExpression();
    }
    return newParam;
}

vector<Parameter> Parser::parseParameterList() {
    vector<Parameter> newParamList;
    if(tkn.type != RIGHT_PAREN) {
        match(COMMA);
        newParamList.push_back(parseParameter());
        vector<Parameter> temp = parseParameterList();
        newParamList.insert(newParamList.end(), temp.begin(), temp.end());
    }
    return newParamList;
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
    if(tkn.type == ADD) {
        match(ADD);
        return "+";
    }
    else if(tkn.type == MULTIPLY) {
        match(MULTIPLY);
        return "*";
    }
    else {
        error();
        return 0;
    }
}

void Parser::parseQuery() {
    program.addQuery(parsePredicate());
    match(Q_MARK);
}

void Parser::parseQueryList() {
    if(tkn.type != END) {
        parseQuery();
        parseQueryList();
    }

}

vector<string> Parser::idList() {
    vector<string> myList;
    if(tkn.type != RIGHT_PAREN) {
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
    if(tkn.type != RIGHT_PAREN) {
        match(COMMA);
        myList.push_back(tkn.value);
        match(STRING);
        vector<string> temp = stringList();
        myList.insert(myList.end(), temp.begin(), temp.end());
    }
    return myList;
}