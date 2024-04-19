#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <iomanip>
#include <algorithm>

namespace jean {
    struct DataStruct {
        char key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;
    };

    struct DelimiterIO {
        char exp;
    };

    struct LabelCharIO {
        char& ref;
    };

    struct LongLongIO {
        long long& ref;
    };

    struct UnsLongLongIO {
        unsigned long long& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    struct KeyStringIO {
        std::string& ref;
    };

    struct LabelIO {
        std::string exp;
    };

    class iofmtguard {
    public:
        iofmtguard(std::basic_ios<char>& s);
        ~iofmtguard();
    private:
        std::basic_ios<char>& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags fmt_;
    };

    bool comparator(const DataStruct& left, const DataStruct& right);

    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& src);
}

#endif // NAMESPACE_H
