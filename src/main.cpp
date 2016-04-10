#include <iostream>
#include "lexic.hpp"

int main(int argc, char const *argv[]) {
    char *filename = nullptr;
    if (argc == 2) {
        filename = (char*)argv[1];
    }
    Lexic *lexic = new Lexic(filename);
    return 0;
}
