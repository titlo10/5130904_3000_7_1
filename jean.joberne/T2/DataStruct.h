#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <string>
#include <iostream>

#include "Delimiter.h"

namespace jean {
  struct DataStruct {
    bool operator<(const DataStruct& other) const;
    char characterKey;
    std::pair<long long, unsigned long long> rationalNumberKey;
    std::string stringKey;
  };

  std::istream& operator>>(std::istream& in, DataStruct& value);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
}
#endif // !DATA_STRUCT_H
