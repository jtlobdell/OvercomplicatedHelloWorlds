#include <iostream>
#include <array>
#include <numeric>
#include <list>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <exception>
#include <queue>
#include <functional>

namespace {

enum Command {
    GenerateCharacters,
    FillIndices,
    MakePrintables,
    OutputCharacter
};

// Returns true if successful, false otherwise
bool outputSingleCharacter(char c) {
    try {
        std::ostream outputStream(std::cout.rdbuf());
        outputStream.put(c);
        return true;
    }
    catch (const std::exception&) {
        return false;
    }
} // bool outputSingleCharacter(char)

class PrintableCharacter {
private:
    char c;
    
public:
    PrintableCharacter(char character) : c(character) {}
    void operator()() {
        if (!outputSingleCharacter(this->c)) {
            throw std::runtime_error("Failed to print a char.");
        }
    }
}; // class PrintableCharacter

std::array<char, 0x0e> helloCharacters;
std::list<std::size_t> helloIndices(helloCharacters.size());
std::vector<PrintableCharacter> helloPrintables;

void generateCharacters() {
    helloCharacters = std::array<char, 0x0e> {0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x0a};
}

void fillIndices() {
    std::iota(helloIndices.begin(), helloIndices.end(), (std::size_t) 0);
}

void makePrintables() {
    std::for_each(helloIndices.begin(),
                  helloIndices.end(),
                  [](std::size_t &n) {
                      helloPrintables.push_back(PrintableCharacter(helloCharacters[n]));
                  });
}

bool outputCharacter() {
    static auto printableIterator = helloPrintables.begin();
    bool success;

    if (printableIterator == helloPrintables.end()) {
        return false; // no more to print
    }

    try {
        (*printableIterator)();
        success = true;
    }
    catch (std::runtime_error&) {
        success = false;
    }
    
    printableIterator++;
    return success;

} // void outputCharacter()
    
}; // anonymous namespace


int main(int argc, char* argv[]) {
    std::queue<Command> commandQueue;
    std::vector<bool> charactersPrinted(helloCharacters.size());
    std::size_t charactersPrintedIndex = 0;

    // Set up our command queue
    commandQueue.push(Command::GenerateCharacters);
    commandQueue.push(Command::FillIndices);
    commandQueue.push(Command::MakePrintables);
    std::for_each(charactersPrinted.begin(),
                  charactersPrinted.end(),
                  [&commandQueue](bool) {
                      commandQueue.push(Command::OutputCharacter);
                  });

    // Run all the commands in the command queue
    while (!commandQueue.empty()) {
        switch (commandQueue.front()) {
            case Command::GenerateCharacters:
                generateCharacters();
                break;
            case Command::FillIndices:
                fillIndices();
                break;
            case Command::MakePrintables:
                makePrintables();
                break;
            case Command::OutputCharacter:
                charactersPrinted[charactersPrintedIndex++] = outputCharacter();                
                break;
            default:
                std::cerr << "Unknown command encountered in command queue." << std::endl;
                break;
        }

        commandQueue.pop();
    }

    // Make sure everything printed okay
    std::size_t failedPrintCount = std::count(charactersPrinted.begin(), charactersPrinted.end(), false);
    if (failedPrintCount > 0) {
        std::cerr << failedPrintCount << " characters failed to print." << std::endl;
    }
    
    return 0;
}
