#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <iomanip>

struct DataStruct {
  unsigned long long key1;
  std::complex<double> key2;
  std::string key3;
};
struct SortComparator {
  bool operator()(const DataStruct& lhs, const DataStruct& rhs) const {
    if (lhs.key1 != rhs.key1)
      return lhs.key1 < rhs.key1;
    if (lhs.key2 != rhs.key2)
      return std::abs(lhs.key2) < std::abs(rhs.key2);
      return lhs.key3.length() < rhs.key3.length();
  }
};