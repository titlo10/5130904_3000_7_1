#include "item_data.h"
namespace myspace {
    std::istream& operator>>(std::istream& in, ItemData& item) {
        std::string part;
        while (std::getline(in, part, ';')) {
            std::stringstream partStream(part);
            std::string key, value;
            if (std::getline(partStream, key, '=') && std::getline(partStream, value)) {
                if (key == "key1") {
                    item.key1 = std::stod(value);
                }
                else if (key == "key2" && !value.empty()) {
                    item.key2 = value.front();
                }
                else if (key == "key3") {
                    item.key3 = value;
                }
            }
        }
        return in;
    }
    std::ostream& operator<<(std::ostream& out, const ItemData& item) {
        out << "key1=" << item.key1 << "; ";
        out << "key2=" << item.key2 << "; ";
        out << "key3=" << item.key3;
        return out;
    }
}
