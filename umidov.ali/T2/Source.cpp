#include "header.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <charconv>
namespace umidov {
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest) {
        out << "key1=" << dest.key1 << "; ";
        out << "key2=" << static_cast<int>(dest.key2) << "; ";
        out << "key3=" << dest.key3;
        return out;
    }
    std::istream& operator>>(std::istream& in, DataStruct& dest) {
        std::string part;
        while (std::getline(in, part, ';')) {
            if (part.find("key1") != std::string::npos) {
                std::string number = part.substr(part.find("=") + 1);
                try {
                    dest.key1 = std::stod(number);
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Ошибка преобразования key1: " << e.what() << '\n';
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "Ошибка преобразования key1: " << e.what() << '\n';
                }
            }
            else if (part.find("key2") != std::string::npos) {
                std::string value = part.substr(part.find("=") + 1);
                if (value.front() == '\'') {
                    dest.key2 = value.at(1);
                }
                else if (value.front() == '0' && (value.at(1) == 'x' || value.at(1) == 'X')) {
                    unsigned long long hexValue = std::stoull(value, nullptr, 16);
                    dest.key2 = static_cast<char>(hexValue & 0xFF);
                }
            }
            else if (part.find("key3") != std::string::npos) {
                dest.key3 = part.substr(part.find("=") + 1);
            }
        }
        return in;
    }
}
