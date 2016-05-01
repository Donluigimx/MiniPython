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
    outFile << syntactic->tree->semanticAnalysis() << std::endl;
    outFile.close();
    return 0;
}
