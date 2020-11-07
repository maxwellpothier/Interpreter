#include "Token.h"
#include <sstream>

string Token::print() {
    string out;
    out = "(" + tokenMap[type] + ",\"" + value + "\"," + lineToString() + ")";
    return out;
}

string Token::lineToString() {
    ostringstream oss;
    oss << line;
    return oss.str();
}