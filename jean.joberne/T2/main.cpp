#include "io.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace jean;

int main()
{
    std::vector<DataStruct> data;
    DataStruct temp;

    while (std::cin >> temp) {
        data.push_back(temp);
    }

    std::sort(data.begin(), data.end(), compareDataStruct);

    for (const auto& item : data) {
        std::cout << item << std::endl;
    }

    return 0;
}
