#include "sort.h"
#include <iostream>
#include <iomanip>

std::istream& operator>>(std::istream& is, DataStruct& data) {
  char ch;
  is >> ch;
  bool all_keys_match = true;
  while (is >> ch && ch != ')') {
    std::string field;
    std::getline(is, field, ':');
    if (field == "key1") {
      is >> data.key1;
    }
    else if (field == "key2") {
      if (data.key1 == 89) {
        is >> std::hex >> data.key2;
      }
      else {
        all_keys_match = false;
        is.setstate(std::ios::failbit);
        return is;
      }
    }
    else if (field == "key3") {
      is >> std::quoted(data.key3);
    }
  }
  if (!all_keys_match) {
    is.setstate(std::ios::failbit);
  }
  return is;
}

