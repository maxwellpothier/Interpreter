#ifndef DATABASE_H_
#define DATABASE_H_
#include <map>
#include "Relation.h"
using namespace std;

class Database {
public:
    Database(){}
    ~Database(){}
    map<string, Relation> relations;
    string toString() {
        string out;
        for (std::map<string, Relation>::iterator it = relations.begin(); it != relations.end(); ++it) {
            out += it->second.toString() + "\n";
        }
        return out;
    }
};


#endif /* DATABASE_H_ */