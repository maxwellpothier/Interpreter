#include "Interpreter.h"
#include "Token.h"
#include <iostream>

void Interpreter::interpret(string inFile) {
    p.parse(inFile);
    schemesList = p.schemesList;
    factsList = p.factsList;
    domain = p.domain;
    rulesList = p.rulesList;
    queryList = p.queryList;

    for (unsigned int i = 0; i < schemesList.size(); i++) {
        Relation newRelation;
        newRelation.setScheme(schemesList[i]);
        data.relations.insert(pair<string, Relation>(schemesList[i].name,newRelation));
    }

    for (unsigned int i = 0; i < factsList.size(); i++) {
        Tuple newTuple(factsList[i]);
        data.relations[factsList[i].name].addTuple(newTuple);
    }

    for (unsigned int i = 0; i < queryList.size(); i++) {
        Relation selects = data.relations[queryList[i].name];
        Relation projects;
        vector<int> projectsPos;
        vector<string> renameVals;
        for (unsigned int j = 0; j < queryList[i].parameterList.size(); j++) {
            Parameter temp = queryList[i].parameterList[j];
            if (temp.type == STRING) {
                selects = selects.select(j + 1, temp.value);
            }
        }
        for (unsigned int j = 0; j < queryList[i].parameterList.size(); j++) {
            for (unsigned int k = j+1; k < queryList[i].parameterList.size(); k++) {
                if (queryList[i].parameterList[j].value == queryList[i].parameterList[k].value) {
                    selects = selects.select(j,k);
                    break;
                }
            }
        }
        for (unsigned int k = 0; k < queryList[i].parameterList.size(); k++) {
            Parameter temp = queryList[i].parameterList[k];
            if (temp.type == ID) {
                bool exists = false;
                for (unsigned int x = 0; x < projectsPos.size(); x++) {
                    if (temp.value == renameVals[x]) {
                        exists = true;
                    }
                }
                if (!exists) {
                    projectsPos.push_back(k);
                    renameVals.push_back(temp.value);
                }
            }
        }
        projects = selects.project(projectsPos);
        Scheme tempScheme(queryList[i].name);
        tempScheme.addParameter(renameVals);
        projects.setScheme(tempScheme);
        cout << queryList[i].toString() << "? ";
        if ((selects.tupleList).empty()) {
            cout << "No" << endl;
        }
        else if ((projects.tupleList).empty()) {
            cout << "Yes(1)" << endl;
        }
        else {
            cout << "Yes(" << projects.tupleList.size() << ")" << endl;
            for (set<Tuple>::iterator i = projects.tupleList.begin(); i != projects.tupleList.end(); ++i) {
                cout << "  ";
                int count = 0;
                for (unsigned int x = 0; x < projects.scheme.parameterList.size(); x++) {
                    if (count != 0) {
                        cout << ", ";
                    }
                    cout  << projects.scheme.parameterList[x] << "=" << (*i)[count];
                    count++;
                }
                cout << endl;
            }
        }
    }
}
