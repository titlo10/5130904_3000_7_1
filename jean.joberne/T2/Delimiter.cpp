#include "Delimiter.h"

std::istream& jean::operator>>(std::istream& in, const Delimiter&& exp)
{
  std::istream::sentry inputGuard(in);
  if (!inputGuard)
  {
    return in;
  }
  
  char readChar;
  in >> readChar;
  if (readChar != exp.expected) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& jean::operator>>(std::istream& in, const StringDelimiter&& exp)
{
  std::istream::sentry inputGuard(in);
  if (!inputGuard)
  {
    return in;
  }

  char currentChar;
  for (size_t i = 0; exp.expected[i] != '\0'; i++) {
    in >> currentChar;
    if (currentChar != exp.expected[i]) {
      in.setstate(std::ios::failbit);
      break;
    }
  }
  return in;
}

