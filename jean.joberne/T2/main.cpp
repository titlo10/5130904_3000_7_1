#include "namespace.h"

using namespace jean;

int main() {
    std::vector<DataStruct> data;
    DataStruct tmp;

    while (std::cin >> tmp) {
        data.push_back(tmp);
    }

    std::sort(data.begin(), data.end(), comparator);

    for (const auto& ds : data) {
        std::cout << ds << '\n';
    }

    return 0;
}
