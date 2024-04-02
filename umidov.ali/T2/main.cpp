#include "header.h"
#include <iostream>
int main() {
    umidov::DataStruct data;
    if (std::cin >> data) {
        std::cout << data << std::endl;
    }
    else {
        std::cerr << "Error: Process completed with exit code 2.\n";
    }
    return 0;
}
