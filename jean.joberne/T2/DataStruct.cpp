#include "DataStruct.h"

std::istream& jean::operator>>(std::istream& in, DataStruct& value) {
    std::istream::sentry guard(in);
    if (!guard) {
        return in;
    } else {
        using Del = Delimiter;
        using StrDel = StringDelimiter;
        char openBracket, closeBracket;
        in >> openBracket;
        if (openBracket != '(') {
            in.setstate(std::ios_base::failbit);
            return in;
        }
        for (size_t i = 0; i < 3; i++) {
            int keyNum = 0;
            in >> StrDel{":key"} >> keyNum;
            if (keyNum == 1) {
                in >> Del{'\''} >> value.key1 >> Del{'\''};
            } else if (keyNum == 2) {
                long long n = 0;
                unsigned long long d = 0;
                char start, end;
                in >> StrDel{"(:N"} >> n >> StrDel{":D"} >> d >> StrDel{":)"} >> start;
                if (start != '(') {
                    in.setstate(std::ios_base::failbit);
                    return in;
                }
                value.key2.first = n;
                value.key2.second = d;
            } else if (keyNum == 3) {
                in >> Del{'"'};
                std::getline(in, value.key3, '"');
            } else {
                in.setstate(std::ios_base::failbit);
                return in;
            }
        }
        in >> closeBracket;
        if (closeBracket != ')') {
            in.setstate(std::ios_base::failbit);
            return in;
        }
    }
    return in;
}
