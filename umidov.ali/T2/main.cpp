#include "DataStruct.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<DataStruct> dataVector;
    std::cout << "Start reading data...\n";

    DataStruct temp;
    while (std::cin >> temp) {
        dataVector.push_back(temp);
        std::cout << "Read record: " << temp << std::endl; // Проверка успешного чтения
    }

    if (dataVector.empty()) {
        std::cout << "No data read. Exiting." << std::endl;
        return 0;
    }

    std::cout << "Data reading completed.\n" << dataVector.size() << " records read. Sorting...\n";

    std::sort(dataVector.begin(), dataVector.end(), compareDataStructs);

    std::cout << "Sorted data:\n";
    for (const auto& data : dataVector) {
        std::cout << data << "\n";
    }

    return 0;
}
