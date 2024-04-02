#ifndef ITEM_DATA_H
#define ITEM_DATA_H
#include <iostream>
#include <string>
#include <sstream>
namespace myspace {
    struct ItemData {
        double key1 = 0.0;
        char key2 = '\0';
        std::string key3;
        friend std::istream& operator>>(std::istream& in, ItemData& item);
        friend std::ostream& operator<<(std::ostream& out, const ItemData& item);
    };
}
#endif
