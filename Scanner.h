#ifndef SCANNER_H_
#define SCANNER_H_
#include "Token.h"
#include <fstream>
#include <vector>

class Scanner {
private:
    ifstream inFile;
    ofstream outFile;
    int line = 1;
    char parse;
    char next;
    string value = "";
    string valueUpper = "";
    int lineStart = 0;
    vector<Token> myVector;
public:
    Scanner() {  }
    ~Scanner() {  }
    void scan(string);
    void scanToken();
    void scanID();
    void scanStr();
    void scanComm();
    void makeToken(tokenType type, int lineNum);
    void valueToUpper();
    vector<Token> getVector();
};


#endif /* SCANNER_H_ */