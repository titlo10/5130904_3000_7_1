#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

struct DataStruct {
    std::string key1;
    std::string key2;
    std::string key3;
};

inline std::istream& operator>>(std::istream& is, DataStruct& data) {
    std::string line;
    if (!std::getline(is, line, ')')) {
        return is;
    }
    std::istringstream iss(line.substr(1)); // Удаляем '('
    std::getline(iss, data.key1, ':');
    std::getline(iss, data.key2, ':');
    std::getline(iss, data.key3, ':');
    // Убираем кавычки из key3, если они есть
    if (!data.key3.empty() && data.key3.front() == '\"') {
        data.key3 = data.key3.substr(1, data.key3.size() - 2);
    }
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
    os << "(:key1 " << data.key1 << " :key2 " << data.key2 << " :key3 \"" << data.key3 << "\":)";
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
