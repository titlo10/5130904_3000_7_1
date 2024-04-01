#include "DataStruct.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
std::istream& operator>>(std::istream& is, DataStruct& ds) {
    std::string input, key, value;
    char ch;
    if (!std::getline(is, input, ')')) return is;
    std::istringstream iss(input.substr(1));

    while (iss >> key >> value) {
        if (key == "key1") {
            ds.key1 = std::stoull(value.substr(0, value.find("ull")));
        }
        else if (key == "key2") {
            ds.key2 = std::stoull(value, nullptr, 8);
        }
        else if (key == "key3") {
            ds.key3 = value.substr(1, value.size() - 2);
        }
        while (iss >> std::noskipws >> ch && ch != ':');
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
