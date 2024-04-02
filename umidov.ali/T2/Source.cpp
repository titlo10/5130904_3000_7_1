#include "header.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
namespace umidov {
    std::istream& operator>>(std::istream& in, DataStruct& dest) {
        std::string part;
        bool isValidRecord = false;
        while (std::getline(in, part, ';')) {
            if (part.find("key1") != std::string::npos) {
                std::string number = part.substr(part.find("=") + 1);
                try {
                    dest.key1 = std::stod(number);
                }
                catch (const std::exception& e) {
                    std::cerr << "Ошибка преобразования key1: " << e.what() << '\n';
                }
            }
            else if (part.find("key2") != std::string::npos) {
                std::string value = part.substr(part.find("=") + 1);
                try {
                    if (value.front() == '\'') {
                        dest.key2 = value.at(1);
                    }
                    else if (value.front() == '0' && (value.at(1) == 'x' || value.at(1) == 'X')) {
                        unsigned long long hexValue = std::stoull(value, nullptr, 16);
                        dest.key2 = static_cast<char>(hexValue & 0xFF);
                    }
                    else {
                        throw std::invalid_argument("Неподдерживаемый формат key2");
                    }
                }
                catch (const std::exception& e) {
                    std::cerr << "Ошибка обработки key2: " << e.what() << '\n';
                }
            }
            else if (part.find("key3") != std::string::npos) {
                dest.key3 = part.substr(part.find("=") + 1);
            }
        }
        return in;
    }
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest) {
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
