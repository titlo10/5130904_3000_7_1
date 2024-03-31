#include "DataStruct.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<DataStruct> dataVector;
    std::cout << "Start reading data...\n";

    // Чтение данных в вектор
    DataStruct temp;
    while (std::cin >> temp) {
        dataVector.push_back(temp);
    }

    // Проверка наличия считанных данных
    if (dataVector.empty()) {
        std::cout << "No data read. Exiting.\n";
        return 0;
    }
    else {
        std::cout << "Data reading completed.\nSorting...\n";
    }

    // Сортировка данных
    std::sort(dataVector.begin(), dataVector.end(), compareDataStructs);

    // Вывод отсортированных данных
    std::cout << "Sorted data:\n";
    for (const auto& item : dataVector) {
        std::cout << item << "\n";
    }

    return 0;
}
