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
    data = DataStruct();
    char c;
    is >> c;

    while (is >> c && c != ':') {}

    std::string keyName, keyValue;
    while (is >> keyName) {
        if (keyName.back() != ':') {
            is.setstate(std::ios_base::failbit);
            return is;
        }
        keyName.pop_back();
        if (keyName == "key1") {
            if (!(is >> data.key1)) {
                is.setstate(std::ios_base::failbit);
                return is;
            }
        }
        else if (keyName == "key2") {
            if (!(is >> data.key2)) {
                is.setstate(std::ios_base::failbit);
                return is;
            }
        }
        else if (keyName == "key3") {
            if (!(is >> std::quoted(data.key3))) {
                is.setstate(std::ios_base::failbit);
                return is;
            }
        }
        else {
            std::getline(is, keyValue, ':');
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
    os << "(:key1 " << data.key1 << " :key2 " << data.key2 << " :key3 " << std::quoted(data.key3) << ")";
    return os;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    else if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }
    else {
        return a.key3.size() < b.key3.size();
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
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
            iss.clear();
        }
    }

    std::sort(dataVector.begin(), dataVector.end(), compareDataStruct);

    std::copy(dataVector.begin(), dataVector.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
