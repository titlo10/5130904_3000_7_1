#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "io.h" 

using namespace gubanov;

int main()
{
  std::vector<DataStruct> data;
  std::string line = "";

  while (std::getline(std::cin, line))
  {
    std::istringstream iss(line);
    DataStruct tmp;
    if (iss >> tmp)
    {
      data.push_back(tmp);
    }
  }

  std::sort(std::begin(data), std::end(data),
    [](const DataStruct& d1, const DataStruct& d2)
    {
      if (d1.key1 == d2.key1)
      {
        if (d1.key2 == d2.key2)
          return d1.key3.length() < d2.key3.length();
        return d1.key2 < d2.key2;
      }
      return d1.key1 < d2.key1;
    }
  );

  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<DataStruct>(std::cout, "\n")
  );

  return EXIT_SUCCESS;
}
