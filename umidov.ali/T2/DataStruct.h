#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <iostream>
#include <string>
namespace umidov {
    struct DataStruct
    {
        unsigned long long key1;
        unsigned long long key2;
        std::string key3;
    };
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& src);
}
#endif
