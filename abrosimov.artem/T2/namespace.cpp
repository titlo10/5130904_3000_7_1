#include "namespace.h"

namespace abrosimov
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
    std::istream& operator>>(std::istream& in, ULongLiteralIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string input;
        in >> input;
        dest.ref = std::stoull(input);
        return in;
    }
    std::istream& operator>>(std::istream& in, ULongBinaryLiteralIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in; // Ќе удалось установить sentry, возврат input stream
        }
        std::string input;
        in >> input;
        // ѕример обработки двоичного литерала (например, преобразование из бинарной строки)
        if (input.size() > 2 && input.substr(0, 2) == "0b")
        {
            dest.ref = std::bitset<64>(input.substr(2)).to_ullong();
        }
        else
        {
            in.setstate(std::ios::failbit); // Ќеправильный формат ввода, установка failbit
        }

        return in;
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
            using ull = ULongLiteralIO;
            using ulbl = ULongBinaryLiteralIO;
            using str = StringIO;

            in >> sep{ '(' };
            bool flag1 = false;
            bool flag2 = false;
            bool flag3 = false;
            while (true)
            {
                if (flag1 && flag2 && flag3)
                {
                    break;
                }
                std::string key;
                char c;
                in >> c;
                if (!in)
                {
                    break;
                }

                if (c == ':' && (in >> key))
                {
                    if (key == "key1")
                    {
                        in >> ull{ input.key1 };
                        flag1 = true;
                    }
                    else if (key == "key2")
                    {
                        in >> ulbl{ input.key2 };
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
        out << ":key1 " << src.key1;
        out << ":key2 " << "0b" << src.key2;
        out << ":key3 " << "\"" << src.key3 << "\"" << ":";
        out << ")";
        return out;
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