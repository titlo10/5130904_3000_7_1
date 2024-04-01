#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <string>
#include <iomanip>

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
