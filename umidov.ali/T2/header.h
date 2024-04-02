#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <vector>
#include <sstream>
namespace umidov
{
    struct DataStruct
    {
        double key1 = 0.0;
        char key2 = '\0';
        std::string key3;
    };
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}
#endif
