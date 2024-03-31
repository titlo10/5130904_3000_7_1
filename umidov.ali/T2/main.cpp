#include "DataStruct.h"
#include <vector>
#include <algorithm>
#include <iostream>

bool compareDataStructs(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> dataVector;
    DataStruct temp;

    std::cout << "Enter data, finish with EOF (Ctrl+D or Ctrl+Z):\n";

    while (std::cin >> temp) {
        dataVector.push_back(temp);
    }

    std::sort(dataVector.begin(), dataVector.end(), compareDataStructs);

    for (const auto& data : dataVector) {
        std::cout << data << "\n";
    }

    return 0;
}