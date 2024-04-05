#include <iomanip>
#include <iostream>
#include <string>
#include <limits>
#include "DataStruct.h"

using namespace std;

istream& operator>>(istream& in, DelimiterIO&& elem)
{
    istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    string del;
    size_t tSize = elem.delimiter.length();
    in >> setw(tSize) >> del;
    if (!in)
    {
        return in;
    }
    if (elem.delimiter != del)
    {
        in.setstate(ios_base::failbit);
    }
    return in;
}

istream& operator>>(istream& in, UllIO&& elem)
{
    istream::sentry sentry(in);
    ResPars rGard(in);
    if (!sentry)
    {
        return in;
    }
    if (!(in >> oct >> elem.ref))
    {
        return in;
    }
    return in;
}

istream& operator>>(istream& in, ComplexIO&& elem)
{
    istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    string del;
    double real, imag;
    if (!(in >> DelimiterIO{"#c("}))
    {
        return in;
    }
    if (!(in >> real >> imag))
    {
        return in;
    }
    if (!(in >> DelimiterIO{")"}))
    {
        return in;
    }
    elem.ref = complex<double>(real, imag);
    return in;
}

istream& operator>>(istream& in, StringIO&& elem)
{
    istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return getline(in >> DelimiterIO{"\""}, elem.ref, '"');
}

istream& operator>>(istream& in, DataStruct& elem)
{
    istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    in >> DelimiterIO{"(:"};
    if (!in)
    {
        return in;
    }

    for (int i = 0; i < 3; i++)
    {
        string key;
        if (!(in >> key))
        {
            return in;
        }

        if (key == "key1")
        {
            if (!(in >> UllIO{ elem.key1 }))
            {
                return in;
            }
        }
        else if (key == "key2")
        {
            if (!(in >> ComplexIO{ elem.key2 }))
            {
                return in;
            }
        }
        else if (key == "key3")
        {
            if (!(in >> StringIO{ elem.key3 }))
            {
                return in;
            }
        }
        else
        {
            in.setstate(ios_base::failbit);
            return in;
        }
        in >> DelimiterIO{":"};
        if (!in)
        {
            return in;
        }
    }
    in >> DelimiterIO{")"};

    return in;
}

ostream& operator<<(ostream& op, const DataStruct& elem)
{
    ostream::sentry sentry(op);
    if (!sentry)
    {
        return op;
    }

    ResPars rGard(op);

    op << "(:key1 " << uppercase << oct << showbase << elem.key1
       << ":key2 " << "#c(" << fixed << setprecision(1) << elem.key2.real() << " "
       << fixed << setprecision(1) << elem.key2.imag() << ")"
       << ":key3 \"" << elem.key3 << "\":)";
    return op;
  }

ResPars::ResPars(basic_ios<char>& strm) :
    strm_(strm),
    fill_(strm.fill()),
    precision_(strm.precision()),
    fmtFlags_(strm.flags())
{}

ResPars::~ResPars()
{
    strm_.fill(fill_);
    strm_.precision(precision_);
    strm_.flags(fmtFlags_);
}


