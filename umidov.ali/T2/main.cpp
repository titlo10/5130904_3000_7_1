#include "DataStruct.h"
#include <algorithm>
#include <vector>
#include <iterator>

std::istream& operator>>(std::istream& is, DataStruct& data) {
    std::getline(is, data.key1, ':');
    std::getline(is, data.key2, ':');
    std::getline(is, data.key3);
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
    os << "(:key1 " << data.key1 << " :key2 " << data.key2 << " :key3 \"" << data.key3 << "\":)";
    return os;
}

bool compareDataStructs(const DataStruct& a, const DataStruct& b) {
    return a.key1 < b.key1;
}

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
