#include "namespace.h"

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

    std::istream& operator>>(std::istream& in, ULLLitIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, ULLOctIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> std::oct >> dest.ref;
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
        std::string input;
        in >> input;
        if (input != dest.exp)
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
            using ULL_LIT = ULLLitIO;
            using ULL_OCT = ULLOctIO;
            using str = StringIO;

            in >> sep{ '(' };
            bool flag1 = false, flag2 = false, flag3 = false;
            while (true) {
                if (flag1 && flag2 && flag3) break;
                std::string key;
                char c;
                in >> c;
                if (!in) break;

                if (c == ':' && (in >> key))
                {
                    if (key == "key1")
                    {
                        in >> ULL_LIT{ input.key1 };
                        flag1 = true;
                    }
                    else if (key == "key2")
                    {
                        in >> ULL_OCT{ input.key2 };
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
        out << "(:key1 " << src.key1 << ":key2 " << std::oct << src.key2 << ":key3 \"" << src.key3 << "\":)";
        return out;
    }

    bool compareDataStruct(const DataStruct& ds_first, const DataStruct& ds_second)
    {
        if (ds_first.key1 != ds_second.key1)
        {
            return ds_first.key1 < ds_second.key1;
        }
        else if (ds_first.key2 != ds_second.key2)
        {
            return ds_first.key2 < ds_second.key2;
        }
        else
        {
            return ds_first.key3.length() < ds_second.key3.length();
        }
    }
}
