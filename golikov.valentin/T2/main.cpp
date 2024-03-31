#include "namespace.h"

const std::string EXP1 = "(:key2 #c(1.0 1.0):key3 \"Data\":key1 0xFFFF:)";
const std::string EXP2 = "(:key1 0xFFFF:key2 #c(1.0 5.0):key3 \"Data2\":)";
const std::string EXP3 = "(:key3 \"Data33\":key2 #c(-1.0 2.0):key1 0xFFFA:)";
const std::string EXP4 = "(:key1 0xAFFF:key2 #c(1.0 3.0):key3 \"Data444\":)";

using golikov::DataStruct;

int main()
{
  try
  {
    std::vector< DataStruct > data;
    std::istringstream iss1(EXP1);
    std::istringstream iss2(EXP2);
    std::istringstream iss3(EXP3);
    std::istringstream iss4(EXP4);

    //Запись в вектор (iss1)
    insertData(iss1, data);

    //Запись в вектор (iss2)
    insertData(iss2, data);

    //Запись в вектор (iss3)
    insertData(iss3, data);

    //Запись в вектор (iss4)
    insertData(iss4, data);

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
  catch (std::exception ex const&)
  {
    std::cerr << ex.what();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
