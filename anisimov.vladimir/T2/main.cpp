#include "sort.h"

int main() {
  std::vector<DataStruct> dataVector;
  std::string line;
  while (std::getline(std::cin, line)) {
    std::istringstream iss(line);
    DataStruct data;
    if (iss >> data) {
      dataVector.push_back(data);
    }
  }
  std::sort(dataVector.begin(), dataVector.end(), [](const DataStruct& lhs, const DataStruct& rhs) {
    if (lhs.key1 != rhs.key1)
      return lhs.key1 < rhs.key1;
    if (lhs.key2 != rhs.key2)
      return lhs.key2 < rhs.key2;
    return lhs.key3.length() < rhs.key3.length();
    });

  for (const auto& data : dataVector) {
    std::cout << data << std::endl;
  }
  return 0;
}
