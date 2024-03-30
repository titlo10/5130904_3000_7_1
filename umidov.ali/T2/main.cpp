#include "DataStruct.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <vector>

std::istream& operator>>(std::istream& is, DataStruct& data) {
    std::string line, key, value;
    char colon;

    if (std::getline(is, line, ')')) {
        std::istringstream iss(line.substr(1));

        while (iss >> colon >> key >> value) {
            if (colon != ':') {
                is.setstate(std::ios::failbit);
                break;
            }
            value.pop_back();
            if (key == "key1") {
                data.key1 = std::stoull(value);
            }
            else if (key == "key2") {
                data.key2 = std::stoull(value, nullptr, 8);
            }
            else if (key == "key3") {
                data.key3 = value.substr(1, value.size() - 2);
            }
        }
    }
    else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
    os << "(:key1 " << data.key1 << "ull :key2 " << std::oct << data.key2
        << " :key3 \"" << data.key3 << "\":)";
    return os;
}

bool compareDataStructs(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.size() < b.key3.size();
}

int main() {
    std::vector<DataStruct> dataVector;
    std::cout << "Start reading data...\n";

    std::copy(std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(dataVector));

    std::cout << "Data reading completed.\n";

    std::sort(dataVector.begin(), dataVector.end(), compareDataStructs);
    std::cout << "Sorting completed.\n";

    std::copy(dataVector.begin(), dataVector.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n"));
    std::cout << "Data output completed.\n";

    return 0;
}