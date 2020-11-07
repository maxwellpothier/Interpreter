#include "Scanner.h"
#include <fstream>
#include <cctype>
#include <iostream>

void Scanner::scan(string file) {
    inFile.open(file.c_str());
    if (inFile) {
        while (inFile.get(parse)) {
            scanToken();
        }
        makeToken(END, line);
        outFile.open("output.txt");
        for (int i = 0; i < myVector.size(); i++) {
            outFile << myVector[i].print() << endl;
        }
        outFile << "Total Tokens = " << myVector.size();
        outFile.close();
    }
    else {
        cout << "File did not load" << endl;
    }
}

void Scanner::scanToken() {
    while (isspace(parse)) {
        if (parse == '\n') line++;
        inFile.get(parse);
        if(inFile.eof()) break;
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
            next = inFile.peek();
            if (next == '-') {
                value = ":-";
                makeToken(COLON_DASH, line);
                inFile.get(parse);
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
            if (isalpha(parse)) scanID();
            else if (!inFile.eof()) {
                value += parse;
                makeToken(UNDEFINED, line);
            }
            break;
    }
}

void Scanner::scanID() {
    value += parse;
    inFile.get(parse);
    while (isalnum(parse)) {
        value += parse;
        inFile.get(parse);
    }
    valueToUpper();
    if (valueUpper == "SCHEMES") makeToken(SCHEMES, line);
    else if (valueUpper == "FACTS") makeToken(FACTS, line);
    else if (valueUpper == "RULES") makeToken(RULES, line);
    else if (valueUpper == "QUERIES") makeToken(QUERIES, line);
    else makeToken(ID, line);
    scanToken();
}

void Scanner::scanStr() {
    bool endOfString = false;
    value += parse;
    lineStart = line;
    while (endOfString == false) {
        if (inFile.peek() == -1) {
            makeToken(UNDEFINED, lineStart);
            endOfString = true;
        }
        else {
            inFile.get(parse);
            switch(parse) {
                case '\n':
                    line++;
                    value += parse;
                    break;
                case '\'':
                    value += parse;
                    next = inFile.peek();
                    if (next != '\'') {
                        makeToken(STRING, lineStart);
                        endOfString = true;
                    }
                    else {
                        inFile.get(parse);
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
    next = inFile.peek();
    if (next != '|') {
        inFile.get(parse);
        while (parse != '\n') {
            value += parse;
            inFile.get(parse);
        }
        if (parse == '\n') line++;
        makeToken(COMMENT, lineStart);
    }
    else {
        inFile.get(parse);
        value += parse;
        inFile.get(parse);
        next = inFile.peek();
        while ((parse != '|' || next != '#') && !inFile.eof()) {
            if (parse == '\n') line++;
            value += parse;
            inFile.get(parse);
            next = inFile.peek();
        }
        if (parse == '|' && next == '#') {
            value += parse;
            inFile.get(parse);
            value += parse;
            makeToken(COMMENT, lineStart);
        }
        else if (inFile.eof()) makeToken(UNDEFINED, lineStart);
    }
}

void Scanner::makeToken(tokenType type, int lineNum) {
    Token newToken(type, value, lineNum);
    if (type != COMMENT) {
        myVector.push_back(newToken);
    }
    value = "";
    valueUpper = "";
}

void Scanner::valueToUpper() {
    for (int i = 0; i < value.length(); i++) {
        valueUpper += toupper(value[i]);
    }
}

vector<Token> Scanner::getVector() {
    return myVector;
}