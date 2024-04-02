#ifndef HEADER_H
#define HEADER_H
#include <string>
#include <iostream>
namespace umidov {
    struct DataStruct {
        double key1;
        char key2;
        std::string key3;
    };
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}
#endif
