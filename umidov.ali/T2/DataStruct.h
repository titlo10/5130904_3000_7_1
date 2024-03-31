#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <iostream>
#include <string>
#include <complex>
#include <utility>

struct DataStruct
{
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
};

bool compareDataStruct(const DataStruct& a, const DataStruct& b);

std::istream& operator>>(std::istream& is, DataStruct& ds);

std::ostream& operator<<(std::ostream& os, const DataStruct& ds);

#endif