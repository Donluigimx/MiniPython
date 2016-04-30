#include <iostream>
#include <streambuf>
#include <fstream>
#include <cstring>
#include "lexic.hpp"
#include "token.hpp"

Lexic::Lexic(char* filename) {
    this->init();
    this->Analyze(filename);
    this->tokenPosition = 0;
    this->symbol = this->lexTokens[this->tokenPosition].first;
    this->type = this->lexTokens[this->tokenPosition].second;
}

void Lexic::init() {
    reserved.insert(std::pair<std::string,int>("if",Token::IF));
    reserved.insert(std::pair<std::string,int>("elif",Token::ELIF));
    reserved.insert(std::pair<std::string,int>("else",Token::ELSE));
    reserved.insert(std::pair<std::string,int>("while",Token::WHILE));
    reserved.insert(std::pair<std::string,int>("print",Token::PRINT));
}

void Lexic::Analyze(char* filename) {
    std::ifstream inFile;
    std::string symbol = "";
	bool isnewline;
    int type;
    int actualState = 0;
    int inputValue;
    int maxIndent;
    int contIndent;

    if( filename != nullptr) {
        inFile.open(filename, std::ios_base::in);
    } else {
        inFile.open(inFileName, std::ios_base::in);
    }
/* message */
    if (!inFile.good()) {
        exit(1);
    }
    std::string str((std::istreambuf_iterator<char>(inFile)),
                     std::istreambuf_iterator<char>());

    maxIndent = 0;
    contIndent = 0;
	isnewline = false;
    for(auto c: str) {
        inputValue = this->getValue(c);
        type = this->tokenMachine[actualState][inputValue];
        actualState = this->stateMachine[actualState][inputValue];
        if( c == '\t') {
            contIndent++;
        }
        if (type != -1) {
            if (isnewline) {
				if(type == Token::NEWLINE) {
					symbol = c;
					continue;
				}
				else if( contIndent > maxIndent ) {
					for(int i = maxIndent; i < contIndent; i++)
						lexTokens.push_back(std::pair<std::string, int>("INDENT",Token::INDENT));
				}
				else if ( contIndent < maxIndent) {
					for(int i = contIndent; i < maxIndent; i++)
						lexTokens.push_back(std::pair<std::string, int>("DEDENT",Token::DEDENT));
				}
                else if ( contIndent == maxIndent ) {
					//
                }
                maxIndent = contIndent;
                contIndent = 0;
				isnewline = false;
				if (type == Token::TAB) {
					symbol = c;
					continue;
				}
            }
			if (type == Token::IDENTIFIER) {
                if(reserved.find(symbol) != reserved.end()) {
                   type = reserved.find(symbol)->second;
                }
            }
			if (type == Token::NEWLINE) {
				isnewline = true;
			}
            if (type == Token::ERROR)
                this->Error();
            lexTokens.push_back(std::pair<std::string, int>(symbol,type));
            symbol = "";
        }

        if( c == ' ')
            continue;

        symbol += c;
    }
    type = this->tokenMachine[actualState][this->i0];
    if (type != -1) {
		if (type == Token::IDENTIFIER) {
			if(reserved.find(symbol) != reserved.end()) {
			   type = reserved.find(symbol)->second;
			}
		}
		if (type == Token::NEWLINE) {
			isnewline = true;
		}
		if (type == Token::ERROR)
			this->Error();
		if(isnewline) {
			if( contIndent > maxIndent ) {
				for(int i = maxIndent; i < contIndent; i++) {
					lexTokens.push_back(std::pair<std::string, int>("INDENT",Token::INDENT));
				}
			}
			else if ( contIndent < maxIndent) {
				for(int i = contIndent; i < maxIndent; i++)
				lexTokens.push_back(std::pair<std::string, int>("DEDENT",Token::DEDENT));
			}
			else if ( contIndent == maxIndent ) {
				//
			} else
			Error();
		}
		lexTokens.push_back(std::pair<std::string, int>(symbol,type));
    }

    lexTokens.push_back(std::pair<std::string, int>("$",Token::END_OF_FILE));
}

int Lexic::getValue(char c) {

    if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
        return this->i3;
    if ( c >= '0' && c <= '9' )
        return this->i4;
    switch (c) {
        case ' ':
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
        case '\r':
            return this->i18;
    }
    return this->inv;
}

void Lexic::Error() {
    std::ofstream outFile(outFileName, std::ios_base::out);

    outFile << 0;
    outFile.close();
    exit(0);
}

void Lexic::Next() {
    this->tokenPosition++;
    this->symbol = this->lexTokens[this->tokenPosition].first;
    this->type = this->lexTokens[this->tokenPosition].second;
}
