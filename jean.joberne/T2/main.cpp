#include "namespace.h"
#include <iterator>

int main()
{
    try
    {
        std::string input = "";
        std::vector<jean::DataStruct> data;

        while (std::getline(std::cin, input))
        {
            std::istringstream iss(input);
            jean::DataStruct temp;
            if (iss >> temp)
            {
                data.push_back(temp);
            }
        }

        std::sort(data.begin(), data.end(), jean::compareDataStruct);

        std::copy(
            data.begin(),
            data.end(),
            std::ostream_iterator<jean::DataStruct>(std::cout, "\n")
        );
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
