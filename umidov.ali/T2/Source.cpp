#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "DataStruct.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "DataStruct.h" 
unsigned long long readOctal(const std::string& str)
{
    unsigned long long value = 0;
    std::istringstream iss(str);
    iss >> std::oct >> value;
    return value;
}
std::istream& umidov::operator>>(std::istream& in, umidov::DataStruct& dest)
{
    std::string line;
    if (std::getline(in, line))
    {
        std::istringstream iss(line);
        std::string key;
        while (iss >> key)
        {
            if (key == "(:key1")
            {
                iss >> dest.key1;
            }
            else if (key == ":key2")
            {
                std::string octalValue;
                iss >> octalValue;
                dest.key2 = readOctal(octalValue.substr(0, octalValue.find(':')));
            }
            else if (key == ":key3")
            {
                iss.ignore(std::numeric_limits<std::streamsize>::max(), '"');
                std::getline(iss, dest.key3, '"');
            }
        }
    }
    return in;
}
std::ostream& umidov::operator<<(std::ostream& out, const umidov::DataStruct& src)
{
    out << "(:key1 " << src.key1
        << ":key2 " << std::oct << src.key2 << std::dec
        << ":key3 \"" << src.key3 << "\":)";
    return out;
}
