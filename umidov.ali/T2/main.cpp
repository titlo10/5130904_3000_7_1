#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <complex>

struct DataStruct {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
};

std::istream& operator>>(std::istream& is, DataStruct& data) {
    char c;
    is >> c;
    while (is >> c && c != ':') {}

    while (is >> c && c == ':') {
        std::string keyName;
        is >> keyName;

        if (keyName == "key1") {
            is >> data.key1;
        }
        else if (keyName == "key2") {
            is >> data.key2;
        }
        else if (keyName == "key3") {
            is >> std::quoted(data.key3);
        }
        else {
            std::string value;
            is >> value;
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
    os << "(:key1 " << data.key1 << "ull:key2 " << data.key2 << "ull:key3 " << std::quoted(data.key3) << ":)";
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
    std::vector<DataStruct> dataVector;

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        DataStruct data;
        if (iss >> data) {
            dataVector.push_back(data);
        }
    }

    std::sort(dataVector.begin(), dataVector.end(), compareDataStruct);

    std::copy(dataVector.begin(), dataVector.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
