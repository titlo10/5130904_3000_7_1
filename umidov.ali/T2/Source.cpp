#include "io.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
namespace umidov
{
    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::string part;
        while (std::getline(in, part, ';'))
        {
            if (part.find("key1") != std::string::npos)
            {
                std::string number = part.substr(part.find("=") + 1);
                dest.key1 = stod(number);
            }
            else if (part.find("key2") != std::string::npos)
            {
                std::string number = part.substr(part.find("=") + 1);
                unsigned long long octValue = std::stoull(number, nullptr, 8);
                dest.key2 = static_cast<char>(octValue & 0xFF);
            }
            else if (part.find("key3") != std::string::npos)
            {
                dest.key3 = part.substr(part.find("=") + 1);
            }
        }
        return in;
    }
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest)
    {
        out << "key1=" << dest.key1 << "; ";
        out << "key2=" << static_cast<int>(dest.key2) << "; ";
        out << "key3=" << dest.key3;
        return out;
    }
}
