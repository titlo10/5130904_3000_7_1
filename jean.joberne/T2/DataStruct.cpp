#include "DataStruct.h"

std::istream& jean::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry inputGuard(in);
  if (!inputGuard)
  {
    return in;
  }

  char delimiter;
  in >> delimiter;
  if (delimiter != '(') {
    in.setstate(std::ios::failbit);
    return in;
  }

  return in;
}

std::ostream& jean::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry outputGuard(out);
  if (!outputGuard)
  {
    return out;
  }

  out << "(:characterKey '" << value.characterKey;
  out << "':rationalNumberKey (:N " << value.rationalNumberKey.first;
  out << ":D " << value.rationalNumberKey.second << ":):stringKey ";
  out << '"' << value.stringKey << '"' << ":)";
  return out;
}
