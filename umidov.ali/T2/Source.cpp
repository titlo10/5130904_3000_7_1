#include "item_data.h"
namespace myspace {
    std::istream& operator>>(std::istream& in, ItemData& item) {
        std::string line;
        if (!std::getline(in, line, ')')) {
            in.setstate(std::ios::failbit);
            return in;
        }
        std::istringstream iss(line.substr(1));
        std::string key, value;
        char delim;
        while (iss >> key >> delim && delim == ' ' && std::getline(iss, value, ':')) {
            if (key == "key1") {
                item.key1 = std::stoull(value.substr(0, value.find("ull")));
            }
            else if (key == "key2") {
                item.key2 = value[1];
            }
            else if (key == "key3") {
                item.key3 = value.substr(1, value.length() - 2);
            }
            if (iss.peek() == ' ') iss.ignore();
        }
        return in;
    }
    std::ostream& operator<<(std::ostream& out, const ItemData& item) {
        out << "(:key1 " << item.key1 << "ull:key2 '" << item.key2 << "':key3 \"" << item.key3 << "\":)";
        return out;
    }
}
