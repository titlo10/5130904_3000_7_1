#include "DataStruct.h"
#include <vector>
#include <algorithm>
#include <iterator>
using namespace umidov;
int main() {
    std::vector<DataStruct> data;
    DataStruct temp;
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        if (iss >> temp)
        {
            data.push_back(temp);
        }
    }
    std::sort(data.begin(), data.end(), [](const DataStruct& a, const DataStruct& b) {
        if (a.key1 != b.key1)
            return a.key1 < b.key1;
        if (a.key2 != b.key2)
            return a.key2 < b.key2;
        return a.key3.length() < b.key3.length();
        });
    std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
    return 0;
}