#include "Token.h"
#include <sstream>
string Token::print() {
    string output;
    output = "(" + tokenMap[type] + ",\"" + value + "\"," + lineToString() + ")";
    return output;
}

string Token::lineToString() {
    stringstream convert;
    convert << line;
    string lineNum = convert.str();
    return lineNum;
}