#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <iterator>

struct DataStruct {
    unsigned long long key1 = 0;
    unsigned long long key2 = 0;
    std::string key3;
};

std::istream& operator>>(std::istream& is, DataStruct& data) {
    std::string line;
    if (std::getline(is, line)) {
        std::istringstream iss(line);
        char colon;
        std::string key;

        while (iss >> key >> colon && colon == ':') {
            if (key == "key1") {
                if (!(iss >> data.key1)) return is;
            }
            else if (key == "key2") {
                if (!(iss >> data.key2)) return is;
            }
            else if (key == "key3") {
                if (!(iss >> std::quoted(data.key3))) return is;
            }
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
    os << "DataStruct { key1: " << data.key1
        << ", key2: " << data.key2
        << ", key3: " << std::quoted(data.key3) << " }";
    return os;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.size() < b.key3.size();
}

int main() {
    std::vector<DataStruct> dataVector;
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        DataStruct data;
        if (iss >> data) {
            dataVector.push_back(data);
        }
        else {
            std::cerr << "Ошибка чтения данных: " << line << std::endl;
        }
    }

    std::sort(dataVector.begin(), dataVector.end(), compareDataStruct);

    for (const auto& data : dataVector) {
        std::cout << data << std::endl;
    }

    return 0;
}
