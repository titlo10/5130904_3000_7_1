#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <string>
#include <utility>

namespace jean {
    struct DataStruct {
        char key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;
    };

    bool comparator(const DataStruct& left, const DataStruct& right);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& src);
}

#endif // NAMESPACE_H

