#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

struct DataStruct {
    int key1;
    int key2;
    std::string key3;
};

inline std::istream& operator>>(std::istream& is, DataStruct& data) {
    std::string line;
    if (std::getline(is, line, ')')) {
        // Удаление двоеточий из строки
        line.erase(std::remove(line.begin(), line.end(), ':'), line.end());
        std::istringstream iss(line.substr(1));
        if (!(iss >> data.key1 >> data.key2 >> std::ws
            && std::getline(iss, data.key3, '\"')
            && std::getline(iss, data.key3, '\"'))) {
            is.setstate(std::ios::failbit);
        }
    }
    return is;
}


inline std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
    os << "(:key1 " << data.key1 << " :key2 " << data.key2
        << " :key3 \"" << data.key3 << "\":)";
    return os;
}

inline bool compareDataStructs(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }
    return a.key3 < b.key3;
}
