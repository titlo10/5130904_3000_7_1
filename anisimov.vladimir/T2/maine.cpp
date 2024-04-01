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
int main() {
  std::vector<DataStruct> dataVector = {
    {10ull, 'c', "Data"},
    {20ull, 'd', "More Data"},
    {5ull, 'e', "Even More Data"}
  };
  std::sort(dataVector.begin(), dataVector.end(), SortComparator());
  for (const auto& data : dataVector) {
    std::cout << "(:key1 " << data.key1
    << ":key2 #" << std::fixed << std::setprecision(1) << std::real(data.key2) << " "
    << std::fixed << std::setprecision(1) << std::imag(data.key2) << ":key3 \"" << data.key3 << "\":)" << std::endl;
  }
  return 0;
}
