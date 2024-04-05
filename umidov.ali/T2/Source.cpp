#include "item_data.h"
using umidov::DataStruct;
int main()
{
    try
    {
        std::string userInput = "";
        std::vector<DataStruct> dataCollection;
        while (std::getline(std::cin, userInput))
        {
            std::istringstream inputStream(userInput);
            DataStruct temporaryData;
            if (inputStream >> temporaryData)
            {
                dataCollection.push_back(temporaryData);
            }
        }
        std::sort(std::begin(dataCollection), std::end(dataCollection), umidov::compareDataStruct);

        std::copy(std::begin(dataCollection), std::end(dataCollection), std::ostream_iterator<DataStruct>(std::cout, "\n"));
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
