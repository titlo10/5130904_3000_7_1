#include "DataStruct.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>

std::istream& operator>>(std::istream& is, DataStruct& ds)
{
    std::string input;
    if (!std::getline(is, input, ')')) return is;
    input.erase(std::remove(input.begin(), input.end(), '('), input.end());
    std::replace(input.begin(), input.end(), ':', ' ');
    std::istringstream iss(input);
    std::string temp;
    while (iss >> temp)
    {
        if (temp == "key1")
        {
            std::string ullStr;
            iss >> ullStr;
            ds.key1 = std::stoull(ullStr.substr(0, ullStr.length() - 3));
        }
        else if (temp == "key2")
        {
            std::string octStr;
            iss >> octStr;
            ds.key2 = std::stoull(octStr, nullptr, 8);
        }
        else if (temp == "key3")
        {
            iss >> std::ws;
            std::getline(iss, ds.key3, '\"');
            std::getline(iss, ds.key3, '\"');
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& ds)
{
    os << "(:key1 " << ds.key1 << "ull:key2 0"
        << std::oct << ds.key2 << std::dec
        << ":key3 \"" << ds.key3 << "\":)";
    return os;
}

bool compareDataStructs(const DataStruct& a, const DataStruct& b)
{
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}

int main()
{
    std::vector<DataStruct> dataVector;
    DataStruct temp;

    std::cout << "Enter data, finish with EOF (Ctrl+D or Ctrl+Z):\n";

    while (std::cin >> temp)
    {
        dataVector.push_back(temp);
    }

    std::sort(dataVector.begin(), dataVector.end(), compareDataStructs);

    for (const auto& data : dataVector)
    {
        std::cout << data << "\n";
    }

    return 0;
}