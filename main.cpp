#include <cstring>
#include <iostream>
#include "permuter.cpp"


#define ENDL "\n"

using namespace std;


void showIntro() {
    cout << "Dictionary Generator v1.0 - by Miguel Espinoza - http://purefan.me" << ENDL;
    cout << ENDL;
    cout << "| This program takes words from a file and permutes them into a  |" << ENDL;
    cout << "| dictionary that can be used in brute force attacks.            |" << ENDL;
    cout << "| Intended only for educational purposes, do not use it for evil |" << ENDL;
    cout << "| By using this software you agree to release the author(s) from |" << ENDL;
    cout << "| any liability and responsibility.                              |" << ENDL;
    cout << ENDL;
}


int main(int argc, char *argv[]) {
    // Read file with most common words
    showIntro();
    // SUPER important
    std::locale::global(std::locale("sv_SE"));

    std::string sourcePath;
    std::string targetPath;

    if (argc > 1) {
        sourcePath = argv[1];
    } else {
        cout << "1. Path to a file with common words to permute: ";
        getline(cin, sourcePath);
    }

    if (argc > 2) {
        targetPath = argv[2];
    } else {
        cout << "2. Path to the target file: ";
        getline(cin, targetPath);
    }

    Permuter myPermuter = Permuter();
    myPermuter.setSourceFile(sourcePath);
    myPermuter.setTargetFile(targetPath);

    if (myPermuter.allGood() == true) {
        myPermuter.run();
    }

    return 0;
}