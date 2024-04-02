#include "header.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace umidov;
int main() {
    setlocale(LC_ALL,"rus");
    umidov::DataStruct data;
    std::cin >> data;
    std::cout << data << std::endl;
    return 0;
}
