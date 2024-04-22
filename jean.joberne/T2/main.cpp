#include "io.h"
#include <algorithm>

int main() {
    try {
        std::vector<DataStruct> data;

        // Read DataStructs from standard input
        std::copy(std::istream_iterator<DataStruct>(std::cin), std::istream_iterator<DataStruct>(), std::back_inserter(data));

        // Sort the data
        std::sort(data.begin(), data.end(), compareDataStruct);

        // Output sorted data
        std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
    }
    catch (std::exception& ex) {
        std::cerr << ex.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
