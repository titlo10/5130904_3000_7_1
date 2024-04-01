#include "sort.h"
#include <sstream>

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
      std::string key2_str;
      is >> key2_str;
      std::stringstream ss(key2_str);
      ss >> std::hex >> data.key2;
    }
    else if (field == "key3") {
      is >> data.key3;
      is.get();
      is.get();
    }
  }
  return is;
}
