#include "header.h"
#include <iostream>
using namespace umidov;
int main() {
    setlocale(LC_ALL, "rus");
    DataStruct data;
    std::cout << "Введите данные в формате key1=<значение>;key2=<значение>;key3=<строка>:" << std::endl;
    std::cin >> data;
    std::cout << "Вы ввели:" << std::endl;
    std::cout << data << std::endl;
    return 0;
}
