#include "DataStruct.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <vector>
std::istream& operator>>(std::istream& is, DataStruct& ds) {
    std::string input;
    while (std::getline(is, input)) {
        std::replace(input.begin(), input.end(), ':', ' ');
        if (input.size() < 3 || input[0] != '(' || input[1] != ':') {
            continue;
        }
        input = input.substr(2, input.size() - 3);
        std::istringstream iss(input);
        std::string part;
        bool key1Found = false, key2Found = false, key3Found = false;
        while (iss >> part) {
            if (part == "key1" && !key1Found) {
                if (!(iss >> ds.key1)) break;
                iss.ignore(3);
                key1Found = true;
            }
            else if (part == "key2" && !key2Found) {
                if (!(iss >> std::oct >> ds.key2 >> std::dec)) break;
                key2Found = true;
            }
            else if (part == "key3" && !key3Found) {
                iss.ignore(1, '\"');
                if (!std::getline(iss, ds.key3, '\"')) break;
                key3Found = true;
            }
        }
        if (key1Found && key2Found && key3Found) {
            return is;
        }
    }
    is.setstate(std::ios::eofbit);
    return is;
}
std::ostream& operator<<(std::ostream& os, const DataStruct& ds)
{
    os << "(:key1 " << ds.key1 << " :key2 0" << std::oct << ds.key2 << std::dec << " :key3 \"" << ds.key3 << "\")";
    return os;
}
bool compareDataStructs(const DataStruct& a, const DataStruct& b)
{
    return false;
}
