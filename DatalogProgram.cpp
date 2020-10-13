#include "DatalogProgram.h"
#include <sstream>
#include <algorithm>

void DatalogProgram::addScheme(Scheme s) {
    schemesList.push_back(s);
}

void DatalogProgram::addFact(Scheme f) {
    factsList.push_back(f);
    domain.insert(domain.end(), f.parameterList.begin(), f.parameterList.end());
}

void DatalogProgram::addRule(Rule r) {
    rulesList.push_back(r);
}

void DatalogProgram::addQuery(Predicate p) {
    queryList.push_back(p);
}

void DatalogProgram::makeDomain() {
    sort(domain.begin(), domain.end());
    domain.erase(unique(domain.begin(), domain.end()), domain.end());
}

string DatalogProgram::toString() {
    string output;
    output = "Schemes(" + intToString(schemesList.size()) + "):\n";
    for(int i = 0; i < schemesList.size(); i++) {
        output += "  " + schemesList[i].toString() + "\n";
    }
    output += "Facts(" + intToString(factsList.size()) +  "):\n";
    for(int i = 0; i < factsList.size(); i++) {
        output += "  " + factsList[i].toString() + ".\n";
    }
    output += "Rules(" + intToString(rulesList.size()) + "):\n";
    for(int i = 0; i < rulesList.size(); i++) {
        output += "  " + rulesList[i].toString() + ".\n";
    }
    output += "Queries(" + intToString(queryList.size()) + "):\n";
    for(int i = 0; i < queryList.size(); i++) {
        output += "  " + queryList[i].toString() + "?\n";
    }
    output += "Domain(" + intToString(domain.size()) + "):\n";
    for(int i = 0; i < domain.size(); i++) {
        output += "  " + domain[i] + "\n";
    }
    return output;
}

string DatalogProgram::intToString(int x) {
    stringstream convert;
    convert << x;
    string output = convert.str();
    return output;
}