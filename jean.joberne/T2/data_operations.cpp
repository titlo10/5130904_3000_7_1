#include "namespace.h"

namespace jean {
    std::istream& operator>>(std::istream& in, DataStruct& dest) {
        char sep;
        if (!(in >> sep && sep == '(')) return in;
        
        if (!(in >> dest.key1)) return in;
        
        long long num;
        unsigned long long denom;
        if (!(in >> num >> sep && sep == ':' && in >> denom)) return in;
        dest.key2 = {num, denom};
        
        if (!(in >> std::quoted(dest.key3))) return in;
        
        if (!(in >> sep && sep == ')')) return in;
        
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
        out << '(';
        out << src.key1 << ' ';
        out << src.key2.first << ':' << src.key2.second << ' ';
        out << '"' << src.key3 << '"';
        out << ')';
        return out;
    }

    bool comparator(const DataStruct& left, const DataStruct& right) {
        if (left.key1 != right.key1) return left.key1 < right.key1;
        if (left.key2.first != right.key2.first) return left.key2.first < right.key2.first;
        if (left.key2.second != right.key2.second) return left.key2.second < right.key2.second;
        return left.key3 < right.key3;
    }
}
