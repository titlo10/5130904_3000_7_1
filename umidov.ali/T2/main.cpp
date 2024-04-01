#include "DataStruct.h"
#include <vector>
#include <algorithm>
#include <iostream>
int main() {
    std::vector<DataStruct> dataVector;
    DataStruct temp;
    std::cout << "Enter data, finish with EOF (Ctrl+D or Ctrl+Z on UNIX, Ctrl+Z then Enter on Windows):\n";
    while (std::cin >> temp) {
        dataVector.push_back(temp);
    }
    std::sort(dataVector.begin(), dataVector.end(), compareDataStructs);
    for (const auto& data : dataVector) {
    }
    return 0;
}
