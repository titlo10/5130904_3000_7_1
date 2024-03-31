#include "DataStruct.h"
#include <iostream>
#include <vector>
#include <algorithm>


int main()
{
    std::vector<DataStruct> dataVector;
    std::cout << "Start reading data...\n";

    DataStruct data;
    while (std::cin >> data)
    {
        dataVector.push_back(data);
    }

    if (dataVector.empty())
    {
        std::cerr << "Looks like there are no supported records. Cannot determine input. Test skipped." << std::endl;
        return 0;
    }

    std::cout << "Data reading completed." << std::endl;
    std::cout << "Sorting..." << std::endl;

    std::sort(dataVector.begin(), dataVector.end(), compareDataStructs);

    std::cout << "Sorted data:" << std::endl;

    for (const auto& d : dataVector)
    {
        std::cout << d << std::endl;
    }

    return 0;
}