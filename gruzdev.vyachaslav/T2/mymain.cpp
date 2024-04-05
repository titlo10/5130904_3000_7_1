#include <iostream>
#include <vector>
#include <algorithm>
#include "iter.h"

int main() {
    try {
        std::string input = "";
        std::vector< brat::DataStruct > data;

        while (std::getline(std::cin, input)) {
            std::istringstream iss(input);
            brat::DataStruct temp;
            if (iss >> temp) {
                data.push_back(temp);
            }
        }

        std::sort(std::begin(data), std::end(data), brat::compareDataStruct);

        for (const auto& d : data) {
            std::cout << d << std::endl;
        }
    }
    catch (std::exception& er) {
        std::cerr << er.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
