#include "Scanner.h"
#include <cctype>
#include <iostream>

void Scanner::scan(string fileName) {
    file.open(fileName.c_str());
    if(file) {
        while(file.get(parse)) {
            scanToken();
        }
        makeToken(END, line);
        outFile.open("output.txt");
        for(int i = 0; i < tokenVector.size(); i++) {
            outFile << tokenVector[i].print() << endl;
        }
        outFile << "Total Tokens = " << tokenVector.size();
        outFile.close();
    }
    else {
        cout << "File did not load"<< endl;
    }
}

void Scanner::scanToken() {
    while(isspace(parse)) {
        if(parse == '\n') line++;
        file.get(parse);
        if(file.eof()) break;
    }
    switch (parse) {
        case ',':
            value = ",";
            makeToken(COMMA, line);
            break;
        case '.':
            value = ".";
            makeToken(PERIOD, line);
            break;
        case '?':
            value = "?";
            makeToken(Q_MARK, line);
            break;
        case '(':
            value = "(";
            makeToken(LEFT_PAREN, line);
            break;
        case ')':
            value = ")";
            makeToken(RIGHT_PAREN, line);
            break;
        case '*':
            value = "*";
            makeToken(MULTIPLY, line);
            break;
        case '+':
            value = "+";
            makeToken(ADD, line);
            break;
        case ':':
            value = ":";
            next = file.peek();
            if(next == '-') {
                value = ":-";
                makeToken(COLON_DASH, line);
                file.get(parse);
            }
            else {
                makeToken(COLON, line);
            }
            break;
        case '\'':
            scanStr();
            break;
        case '#':
            scanComm();
            break;
        default:
            if(isalpha(parse)) scanID();
            else if(!file.eof()) {
                value += parse;
                makeToken(UNDEFINED, line);
            }
            break;
    }
}

void Scanner::scanID() {
    value += parse;
    file.get(parse);
    while(isalnum(parse)) {
        value += parse;
        file.get(parse);
    }
    valueToUpper();
    if(valueUpper == "SCHEMES") makeToken(SCHEMES, line);
    else if(valueUpper == "FACTS") makeToken(FACTS, line);
    else if(valueUpper == "RULES") makeToken(RULES, line);
    else if(valueUpper == "QUERIES") makeToken(QUERIES, line);
    else makeToken(ID, line);
    scanToken();
}

void Scanner::scanStr() {
    bool endOfString = false;
    value += parse;
    lineStart = line;
    while(endOfString == false) {
        if(file.peek() == -1) {
            makeToken(UNDEFINED, lineStart);
            endOfString = true;
        }
        else {
            file.get(parse);
            switch(parse) {
                case '\n':
                    line++;
                    value += parse;
                    break;
                case '\'':
                    value += parse;
                    next = file.peek();
                    if(next != '\'') {
                        makeToken(STRING, lineStart);
                        endOfString = true;
                    }
                    else {
                        file.get(parse);
                        value += parse;
                    }
                    break;
                default:
                    value += parse;
                    break;
            }
        }
    }
}

void Scanner::scanComm() {
    value += parse;
    lineStart = line;
    next = file.peek();
    if(next != '|') {
        file.get(parse);
        while(parse != '\n') {
            value += parse;
            file.get(parse);
        }
        if(parse == '\n') {
            line++;
        }
        makeToken(COMMENT, lineStart);
    }
    else {
        file.get(parse);
        value += parse;
        file.get(parse);
        next = file.peek();
        while((parse != '|' || next != '#') && !file.eof()) {
            if(parse == '\n') line++;
            value += parse;
            file.get(parse);
            next = file.peek();
        }
        if(parse == '|' && next == '#') {
            value += parse;
            file.get(parse);
            value += parse;
            makeToken(COMMENT, lineStart);
        }
        else if(file.eof()) {
            makeToken(UNDEFINED, lineStart);
        }
    }
}

void Scanner::makeToken(tokenType type, int lineNum) {
    Token newToken(type, value, lineNum);
    if(type != COMMENT) {
        tokenVector.push_back(newToken);
    }
    value = "";
    valueUpper = "";
}

void Scanner::valueToUpper() {
    for(int i = 0; i < value.length(); i++) {
        valueUpper += toupper(value[i]);
    }
}

vector<Token> Scanner::getVector() {
    return tokenVector;
}