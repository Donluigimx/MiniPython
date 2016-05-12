#include <iostream>
#include <fstream>
#include "syntactic.hpp"
#include "token.hpp"

int main(int argc, char const *argv[]) {
    char *filename = nullptr;
    if (argc == 2) {
        filename = (char*)argv[1];
    }
    Syntactic *syntactic = new Syntactic(filename);
    std::ofstream outFile(outFileName, std::ios_base::out);
    if (syntactic->tree->semanticAnalysis() == 1) {
		syntactic->tree->code(outFile);
	} else {
		std::cout << "/* message */" << std::endl;
	}
    outFile.close();
    return 0;
}
