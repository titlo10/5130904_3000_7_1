#include "sort.h"
#include <iostream>
#include <iomanip>

std::istream& operator>>(std::istream& is, DataStruct& data) {
  char ch;
  is >> ch;
  while (is >> ch && ch != ')') {
    std::string field;
    std::getline(is, field, ':');
    if (field == "key1") {
      is >> data.key1;
    }
    else if (field == "key2") {
      is >> std::hex >> data.key2;
    }
    else if (field == "key3") {
      is >> std::quoted(data.key3);
    }
  }
  return is;
}
std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
  os << "(:key1 " << data.key1 << ":key2 " << std::hex << data.key2 << ":key3 \"" << data.key3 << "\":)";
  return os;
}