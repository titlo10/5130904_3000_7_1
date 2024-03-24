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
	void printFullNames()
	{
		std::cout << "abrosimov" << "." << "artem" << "\n";
	}
}

