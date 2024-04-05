#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
#include <string>

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

    struct DoubleIO
    {
        double& ref;
    };

    struct CharIO
    {
        char& ref;
    };

    struct StringIO
    {
        std::string& ref;
    };

    struct UllLitIO
    {
        unsigned long long& ref;
    };

    struct UllOctIO
    {
        unsigned long long& ref;
    };

    class StreamGuard
    {
    public:
        StreamGuard(std::basic_ios<char>& s);
        ~StreamGuard();
    private:
        std::basic_ios<char>& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags fmt_;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, DoubleIO&& dest);
    std::istream& operator>>(std::istream& in, CharIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, UllLitIO&& dest);
    std::istream& operator>>(std::istream& in, UllOctIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
    std::string doubleToScientific(double x);
}

#endif
