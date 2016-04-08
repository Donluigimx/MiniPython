#include <iostream>
#include <streambuf>
#include <fstream>
#include <cstring>
#include "lexic.hpp"
#include "token.hpp"

#define inFileName "input.txt"

Lexic::Lexic(char* filename) {
    this->Analyze(filename);
    this->tokenPosition = 0;
    this->symbol = this->lexTokens[this->tokenPosition].first;
    this->type = this->lexTokens[this->tokenPosition].second;
}

void Lexic::Analyze(char* filename) {
    std::ifstream inFile;
    std::string symbol = "";
    int type;
    int actualState = 0;
    int inputValue;

    if( filename != nullptr) {
        inFile.open(filename)
    } else {
        inFile.open(inFileName);
    }

    std::string str((std::istreambuf_iterator<char>(inFile)),
                     std::istreambuf_iterator<char>());

    for(auto c: str) {

        inputValue = this->getValue(c);
        type = this->tokenMachine[actualState][inputValue];
        actualState = this->tokenMachine[actualState][inputValue];

        if (val != -1) {
            if (val == Token::ERROR)
                this->Error();
            lexTokens.push_back(std::pair<std::string, int>(symbol,type));
            symbol = "";
        }

        if( c == ' ')
            continue;

        symbol += c;
    }
}

int Lexic::getValue(char c) {

    if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
        return this->i3;
    if ( c >= '0' && c <= '9' )
        return this->i4;
    switch (c) {
        case '\s':
            return this->i0;
        case '\n':
            return this->i1;
        case '\t':
            return this->i2;
        case '+':
            return this->i5;
        case '-':
            return this->i6;
        case '*':
            return this->i7;
        case '/':
            return this->i8;
        case ':':
            return this->i9;
        case '<':
            return this->i10;
        case '>':
            return this->i11;
        case '=':
            return this->i12;
        case '!':
            return this->i13;
        case '(':
            return this->i14;
        case ')':
            return this->i15;
        case '_':
            return this->i16;
        case '.':
            return this->i17;
        default:
            return this->inv;
    }
}
