#include "header.h"
#include <iostream>
#include "header.h"
#include <iostream>
using namespace umidov;
int main() {
    umidov::DataStruct data;
    setlocale(LC_ALL, "rus");
    auto initialKey1 = data.key1;
    std::cout << "Начальное значение key1: " << initialKey1 << std::endl;
    std::cout << "Введите данные в формате key1=<double>;key2=<oct>;key3=<string>:" << std::endl;
    std::cin >> data;
    auto str = data.key3;
    for (auto c : str) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
    return 0;
}
