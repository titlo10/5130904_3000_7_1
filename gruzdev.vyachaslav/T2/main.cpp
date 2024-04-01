#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cctype>
struct DataStruct {
    unsigned long long key1;
    char key2;
    std::string key3;
};
std::istream& operator>>(std::istream& in, DataStruct& data) {
    in >> data.key1;
    in >> data.key2;
    std::getline(in >> std::ws, data.key3);
    return in;
}
std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << data.key1 << " " << data.key2 << " " << data.key3;
    return out;
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
    setlocale(LC_ALL, "Ru");
    std::vector<DataStruct> dataVector;
    DataStruct data;
    std::cout << "Введите данные (формат: key1 key2 key3) или end для завершения ввода:" << std::endl;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "end") {
            break;
        }
        std::istringstream iss(line);
        if (iss >> data) {
            dataVector.push_back(data);
        }
    }
    std::cout << "Данные перед сортировкой:" << std::endl;
    for (const auto& data : dataVector) {
        std::cout << data << std::endl;
    }
    std::sort(dataVector.begin(), dataVector.end(), compareDataStruct);
    std::cout << "Отсортированные данные:" << std::endl;
    for (const auto& data : dataVector) {
        std::cout << data << std::endl;
    }
    return 0;
}
