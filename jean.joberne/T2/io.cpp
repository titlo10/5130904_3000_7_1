#include "io.h"

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    char null = '0';
    in >> null;
    if (in && (null != dest.exp)) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, ULongLiteralIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    return in >> dest.ref;
}

std::istream& operator>>(std::istream& in, ULongBinaryLiteralIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    return in >> dest.ref;
}

std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
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
        while (true) {
            if (flag1 && flag2 && flag3) {
                break;
            }
            std::string key;
            char c;
            in >> c;
            if (!in) {
                break;
            }

            if (c == ':' && (in >> key)) {
                if (key == "key1") {
                    in >> ull{ input.key1 };
                    flag1 = true;
                }
                else if (key == "key2") {
                    in >> sep{ ' ' } >> ull{ input.key2 };
                    flag2 = true;
                }
                else if (key == "key3") {
                    in >> str{ input.key3 };
                    flag3 = true;
                }
            }
        }
        in >> sep{ ':' } >> sep{ ')' };
    }
    if (in) {
        dest = input;
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
        return out;
    }
    out << "(:" << "key1 " << src.key1 << " key2 " << src.key2 << " key3 \"" << src.key3 << "\":)";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    else if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }
    else {
        return a.key3.length() < b.key3.length();
    }
}

iofmtguard::iofmtguard(std::basic_ios<char>& s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
{}

iofmtguard::~iofmtguard() {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
}
