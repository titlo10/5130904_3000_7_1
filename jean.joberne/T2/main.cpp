#include "io.h"
#include <algorithm>

int main() {
    try {
        std::vector<DataStruct> data;

        std::copy(std::istream_iterator<DataStruct>(std::cin), std::istream_iterator<DataStruct>(), std::back_inserter(data));

        std::sort(data.begin(), data.end(), compareDataStruct);

        std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
    }
    catch (std::exception& ex) {
        std::cerr << ex.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

