#include "namespace.h"
#include <vector>
#include <algorithm>

int main()
{
  using anisimov::DataStruct;

  std::vector<DataStruct> data;

  std::string line;
  while (std::getline(std::cin, line))
  {
    std::istringstream iss(line);
    DataStruct tmp;
    if (iss >> tmp)
    {
      data.push_back(tmp);
    }
  }

  std::sort(data.begin(), data.end(), anisimov::compareDataStruct);

  for (const auto& elem : data)
  {
    std::cout << elem << std::endl;
  }

  return 0;
}
