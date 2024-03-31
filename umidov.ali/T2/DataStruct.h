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
        std::istringstream iss(line.substr(1));
        std::string key1, key2;
        std::getline(iss, key1, ':');
        std::getline(iss, key2, ':');
        std::getline(iss, data.key3, ':');
        try {
            data.key1 = std::stoi(key1);
            data.key2 = std::stoi(key2);
        }
        catch (const std::exception&) {
            data.key1 = data.key2 = 0;
        }
        if (!data.key3.empty() && data.key3.front() == '\"') {
            data.key3 = data.key3.substr(1, data.key3.size() - 2);
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
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3 < b.key3;
}
