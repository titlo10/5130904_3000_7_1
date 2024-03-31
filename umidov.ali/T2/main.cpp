#include "DataStruct.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<DataStruct> dataVector;
    std::cout << "Start reading data...\n";

    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(dataVector)
    );

    std::cout << "Data reading completed.\nSorting...\n";

    std::sort(dataVector.begin(), dataVector.end(), compareDataStructs);

    std::cout << "Sorted data:\n";

    std::copy(
        dataVector.begin(),
        dataVector.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
