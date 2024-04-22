#include "namespace.h"

namespace jean
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char character;
        in >> character;
        if (in && (character != dest.exp))
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

        double real_part = 0.0;
        double imag_part = 0.0;

        in >> DelimiterIO{ '(' } >> real_part >> imag_part >> DelimiterIO{ ')' };
        if (in)
        {
            dest.ref = std::complex<double>(real_part, imag_part);
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

    std::istream& operator>>(std::istream& in, ULLLiteralIO&& dest) {
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

    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct input;
        {
            using Delimiter = DelimiterIO;
            using ULL = ULLLiteralIO;
            using CMPDouble = CMPDoubleIO;
            using Double = DoubleIO;
            using String = StringIO;

            in >> Delimiter{ '(' };
            bool flag1 = false, flag2 = false, flag3 = false, flag4 = false;
            while (true) {
                if (flag1 && flag2 && flag3 && flag4) break;
                std::string key;
                char character;
                in >> character;
                if (!in) break;

                if (character == ':' && (in >> key))
                {
                    if (key == "CHR")
                    {
                        in >> ULL{ input.CHR };
                        flag1 = true;
                    }
                    else if (key == "LIT")
                    {
                        in >> Delimiter{ '#' } >> Delimiter{ 'c' } >> CMPDouble{ input.LIT };
                        flag2 = true;
                    }
                    else if (key == "RAT")
                    {
                        in >> String{ input.RAT };
                        flag3 = true;
                    }
                    else if (key == "LSP")
                    {
                        in >> Double{ input.LSP };
                        flag4 = true;
                    }
                }
            }
            in >> Delimiter{ ':' } >> Delimiter{ ')' };
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
        out << ":CHR " << std::uppercase << std::hex << "0x" << src.CHR;
        out << ":LIT " << std::fixed << std::setprecision(1) << "#c(" << src.LIT.real() << " " << src.LIT.imag() << ")";
        out << ":RAT \"" << src.RAT << "\"";
        out << ":LSP " << std::fixed << std::setprecision(2) << src.LSP;
        out << ":)";
        return out;
    }

    bool compareDataStruct(const DataStruct& ds_first, the DataStruct& ds_second)
    {
        double Magnitude_first = std::abs(ds_first.LIT),
               Magnitude_second = std::abs(ds_second.LIT);

        if (ds_first.CHR < ds_second.CHR)
        {
            return true;
        }
        else if (ds_first.CHR == ds_second.CHR)
        {
            if (Magnitude_first < Magnitude_second)
            {
                return true;
            }
            else if (Magnitude_first == Magnitude_second)
            {
                if (ds_first.RAT.length() < ds_second.RAT.length())
                {
                    return true;
                }
                else if (ds_first.RAT.length() == ds_second.RAT.length())
                {
                    return ds_first.LSP < ds_second.LSP;
                }
            }
        }
        return false;
    }

    iofmtguard::iofmtguard(std::basic_ios<char>& stream) :
        s_(stream),
        fill_(stream.fill()),
        precision_(stream.precision()),
        fmt_(stream.flags())
    {}

    iofmtguard::~iofmtguard()
    {
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }
}
