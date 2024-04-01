#include "DataStruct.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <vector>
std::istream& operator>>(std::istream& is, DataStruct& ds) {
    std::string input, part;
    if (!std::getline(is, input, ')')) return is;
    std::replace(input.begin(), input.end(), ':', ' ');
    input = input.substr(2, input.size() - 3);
    std::istringstream iss(input);
    while (iss >> part) {
        if (part == "key1") {
            iss >> ds.key1;
            iss.ignore(3);
        }
        else if (part == "key2") {
            iss >> std::oct >> ds.key2 >> std::dec;
        }
        else if (part == "key3") {
            iss.ignore(1, '\"');
            std::getline(iss, ds.key3, '\"');
        }
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
