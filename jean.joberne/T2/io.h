#ifndef IO_H
#define IO_H

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <string>

namespace jean
{
    struct DataStruct
    {
        char key1;
        int key2;
        std::string key3;

        friend std::istream& operator>>(std::istream& in, DataStruct& dest);
        friend std::ostream& operator<<(std::ostream& out, const DataStruct& src);
    };

    struct DelimiterIO
    {
        char exp;
    };

    struct StringIO
    {
        std::string& ref;
    };

    struct CharIO
    {
        char& ref;
    };

    struct IntIO
    {
        int& ref;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, CharIO&& dest);
    std::istream& operator>>(std::istream& in, IntIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& src);

    bool compareDataStruct(const DataStruct& a, const DataStruct& b);
}

#endif
