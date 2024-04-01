#include "DataStruct.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
std::istream& operator>>(std::istream& is, DataStruct& ds) {
    std::string input, part;
    if (!std::getline(is, input)) return is;
    std::istringstream iss(input);
    ds = DataStruct();
    try {
        while (iss >> part) {
            if (part.find("key1") != std::string::npos) {
            }
            else if (part.find("key2") != std::string::npos) {
            }
            else if (part.find("key3") != std::string::npos) {
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to parse input: " << e.what() << '\n';
        is.setstate(std::ios::failbit);
    }
    return is;
}
std::ostream& operator<<(std::ostream& os, const DataStruct& ds) {
    os << "(:key1 " << ds.key1 << "ull:key2 0" << std::oct << ds.key2 << std::dec << ":key3 \"" << ds.key3 << "\":)";
    return os;
}
bool compareDataStructs(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3 < b.key3;
}
