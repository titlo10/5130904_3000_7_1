// Пример перегрузки ввода/вывода для пользовательского типа Data.
// Похожим образом можно организовать ввод/вывод в работе 1,
// но в этом примере имеется ряд упрощений:
// 1) не поддерживается произвольный порядок полей
// 2) не поддерживаются строки некорректного формата

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <complex>
#include <algorithm>
#include <cmath>

namespace golikov
{
  struct DataStruct
  {
    unsigned long long key1;
    std::complex< double > key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };

  //struct for definition of complex type
  struct CMPDoubleIO
  {
    std::complex< double >& ref;
  };

  //struct for definition of ULL type
  struct ULLIO
  {
    unsigned long long& ref;
  };

  struct DoubleIO
  {
    double& num;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct LabelIO
  {
    std::string exp;
  };

  // scope guard для возврата состояния потока в первоначальное состояние
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, CMPDoubleIO&& dest);
  std::istream& operator>>(std::istream& in, ULLIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}

int main()
{
  using golikov::DataStruct;

  std::vector< DataStruct > data;
  std::istringstream iss("(:key1 0xFFFF:key2 #c(1.0 5.0):key3 \"Data\":)");
  std::istringstream iss2("(:key1 0xFFFF:key2 #c(1.0 1.0):key3 \"Data\":)");

  std::copy(
    std::istream_iterator< DataStruct >(iss),
    std::istream_iterator< DataStruct >(),
    std::back_inserter(data)
  );

  std::copy(
    std::istream_iterator< DataStruct >(iss2),
    std::istream_iterator< DataStruct >(),
    std::back_inserter(data)
  );
  
  std::sort(
    std::begin(data),
    std::end(data),
    [](const DataStruct& ds_first, const DataStruct& ds_second)
    {
      double Re_first = ds_first.key2.real(),
      Re_second = ds_second.key2.real(),
      Im_first = ds_first.key2.imag(),
      Im_second = ds_second.key2.imag(),
      R_first = 0.0,
      R_second = 0.0;

      R_first = sqrt(pow(Re_first, 2) + pow(Im_first, 2));
      R_second = sqrt(pow(Re_second, 2) + pow(Im_second, 2));

      if (ds_first.key1 < ds_second.key1)
      {
        return true;
      }
      else if (ds_first.key1 == ds_second.key1)
      {
        if (R_first < R_second)
        {
          return true;
        }
        else if (R_first == R_second)
        {
          return ds_first.key3 < ds_second.key3;
        }
      }
      return false;
    }
  );





  std::cout << "Data:\n";
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );

  

  return 0;
}

namespace golikov
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    // все перегрузки операторов ввода/вывода должны начинаться с проверки экземпляра класса sentry
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, CMPDoubleIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    double real = 0.0;
    double imag = 0.0;

    in >> DelimiterIO{ '(' } >> real >> imag >> DelimiterIO{ ')' };
    if (in)
    {
      dest.ref = std::complex<double>(real, imag);
    }
    return in;
  }


  std::istream& operator>>(std::istream& in, DoubleIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.num;
  }

  std::istream& operator>>(std::istream& in, ULLIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> std::hex >> dest.ref;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> data) && (data != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimiterIO;
      using label = LabelIO;
      using ULL = ULLIO;
      using dbl = DoubleIO;
      using cmp = CMPDoubleIO;
      using str = StringIO;
      in >> sep{ '(' };
      in >> sep{ ':' };
      in >> label{ "key1" } >> ULL{ input.key1 };
      in >> sep{ ':' };
      in >> label{ "key2" } >> sep{ '#' } >> sep{ 'c' } >> cmp{ input.key2 };
      in >> sep{ ':' };
      in >> label{ "key3" } >> str{ input.key3 };
      in >> sep{ ':' };
      in >> sep{ ')' };
    }
    if (in)
    {
      dest = input;
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
    out << ":key1 " << std::uppercase << std::hex << "0x" << src.key1;
    out << ":key2 " << std::fixed << std::setprecision(1) << "(" << src.key2.real() << " " << src.key2.imag() << ")";
    out << ":key3 " << src.key3;
    out << ":)";
    return out;
  }

  iofmtguard::iofmtguard(std::basic_ios< char >& s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}