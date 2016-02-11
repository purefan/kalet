#include "permuter.h"
#include <sys/stat.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <boost/algorithm/string.hpp>
#include <codecvt>
#include <locale>
#include <cstdlib>



#define ENDL "\n"

Permuter::Permuter() {}

bool Permuter::allGood() {
    return true ||
        (this->fileExists(this->sourceFile) &&
                this->canWriteToFile(this->targetFile));
}

/**
 * @brief Checks if a file exists
 * @details Does not check if the file is readable
 * @param sourceFile std::wstring
 * @return bool true if the file exists
 */
bool Permuter::fileExists(std::string sourceFile) {
    struct stat buffer;
    if (stat (sourceFile.c_str(), &buffer) == 0) {
        std::cout << "fileExists(" << sourceFile << ") -> true" << ENDL;
        return true;
    }
    return false;
}


bool Permuter::canWriteToFile(std::string targetFile) {
    FILE * pFile;
    const char* param = targetFile.c_str();
    pFile = fopen(param, "w");
    return pFile != NULL;
}

void Permuter::setWord(std::wstring word) {}

/**
 * @brief Counts lines in a file
 * @details [long description]
 *
 * @param pathToFile The path to the file to count lines from
 * @return int The number of lines in a file
 */
int Permuter::countLinesInFile(std::string pathToFile) {
    std::ifstream sFile(pathToFile);
    std::string line;
    int total = 0;
    for (; std::getline(sFile, line); ++total);
    return total;
}

void Permuter::setSourceFile(std::string sourceFile) { this->sourceFile = sourceFile; }
void Permuter::setTargetFile(std::string targetFile) { this->targetFile = targetFile; }

std::vector<std::wstring> Permuter::fileToVector(std::string sourceFile) {
    std::vector<std::wstring> originalWords;


    std::ifstream hFile(sourceFile);
    if (hFile.is_open()) {
        typedef std::codecvt_utf8<wchar_t> converter_type;
        const std::locale empty_locale = std::locale::empty();
        const converter_type* converter = new converter_type;
        const std::locale utf8_locale = std::locale(empty_locale, converter);
        std::wifstream stream(sourceFile);
        stream.imbue(utf8_locale);
        std::wstring line;





        std::wstring line;
        while (stream.good()) {
            std::getline(stream, line);
            // getline(hFile, line);
            originalWords.push_back(line);
        }
    }
    return originalWords;
}

bool Permuter::hasLowerCase(std::wstring toCheck) {
    return std::any_of(toCheck.begin(), toCheck.end(), ::islower);
}
/**
 * @details Takes the original word and returns a vector of all combinations with different cases
 *
 * @param original string of the original word to permute
 * @return [Chess, CHESS, chess, CHess, CHEss, CHESs, CHESS, cHess, cHEss, cHESs,...]
 */
std::vector<std::wstring> Permuter::mixCases(std::wstring original) {
    std::vector<std::wstring> mixedCases;
    // start with an upper case word
    std::wstring upper = boost::to_upper_copy<std::wstring>(original);

    mixedCases.push_back(upper);
    mixedCases.push_back(original);
    mixedCases.push_back(boost::to_lower_copy<std::wstring>(original));

    // std::vector<std::wstring>::iterator ite = mixedCases.begin();
    std::vector<std::wstring> lower_cases = this->mixOfLowerCases(original);
    // std::cout << "Added " << upper << " and " << original << ENDL;
    // std::cout << mixedCases[0] << ENDL;

    mixedCases = this->mergeVectors(mixedCases, lower_cases);
    // There shouldn't be any duplicates but lets make sure
    this->uniqueVector(mixedCases);
    return mixedCases;
}

/**
 * @brief Returns every combination of upper and lower case
 * @details [long description]
 *
 * @param original [description]
 * @return [Chess, CHess, cHess, cHEss,...]
 */
std::vector<std::wstring> Permuter::mixOfLowerCases(std::wstring original) {
    std::vector<std::wstring> lowerCases;
    std::cout << "mixOfLowerCases(" << original << ");";
    // int boundChecker = 0;
    //por cada posicion
    //    convierta esa posicion a mayuscula --> Chess, cHess, chEss

    std::wstring temp = original;
    // for (std::wstring::iterator ite = original.begin(); ite < original.end(); ite++) {
    for(std::wstring::size_type i = 0; i < original.size(); ++i) {
        // do_things_with(str[i]);
        // std::cout << boost::algorithm::to_lower(*ite) << ENDL;
        std::cout << "Testing original[" << i << "] = " << original[i] << ENDL;
    }

    /*while(this->hasLowerCase(original) && boundChecker < 10) {
        boundChecker++;
        //original = original.
    }*/
    return lowerCases;
}

/**
 * @brief Removes duplicate entries in an std::vector
 *
 * @param originalVector vector of string
 */
void Permuter::uniqueVector(std::vector<std::wstring> &originalVector) {
    sort( originalVector.begin(), originalVector.end() );
    originalVector.erase( unique( originalVector.begin(), originalVector.end() ), originalVector.end() );
}

/**
 * @brief Merges vectors
 *
 * @return A new array with the unique contents of arrays a and b
 */
std::vector<std::wstring> Permuter::mergeVectors(std::vector<std::wstring> a, std::vector<std::wstring> b) {
    std::vector<std::wstring> merged;
    merged.insert(merged.end(), a.begin(), a.end());
    merged.insert(merged.end(), b.begin(), b.end());
    this->uniqueVector(merged);
    return merged;
}


std::vector<std::wstring> Permuter::getPermutations(std::wstring original) {
    std::vector<std::wstring> permutations;
    std::vector<std::wstring> mixedCases = this->mixCases(original);

    // Merge vectors
    permutations.insert(permutations.end(), mixedCases.begin(), mixedCases.end());

    // Remove duplicates
    this->uniqueVector(permutations);

    return permutations;
}

void Permuter::savePermutationsToFile(std::vector<std::wstring> words) {
    // std::cout << "savePermutationsToFile() -> "
    std::ofstream store;
    store.open(this->targetFile);

    for (std::vector<std::wstring>::iterator ite = words.begin(); ite != words.end(); ite++) {
        std::cout << "savePermutationsToFile(vector<string>) -> Storing: " << *ite << ENDL;
        store << *ite << ENDL;
    }
    store.close();
}

void Permuter::run() {
    if (true || this->fileExists(this->sourceFile) == true) {
        std::vector<std::wstring> permutations;
        std::cout << this->sourceFile << " <--> " << this->targetFile << ENDL;
        // this->sourceWords = this->fileToVector(this->sourceFile);
        this->sourceWords.push_back("Tjäna");
        std::cout << "Total words to permute: " << this->sourceWords.size() << ENDL;
        for (std::vector<std::wstring>::iterator ite = this->sourceWords.begin(); ite != this->sourceWords.end(); ite++ ) {
             std::cout << "run() -> " << *ite << ENDL;
             permutations = this->getPermutations(*ite);
             this->savePermutationsToFile(permutations);
        }

        // std::cout << "permutations[0]: " << permutations[0] << ENDL;
    } else {
        std::cout << "Not everything is ok" << ENDL;
    }

}