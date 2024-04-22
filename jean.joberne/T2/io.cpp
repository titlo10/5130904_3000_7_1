#include "io.h"

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    DataStruct input;
    {
        using sep = DelimiterIO;
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
                    char temp;
                    if (!(in >> temp)) {
                        break;
                    }
                    input.key1 = temp;
                    flag1 = true;
                }
                else if (key == "key2") {
                    if (!(in >> input.key2)) {
                        break;
                    }
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
