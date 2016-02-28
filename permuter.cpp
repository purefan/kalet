#include "permuter.h"
#include "options.h"
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
#include <clocale>
#include <cstdlib>
#include <stdlib.h>
#include <string>

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
        std::wifstream stream(sourceFile);
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
    std::vector<std::wstring> lower_cases;

    std::wstring upper = this->to_upper(original);
    std::wstring temp_string;
    int original_size = original.size();

    for(std::wstring::size_type current_char = 0; current_char <= original_size; ++current_char) {
        temp_string = upper;
        for(std::wstring::size_type iteration = 0; iteration <= (original_size); ++iteration) {
            // This routine creates duplicated entries, it can certainly be improved
            temp_string[current_char] = towlower(temp_string[current_char]);
            lower_cases.push_back(temp_string);
            temp_string[current_char + iteration] = towlower(temp_string[current_char + iteration]);
            lower_cases.push_back(temp_string);
        }
    }

    this->uniqueVector(lower_cases);

    return lower_cases;
}

void Permuter::printVector(std::vector<std::wstring> original) {
    for (std::vector<std::wstring>::iterator i = original.begin(); i != original.end(); i++) {
        std::wcout << *i << ENDL;
    }
}

std::wstring Permuter::to_upper(std::wstring original) {
    for (std::wstring::iterator it = original.begin(); it != original.end(); it++) {
        *it = towupper(*it);
    }
    return original;
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

std::vector<std::wstring> Permuter::addNumbers(std::vector<std::wstring> original) {
    std::wstring current_word;
    std::wstring temp;
    std::vector<std::wstring> passwords;
    std::string the_number;
    int original_size;
    // Loop through every word
    for (std::vector<std::wstring>::iterator vec_iterator = original.begin(); vec_iterator != original.end(); vec_iterator++) {
        current_word = *vec_iterator;
        original_size = current_word.size();
        for (std::wstring::size_type current_char = 0; current_char <= original_size; ++current_char) {
            for (int i = 0; i < 10000; ++i) {
                temp = current_word.substr(0, current_char);
                temp += std::to_wstring(i); // + "#" +
                temp += current_word.substr(current_char, (original_size - current_char));
                passwords.push_back(temp);
            }
        }
    }
    return passwords;
}

std::vector<std::wstring> Permuter::generatePasswords(std::wstring original) {
    std::vector<std::wstring> passwords;
    std::vector<std::wstring> mixedCases    = this->mixCases(original);
    std::vector<std::wstring> numeric       = this->addNumbers(mixedCases);


    passwords = this->mergeVectors(mixedCases, numeric);

    // Remove duplicates
    this->uniqueVector(passwords);

    return passwords;
}

void Permuter::savePasswordsToFile(std::vector<std::wstring> words) {
    // std::cout << "savePermutationsToFile() -> "
    std::wofstream store;
    store.open(this->targetFile);

    for (std::vector<std::wstring>::iterator ite = words.begin(); ite != words.end(); ite++) {
        std::wcout << std::wstring(L"savePasswordsToFile(vector<string>) -> Storing: ") << *ite << ENDL;
        store << *ite << ENDL;
    }
    store.close();
}

void Permuter::run() {
    if (true || this->fileExists(this->sourceFile) == true) {
        std::vector<std::wstring> permutations;
        std::cout << this->sourceFile << " <--> " << this->targetFile << ENDL;
        this->sourceWords = this->fileToVector(this->sourceFile);

        std::cout << "Total words to permute: " << this->sourceWords.size() << ENDL;
        for (std::vector<std::wstring>::iterator ite = this->sourceWords.begin(); ite != this->sourceWords.end(); ite++ ) {
             std::wcout << std::wstring(L"run() -> ") << *ite << ENDL;
             permutations = this->generatePasswords(*ite);
             this->savePasswordsToFile(permutations);
        }

        // std::cout << "permutations[0]: " << permutations[0] << ENDL;
    } else {
        std::cout << "Not everything is ok" << ENDL;
    }

}

void Permuter::set_options(Options main_options) {

}