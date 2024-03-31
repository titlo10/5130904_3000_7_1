#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <complex>

struct DataStruct {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;

    // Custom comparator for sorting
    friend bool operator<(const DataStruct& lhs, const DataStruct& rhs) {
        if (lhs.key1 != rhs.key1) return lhs.key1 < rhs.key1;
        if (lhs.key2 != rhs.key2) return lhs.key2 < rhs.key2;
        return lhs.key3.length() < rhs.key3.length();
    }

    friend std::istream& operator>>(std::istream& is, DataStruct& ds) {
        std::string input;
        if (std::getline(is, input, ')')) {
            std::replace(input.begin(), input.end(), ':', ' ');
            std::istringstream iss(input.substr(1));
            char key2_prefix;
            iss >> ds.key1 >> key2_prefix >> ds.key2 >> std::ws;
            std::getline(iss, ds.key3, '\"');
            std::getline(iss, ds.key3, '\"');
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const DataStruct& ds) {
        os << "(:key1 " << ds.key1 << " :key2 0b" << std::bitset<64>(ds.key2)
            << " :key3 \"" << ds.key3 << "\":)";
        return os;
    }
};

#endif