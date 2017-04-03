#include <iostream>
#include <array>

int main(int argc, char* argv[]) {
    std::array<char, 14> hello {0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x0a};
    std::ostream output(std::cout.rdbuf());

    for (auto it: hello) {
        output.write(&it, 1);
    }

    return 0;
}
