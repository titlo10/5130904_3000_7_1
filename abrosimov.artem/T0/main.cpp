#include <iostream>

namespace abrosimov
{
    void printFullName();
}

int main()
{
    abrosimov::printFullName();

    return 0;
}

namespace abrosimov
{
    void printFullName()
    {
        std::cout << "abrosimov.artem" << std::endl;
    }
}