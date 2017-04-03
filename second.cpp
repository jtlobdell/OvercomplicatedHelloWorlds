#include <iostream>
#include <array>
#include <string>

int main(int argc, char* argv[]) {
    std::array<char, 13> hello {'H', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd', '!'};
    std::ostream output(std::cout.rdbuf());

    for (auto it: hello) {
        output << it;
    }

    output << "\n";
    
    return 0;
}
