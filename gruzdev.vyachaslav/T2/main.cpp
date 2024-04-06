#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <complex>

using namespace std;

struct DataStruct
{
    unsigned long long key1 = 0;
    complex<double> key2;
    string key3;
};

struct UllIO
{
    unsigned long long& ref;
};

struct ComplexIO
{
    complex<double>& ref;
};

struct StringIO
{
    string& ref;
};

struct DelimiterIO
{
    string delimiter;
};

istream& operator>>(istream& in, DelimiterIO&& dest)
{
    istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    string del;
    size_t tSize = dest.delimiter.length();
    in >> setw(tSize) >> del;
    if (!in)
    {
        return in;
    }
    if (dest.delimiter != del)
    {
        in.setstate(ios_base::failbit);
    }
    return in;
}

istream& operator>>(istream& in, UllIO&& dest)
{
    istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    in >> dest.ref;
    return in;
}

istream& operator>>(istream& in, ComplexIO&& dest)
{
    istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    in >> dest.ref;
    return in;
}

istream& operator>>(istream& in, StringIO&& dest)
{
    istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return getline(in >> DelimiterIO{ "\"" }, dest.ref, '"');
}

istream& operator>>(istream& in, DataStruct& dest)
{
    istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    in >> DelimiterIO{ "(:key1" } >> UllIO{ dest.key1 }
        >> DelimiterIO{ ":key2" } >> DelimiterIO{ "#c(" } >> ComplexIO{ dest.key2 }
        >> DelimiterIO{ ")" } >> DelimiterIO{ ":key3" } >> StringIO{ dest.key3 }
    >> DelimiterIO{ ")" };

    return in;
}

ostream& operator<<(ostream& out, const DataStruct& dest)
{
    out << "(:key1 " << dest.key1 << " :key2 " << dest.key2 << " :key3 \"" << dest.key3 << "\")";
    return out;
}

int main()
{
    vector<DataStruct> ds_original;
    string request;
    while (getline(cin, request))
    {
        istringstream iss(request);
        DataStruct temp;
        if (iss >> temp)
        {
            ds_original.push_back(temp);
        }
    }

    sort(ds_original.begin(), ds_original.end(), [](const DataStruct& ds1, const DataStruct& ds2)
        {
            if (ds1.key1 != ds2.key1)
                return ds1.key1 < ds2.key1;

            if (abs(ds1.key2) != abs(ds2.key2))
            {
                return abs(ds1.key2) < abs(ds2.key2);
            }
            else
            {
                return ds1.key3.length() < ds2.key3.length();
            }
        });

    copy(ds_original.begin(), ds_original.end(), ostream_iterator<DataStruct>(cout, "\n"));

    return 0;
}
