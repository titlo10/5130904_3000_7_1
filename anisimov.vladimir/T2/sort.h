#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

struct DataStruct {
  unsigned long long key1;
  unsigned long long key2;
  std::string key3;
};

std::istream& operator>>(std::istream& is, DataStruct& data);
std::ostream& operator<<(std::ostream& os, const DataStruct& data);

#endif
