#ifndef TUPLE_H_
#define TUPLE_H_
#include <string>
#include "Scheme.h"
using namespace std;

class Tuple : public vector<string> {
public:
    Tuple(Scheme scheme) {
        push_back(scheme.name);
        for (unsigned int i = 0; i < scheme.parameterList.size(); i++) {
            push_back(scheme.parameterList[i]);
        }
    }
    Tuple() {  }
    ~Tuple() {  }

    string toString() const {
        string out;
        for (vector<string>::const_iterator i = this->begin(); i != this->end(); ++i) {
            out +=  *i + "  ";
        }
        return out;
    }
};


#endif /* TUPLE_H_ */
