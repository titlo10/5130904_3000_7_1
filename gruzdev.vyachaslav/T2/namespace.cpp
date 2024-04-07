#include "namespace.h"

using gruzdev::DataStruct;

namespace gruzdev
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
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

    std::istream& operator>>(std::istream& in, ULLIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> dest.ref;
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
            using ULL = ULLIO;
            using str = StringIO;

            in >> sep{ '(' };
            bool flag1 = false, flag2 = false;
            while (true) {
                if (flag1 && flag2) break;
                std::string key;
                char c;
                in >> c;
                if (!in) break;

                if (c == ':' && (in >> key))
                {
                    if (key == "key1")
                    {
                        in >> ULL{ input.key1 };
                        flag1 = true;
                    }
                    else if (key == "key2")
                    {
                        in >> ULL{ input.key2 };
                        flag2 = true;
                    }
                    else if (key == "key3")
                    {
                        in >> str{ input.key3 };
                    }
                }
            }
            in >> sep{ ':' } >> sep{ ')' };
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
        out << "(";
        out << ":key1 " << std::uppercase << std::hex << "0x" << src.key1;
        out << ":key2 " << std::oct << src.key2;
        out << ":key3 \"" << src.key3 << "\"";
        out << ":)";
        return out;
    }

    bool compareDataStruct(const DataStruct& ds_first, const DataStruct& ds_second)
    {
        if (ds_first.key1 < ds_second.key1)
        {
            return true;
        }
        else if (ds_first.key1 == ds_second.key1)
        {
            return ds_first.key3.length() < ds_second.key3.length();
        }
        return false;
    }

    iofmtguard::iofmtguard(std::basic_ios<char>& s) :
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
