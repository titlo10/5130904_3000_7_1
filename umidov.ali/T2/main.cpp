#include "DataStruct.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

bool isSupported([[maybe_unused]] const DataStruct& data) {

    return true;
}

int main() {
    std::vector<DataStruct> dataVector;
    std::cout << "Start reading data...\n";

    DataStruct temp;
    bool hasSupported = false;
    while (std::cin >> temp) {
        if (isSupported(temp)) {
            hasSupported = true;
            dataVector.push_back(temp);
        }
    }

    if (!hasSupported) {
        std::cout << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
        return 0;
    }

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
