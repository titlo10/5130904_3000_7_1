#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <complex>

namespace anisimov
{
  class DelimiterIO
  {
  public:
    DelimiterIO(char exp) : exp(exp) {}
    char exp;
  };

  class ULongLiteralIO
  {
  public:
    ULongLiteralIO(unsigned long long& ref) : ref(ref) {}
    unsigned long long& ref;
  };

  class ULongBinaryLiteralIO
  {
  public:
    ULongBinaryLiteralIO(unsigned long long& ref) : ref(ref) {}
    unsigned long long& ref;
  };

  class StringIO
  {
  public:
    StringIO(std::string& ref) : ref(ref) {}
    std::string& ref;
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
    iofmtguard(std::basic_ios<char>& s);
    ~iofmtguard();

  private:
    std::basic_ios<char>& s_;
    std::streamsize precision_;
    char fill_;
    std::ios_base::fmtflags fmt_;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, ULongLiteralIO&& dest);
  std::istream& operator>>(std::istream& in, ULongBinaryLiteralIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);
  bool compareDataStruct(const DataStruct& a, const DataStruct& b);
}
