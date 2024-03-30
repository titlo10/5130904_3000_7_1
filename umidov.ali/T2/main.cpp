#include "DataStruct.h"
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>
#include <iterator>

std::istream& operator>>(std::istream& is, DataStruct& data) {
    std::string line;
    if (std::getline(is, line, ')')) {
        std::istringstream iss(line.substr(1));
        std::string key, value;
        char colon;

        while (iss >> colon >> key >> value) {
            if (colon != ':') {
                is.setstate(std::ios::failbit);
                return is;
            }
            if (key == "key1") {
                data.key1 = std::stoull(value.substr(0, value.size() - 3));
            }
            else if (key == "key2") {
                data.key2 = std::stoull(value.substr(0, value.size() - 3), 0, 8);
            }
            else if (key == "key3") {
                data.key3 = value.substr(1, value.size() - 2);
            }
            iss.ignore(std::numeric_limits<std::streamsize>::max(), ':');
        }
    }
    else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
    os << "(:key1 " << data.key1 << "ull:key2 " << std::oct << data.key2 << ":key3 \"" << data.key3 << "\":)";
    return os;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.size() < b.key3.size();
}

int main() {
    std::vector<DataStruct> dataVector;
    std::cout << "Start reading data..." << std::endl;

    std::copy(std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(dataVector));

    std::cout << "Data reading completed." << std::endl;

    std::sort(dataVector.begin(), dataVector.end(), compareDataStruct);
    std::cout << "Sorting completed." << std::endl;

    std::copy(dataVector.begin(), dataVector.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n"));
    std::cout << "Data output completed." << std::endl;

    return 0;
}
