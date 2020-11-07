#include "Relation.h"
#include "Token.h"
#include "Parameter.h"

void Relation::setScheme(Scheme s) {
    scheme = s;
}

void Relation::addTuple(Tuple tuple) {
    tupleList.insert(tuple);
}

string Relation::toString() {
    string out;
    out = scheme.toString() + "\n";
    for (set<Tuple>::iterator i = tupleList.begin(); i != tupleList.end(); ++i) {
        out += (*i).toString() + "\n";
    }
    out += "\n";
    return out;
}

Relation Relation::select(int position, string value) {
    Relation temp;
    temp.setScheme(scheme);
    for (set<Tuple>::iterator i = tupleList.begin(); i != tupleList.end(); ++i) {
        if ((*i)[position] == value) {
            temp.addTuple(*i);
        }
    }
    return temp;
}

Relation Relation::select(int pos1, int pos2) {
    Relation temp;
    temp.setScheme(scheme);
    for (set<Tuple>::iterator i = tupleList.begin(); i != tupleList.end(); ++i) {
        if ((*i)[pos1 + 1] == (*i)[pos2 + 1]) {
            temp.addTuple(*i);
        }
    }
    return temp;
}

Relation Relation::project(vector<int> position) {
    Relation newRelation;
    newRelation.setScheme(scheme);
    if (!position.empty()) {
        for (set<Tuple>::iterator i = tupleList.begin(); i != tupleList.end(); ++i) {
            Tuple temp;
            for(int j = 0; j < position.size(); j++) {
                temp.push_back((*i)[position[j] + 1]);
            }
            newRelation.addTuple(temp);
        }
    }
    return newRelation;
}