#include "DatalogProgram.h"
#include <sstream>
#include <algorithm>

void DatalogProgram::addScheme(Scheme scheme) {
    schemesList.push_back(scheme);
}

void DatalogProgram::addFact(Scheme fact) {
    factsList.push_back(fact);
    domain.insert(domain.end(), fact.parameterList.begin(), fact.parameterList.end());
}

void DatalogProgram::addRule(Rule rule) {
    rulesList.push_back(rule);
}

void DatalogProgram::addQuery(Predicate predicate) {
    queryList.push_back(predicate);
}

void DatalogProgram::makeDomain() {
    sort(domain.begin(), domain.end());
    domain.erase(unique(domain.begin(), domain.end()), domain.end());
}

string DatalogProgram::toString() {
    string out;
    out = "Schemes(" + intToString(schemesList.size()) + "):\n";
    for (unsigned int i = 0; i < schemesList.size(); i++) {
        out += "  " + schemesList[i].toString() + "\n";
    }
    out += "Facts(" + intToString(factsList.size()) +  "):\n";
    for (unsigned int i = 0; i < factsList.size(); i++) {
        out += "  " + factsList[i].toString() + ".\n";
    }
    out += "Rules(" + intToString(rulesList.size()) + "):\n";
    for (unsigned int i = 0; i < rulesList.size(); i++) {
        out += "  " + rulesList[i].toString() + ".\n";
    }
    out += "Queries(" + intToString(queryList.size()) + "):\n";
    for (unsigned int i = 0; i < queryList.size(); i++) {
        out += "  " + queryList[i].toString() + "?\n";
    }
    out += "Domain(" + intToString(domain.size()) + "):\n";
    for (unsigned int i = 0; i < domain.size(); i++) {
        out += "  " + domain[i] + "\n";
    }
    return out;
}

string DatalogProgram::intToString(int toConvert) {
    ostringstream oss;
    oss << toConvert;
    return oss.str();
}
