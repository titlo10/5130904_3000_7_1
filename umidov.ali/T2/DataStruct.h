#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

struct DataStruct {
    unsigned long long key1 = 0;
    unsigned long long key2 = 0;
    std::string key3;

    DataStruct() = default;

    friend std::istream& operator>>(std::istream& is, DataStruct& ds)
    {
        std::string input, temp;
        if (!std::getline(is, input, ')')) return is;
        std::replace(input.begin(), input.end(), ':', ' ');
        std::istringstream iss(input);
        while (iss >> temp)
        {
            try
            {
                if (temp == "key1")
                {
                    std::string ullStr;
                    iss >> ullStr;
                    ullStr.erase(ullStr.size() - 3);
                    ds.key1 = std::stoull(ullStr, nullptr, 10);
                }
                else if (temp == "key2")
                {
                    std::string octStr;
                    iss >> octStr;
                    ds.key2 = std::stoull(octStr, nullptr, 8);
                }
                else if (temp == "key3") {
                    iss >> std::ws;
                    std::getline(iss, ds.key3, '\"');
                    std::getline(iss, ds.key3, '\"');
                }
            }
            catch (const std::invalid_argument& ia)
            {
                std::cerr << "Invalid argument: " << ia.what() << '\n';
                is.setstate(std::ios::failbit);
                break;
            }
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const DataStruct& ds)
    {
        os << "(:key1 " << ds.key1 << "ull:key2 0" << std::oct << ds.key2 << std::dec << ":key3 \"" << ds.key3 << "\":)";
        return os;
    }
};

bool compareDataStructs(const DataStruct& a, const DataStruct& b);

#endif