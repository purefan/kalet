#include <string>
#include <vector>
class Permuter {
public:
    std::wstring currentWord;
    std::string sourceFile;
    std::string targetFile;

    // This constructor sets the path to the file with common words
    Permuter();

    // Runs a few checks before doing the magic
    bool allGood();
    void setSourceFile(std::string);
    void setTargetFile(std::string);
    std::vector<std::wstring> getPermutations(std::wstring);
    std::vector<std::wstring> mixCases(std::wstring);
    void run();

private:
    std::vector<std::wstring> sourceWords;
    std::vector<std::wstring> mixOfLowerCases(std::wstring);

    // Checker functions
    bool canWriteToFile(std::string);
    bool fileExists(std::string);
    bool hasLowerCase(std::wstring);

    // Utility functions
    void uniqueVector(std::vector<std::wstring>&);
    std::vector<std::wstring> mergeVectors(std::vector<std::wstring>, std::vector<std::wstring>);
    std::wstring to_upper(std::wstring);
    void printVector(std::vector<std::wstring>);

    int countLinesInFile(std::string);
    void setWord(std::wstring);
    std::vector<std::wstring> fileToVector(std::string);
    void savePermutationsToFile(std::vector<std::wstring>);

};