#include "DataStruct.h"

std::istream& jean::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry inputGuard(in);
  if (!inputGuard)
  {
    return in;
  }

  char delimiter, quote, colon;
  long long numerator;
  unsigned long long denominator;

  in >> delimiter;
  if (delimiter != '(') {
    in.setstate(std::ios::failbit);
    return in;
  }

  in >> value.characterKey >> colon;
  in >> quote;
  if (quote != '\'') {
    in.setstate(std::ios::failbit);
    return in;
  }
  in >> numerator >> colon >> denominator;
  if (colon != ':') {
    in.setstate(std::ios::failbit);
    return in;
  }
  value.rationalNumberKey = std::make_pair(numerator, denominator);
  in >> quote;
  in >> colon >> quote;
  if (quote != '\"') {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::getline(in, value.stringKey, '\"');
  in >> delimiter;
  if (delimiter != ')') {
    in.setstate(std::ios::failbit);
  }
  return in;
}

