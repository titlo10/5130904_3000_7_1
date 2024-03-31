#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <sstream>

struct DataStruct {
    std::string key1;
    std::string key2;
    std::string key3;
};

inline std::istream& operator>>(std::istream& is, DataStruct& data)
{
    std::string line;
    if (std::getline(is, line, ':'))
    {
        std::istringstream iss(line);
        if (!(std::getline(iss, data.key1, ' ')
            && std::getline(iss, data.key2, ' ')
            && std::getline(iss, data.key3, ':')))
        {
            is.setstate(std::ios::failbit);
        }
    }
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const DataStruct& data)
{
    os << "(" << data.key1 << ":" << data.key2 << ":" << data.key3 << ")";
    return os;
}

inline bool compareDataStructs(const DataStruct& a, const DataStruct& b)
{
    if (a.key1 != b.key1)
    {
        return a.key1 < b.key1;
    }
    if (a.key2 != b.key2)
    {
        return a.key2 < b.key2;
    }
    return a.key3 < b.key3;
}

#endif