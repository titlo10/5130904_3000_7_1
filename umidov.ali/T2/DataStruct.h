#include <iostream>
#include <string>

struct DataStruct {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
    bool compareDataStructs(const DataStruct& a, const DataStruct& b);
    friend std::istream& operator>>(std::istream& is, DataStruct& ds);
    friend std::ostream& operator<<(std::ostream& os, const DataStruct& ds);
};