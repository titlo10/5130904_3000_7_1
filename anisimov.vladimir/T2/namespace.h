#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <complex>

namespace anisimov
{
  struct DelimiterIO
  {
    char exp;
  };

  struct ULongLiteralIO
  {
    unsigned long long ref;
  };

  struct ULongBinaryLiteralIO
  {
    unsigned long long ref;
  };

  struct StringIO
  {
    std::string ref;
  };

  struct ComplexLiteralIO
  {
    std::complex<double> ref;
  };

  struct DataStruct
  {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
  };

  class iofmtguard
  {
  public:
    explicit iofmtguard(std::basic_ios<char>& s);
    ~iofmtguard();

  private:
    std::basic_ios<char>& s_;
    std::streamsize precision_;
    std::ios::fmtflags fmt_;
    char fill_;
  };

  std::string binaryNull(unsigned long long ref);

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, ULongLiteralIO&& dest);
  std::istream& operator>>(std::istream& in, ULongBinaryLiteralIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, ComplexLiteralIO&& dest);

  std::ostream& operator<<(std::ostream& out, const DataStruct& src);

  bool compareDataStruct(const DataStruct& a, const DataStruct& b);
}

#endif
