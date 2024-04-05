#include "item_data.h"
using namespace myspace;
int main() {
    std::vector<ItemData> items;
    ItemData tempItem;
    std::string tempLine;
    while (std::getline(std::cin, tempLine, ')')) {
        std::istringstream itemStream (tempLine + ')');
        if (itemStream >> tempItem) {
            items.push_back(tempItem);
        }
        else {
            std::cerr << "Failed to parse item." << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
