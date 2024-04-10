#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>

#include "DataStruct.h"

int main()
{
  using namespace jean;
  std::vector<DataStruct> data;
  std::istream_iterator<DataStruct> start(std::cin), end;

  std::copy(start, end, std::back_inserter(data)); 

  if (std::cin.bad()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  std::sort(data.begin(), data.end());

  std::ostream_iterator<DataStruct> output(std::cout, "\n");
  std::copy(data.begin(), data.end(), output);

  return 0;
}
