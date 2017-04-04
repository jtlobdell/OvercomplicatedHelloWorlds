#include <iostream>
#include <array>

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

int main(int argc, char* argv[]) {
    std::array<char, 0x0e> hello {0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x0a};

    for (auto it: hello) {
        if (!outputSingleCharacter(it)) {
            return 1;
        }
    }

    return 0;
}
