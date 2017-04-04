#include <iostream>
#include <array>
#include <numeric>
#include <list>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <exception>

namespace {

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
}

}; // anonymous namespace

class PrintableCharacter {
private:
    char c;
    
public:
    PrintableCharacter(char character) : c(character) {}
    void operator()(){
        if (!outputSingleCharacter(this->c)) {
            throw std::runtime_error("Failed to print a char.");
        }
    }
};

int main(int argc, char* argv[]) {
    std::array<char, 0x0e> helloChars {0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x0a};
    std::list<std::size_t> helloIndices(helloChars.size());
    std::iota(helloIndices.begin(), helloIndices.end(), (std::size_t) 0);
    std::vector<PrintableCharacter> helloPrintables;
    
    std::for_each(helloIndices.begin(),
                  helloIndices.end(),
                  [&helloPrintables, &helloChars](std::size_t &n) {
                      helloPrintables.push_back(PrintableCharacter(helloChars[n]));
                  });

    try {
        std::for_each(helloPrintables.begin(),
                      helloPrintables.end(),
                      [](PrintableCharacter &pc) {
                          pc();
                      });
    }
    catch (std::runtime_error&) {
        return 1;
    }
        
    return 0;
}
