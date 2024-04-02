#include "header.h"
#include <iostream>
#include <string>
#include <sstream>
namespace umidov {
    std::istream& operator>>(std::istream& in, DataStruct& dest) {
        std::string part;
        bool isKey1Found = false, isKey2Found = false, isKey3Found = false;
        while (std::getline(in, part, ';')) {
            std::stringstream ss(part);
            std::string key, value;
            if (std::getline(ss, key, '=') && std::getline(ss, value)) {
                if (key == "key1") {
                    dest.key1 = std::stod(value);
                    isKey1Found = true;
                }
                else if (key == "key2") {
                    isKey2Found = true;
                }
                else if (key == "key3") {
                    dest.key3 = value;
                    isKey3Found = true;
                }
                if (!(isKey1Found || isKey2Found || isKey3Found)) {
                    std::cerr << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
                }
            }
        }
          return in;
    }
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest)
    {
        out << "key1=" << dest.key1 << "; ";
        if (dest.key2 == '\0') {
            out << "key2=[NUL]; ";
        }
        else {
            out << "key2=" << dest.key2 << "; ";
        }
        out << "key3=" << dest.key3;
        return out;
    }
    }
