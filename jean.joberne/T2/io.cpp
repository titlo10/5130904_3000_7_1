#include "io.h"

namespace jean
{
    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
            return in;

        char leftParen, colon, rightParen;
        std::string key;
        in >> leftParen;

        while (in >> colon >> key && colon == ':') {
            if (key == "key1")
                in >> CharIO{dest.key1};
            else if (key == "key2")
                in >> IntIO{dest.key2};
            else if (key == "key3")
                in >> StringIO{dest.key3};
        }
        in >> rightParen;
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src)
    {
        out << "(:key1 " << src.key1
            << ":key2 " << src.key2
            << ":key3 \"" << src.key3 << "\":)";
        return out;
    }

    bool compareDataStruct(const DataStruct& a, const DataStruct& b)
    {
        if (a.key1 != b.key1) return a.key1 < b.key1;
        if (a.key2 != b.key2) return a.key2 < b.key2;
        return a.key3.length() < b.key3.length();
    }
}
