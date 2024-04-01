#include "DataStruct.h"
#include <sstream>
#include <iomanip>
#include <limits>
#include <ios>
#include <charconv>
#include <cctype>
namespace umidov
{
    bool isAllDigits(const std::string& str) {
        for (char c : str) {
            if (!isdigit(static_cast<unsigned char>(c))) return false;
        }
        return true;
    }
    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::string line;
        if (std::getline(in, line))
        {
            std::istringstream iss(line);
            std::string key;
            while (iss >> key)
            {
                try {
                    if (key == "(:key1")
                    {
                        if (!(iss >> dest.key1)) { throw std::runtime_error("Invalid key1 value"); }
                    }
                    else if (key == ":key2")
                    {
                        std::string octalValue;
                        if (!(iss >> std::ws) || !std::getline(iss, octalValue, ':') || octalValue.empty() || !isAllDigits(octalValue)) {
                            throw std::runtime_error("Invalid key2 value");
                        }
                        dest.key2 = std::stoull(octalValue, nullptr, 8);
                    }
                    else if (key == ":key3")
                    {
                        if (!(iss.ignore(std::numeric_limits<std::streamsize>::max(), '"')) || !std::getline(iss, dest.key3, '"')) {
                            throw std::runtime_error("Invalid key3 value");
                        }
                    }
                }
                catch (const std::exception& e) {
                    std::cerr << "Error reading DataStruct: " << e.what() << '\n';
                    in.setstate(std::ios::failbit);
                    break;
                }
            }
        }
        return in;
    }
    std::ostream& operator<<(std::ostream& out, const DataStruct& src)
    {
        out << "(:key1 " << src.key1
            << ":key2 " << std::oct << src.key2 << std::dec
            << ":key3 \"" << src.key3 << "\":)";
        return out;
    }
}
