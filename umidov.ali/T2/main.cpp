#include "item_data.h"
#include <vector>
#include <algorithm>
#include <iterator>
using namespace myspace;
int main() {
    std::vector<ItemData> items;
    ItemData tempItem;
    while (std::cin >> tempItem) {
        items.push_back(tempItem);
    }
    std::sort(items.begin(), items.end(), [](const ItemData& a, const ItemData& b) {
        if (a.key1 != b.key1) return a.key1 < b.key1;
        if (a.key2 != b.key2) return a.key2 < b.key2;
        return a.key3.length() < b.key3.length();
        });
    for (const auto& item : items) {
        std::cout << item << std::endl;
    }
    return 0;
}
