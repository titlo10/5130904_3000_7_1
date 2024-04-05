#include "iter.h"

namespace brat
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

    std::istream& operator>>(std::istream& in, ULLLiteralIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> dest.ref >> DelimiterIO{ 'u' } >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
    }

    std::istream& operator>>(std::istream& in, ULLOctIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> std::oct >> dest.ref >> std::dec >> DelimiterIO{ 'u' } >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
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
            using ulllit = ULLLiteralIO;
            using ulloct = ULLOctIO;
            using str = StringIO;

            in >> sep{ '(' };
            bool flag1 = false, flag2 = false, flag3 = false;
            while (true) {
                if (flag1 && flag2 && flag3) break;
                std::string key = "";
                char c = '0';
                in >> c;
                if (!in) break;

                if (c == ':' && (in >> key))
                {
                    if (key == "key1")
                    {
                        in >> ulllit{ input.key1 };
                        flag1 = true;
                    }
                    else if (key == "key2")
                    {
                        in >> ulloct{ input.key2 };
                        flag2 = true;
                    }
                    else if (key == "key3")
                    {
                        in >> str{ input.key3 };
                        flag3 = true;
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
        iofmtguard fmtguard(out);
        out << "(";
        out << ":key1 " << std::fixed << std::setprecision(1) << src.key1 << 'u' << 'l' << 'l';
        out << ":key2 " << std::oct << src.key2 << 'u' << 'l' << 'l' << std::dec;
        out << ":key3 " << "\"" << src.key3 << "\"";
        out << ":)";
        return out;
    }

    bool compareDataStruct(const DataStruct& data1, const DataStruct& data2)
    {
        if (data1.key1 < data2.key1)
        {
            return true;
        }
        else if (data1.key1 == data2.key1)
        {
            if (data1.key2 < data2.key2)
            {
                return true;
            }
            else if (data1.key2 == data2.key2)
            {
                return data1.key3.length() < data2.key3.length();
            }
        }
        return false;
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
