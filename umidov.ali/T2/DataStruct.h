#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <iostream>
#include <string>
#include <utility>
#include <complex>
namespace umidov{
    struct DataStruct {
        double key1 = 0.0;
        unsigned long long key2 = 0;
        std::string key3 = "";
    };

    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& src);
}
#endif
