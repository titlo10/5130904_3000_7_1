#include "namespace.h"

namespace anisimov
{
  std::string binaryNull(unsigned long long ref)
  {
    std::stringstream ss;
    ss << "0b" << std::setfill('0') << std::setw(2) << std::to_string(ref);
    std::string out = ss.str();
    size_t i = out.find('b');
    if (out[i + 1] == '0' and out[i + 2] == '0')
    {
      out.erase(i + 2, 1);
    }
    return out;
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    double realPart, imagPart;
    {
      using sep = DelimiterIO;
      using ull = ULongLiteralIO;
      using ulbl = ULongBinaryLiteralIO;
      using str = StringIO;
      in >> sep{ '(' } >> realPart >> sep{ ',' } >> imagPart >> sep{ ')' };
      dest.key2 = std::complex<double>(realPart, imagPart);
    }
    if (in)
    {
      dest.key1 = static_cast<unsigned long long>(std::abs(dest.key2.real()));
      dest.key3 = std::to_string(dest.key1);
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(";
    out << ":key1 " << src.key1 << "ull";
    out << ":key2 " << binaryNull(static_cast<unsigned long long>(std::abs(src.key2.real())));
    out << ":key3 " << "\"" << src.key3 << "\"";
    out << ":)";
    return out;
  }

  bool compareDataStruct(const DataStruct& a, const DataStruct& b)
  {
    if (a.key1 != b.key1)
    {
      return a.key1 < b.key1;
    }
    else if (std::abs(a.key2.real()) != std::abs(b.key2.real()))
    {
      return std::abs(a.key2.real()) < std::abs(b.key2.real());
    }
    else
    {
      return a.key3.length() < b.key3.length();
    }
  }

  iofmtguard::iofmtguard(std::basic_ios<char>& s) :
    s_(s),
    precision_(s.precision()),
    fill_(s.fill()),
    fmt_(s.flags())
  {}

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}
