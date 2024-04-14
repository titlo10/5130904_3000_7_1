#include <iostream>
#include <vector>
#include <algorithm>
#include "namespace.h"

int main()
{
  std::vector<anisimov::DataStruct> data;
  std::string line;
  while (std::getline(std::cin, line))
  {
    std::istringstream iss(line);
    anisimov::DataStruct tmp;
    if (iss >> tmp)
    {
      data.push_back(tmp);
    }
  }
  std::sort(data.begin(), data.end(), anisimov::compareDataStruct);
  for (const auto& elem : data)
  {
    std::cout << elem << std::endl;
