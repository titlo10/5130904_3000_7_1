#include "DataStruct.h"
#include <vector>
#include <algorithm>
#include <iostream>
int main() {
    std::vector<DataStruct> dataVector;
    DataStruct temp;
    while (std::cin >> temp) {
        dataVector.push_back(temp);
    }
    std::sort(dataVector.begin(), dataVector.end(), compareDataStructs);
    for (const auto& data : dataVector) {
        std::cout << data << "\n";
    }
    return 0;
}
