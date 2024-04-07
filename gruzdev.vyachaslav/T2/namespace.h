#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <complex>
#include <algorithm>
#include <cmath>

namespace gruzdev
{
    struct DataStruct
    {
        unsigned long long key1;
        unsigned long long key2;
        std::string key3;
    };

    struct DelimiterIO
    {
        char exp;
    };

    struct ULLLitIO
    {
        unsigned long long& ref;
    };

    struct ULLOctIO
    {
        unsigned long long& ref;
    };

    struct StringIO
    {
        std::string& ref;
    };

    struct LabelIO
    {
        std::string exp;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, ULLLitIO&& dest);
    std::istream& operator>>(std::istream& in, ULLOctIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, LabelIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

    bool compareDataStruct(const DataStruct& ds_first, const DataStruct& ds_second);
}

#endif
