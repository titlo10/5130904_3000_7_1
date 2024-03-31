#include "DataStruct.h"
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <algorithm>

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}

std::istream& operator>>(std::istream& is, DataStruct& ds)
{
    std::string input, token;
    if (!std::getline(is, input, ')')) return is;
    std::replace(input.begin(), input.end(), ':', ' ');
    std::istringstream iss(input);
    while (iss >> token)
    {
        if (token == "key1")
        {
            iss >> ds.key1;
            iss.ignore(3);
        }
        else if (token == "key2")
        {
            std::string octStr;
            iss >> octStr;
            ds.key2 = std::stoull(octStr, nullptr, 8);
        }
        else if (token == "key3")
        {
            iss.ignore();
            std::getline(iss, ds.key3, '"');
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& ds)
{
    os << "(:key1 " << ds.key1 << "ull:key2 0" << std::oct << ds.key2 << ":key3 "" << ds.key3 << "":)";
    return os;
}

int main()
{
    std::vector<DataStruct> data;

    std::copy(std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data));

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}