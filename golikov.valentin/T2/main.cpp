#include "namespace.h"

//const std::string EXP1 = "(:key2 #c(1.0 1.0):key3 \"Data\":key1 0xFFFF:)";

using golikov::DataStruct;

int main()
{
  try
  {
    std::string input;
    while (true)
    {
      std::string buf;

      std::getline(std::cin, buf, '\n');

      if (buf == "" || std::cin.eof())
        break;

      input += buf + '\n';
    }

    std::vector< DataStruct > data;
    std::istringstream iss(input);

    //Запись в вектор (iss1)
    insertData(iss, data);

    //Сортировка вектора
    std::sort(std::begin(data), std::end(data), golikov::compareDataStruct);

    std::cout << "Data:\n";

    //Вывод вектора с отсортированой информацией
    std::copy(
      std::begin(data),
      std::end(data),
      std::ostream_iterator< DataStruct >(std::cout, "\n")
    );
  }
  catch (std::exception& ex)
  {
    std::cerr << ex.what();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
