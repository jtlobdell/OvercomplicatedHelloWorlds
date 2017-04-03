#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::string hello_str = "Hello, world!";

    for (auto it: hello_str) {
        std::cout << it;
    }

    std::cout << std::endl;
    
    return 0;
}
