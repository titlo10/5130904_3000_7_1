#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <iterator>
#include "DataStruct.h"
using namespace std;

int main() {
    vector<DataStruct> ds_original;
    DataStruct temp;
    while (cin >> temp) {
        ds_original.push_back(temp);
    }

    sort(ds_original.begin(), ds_original.end(),
        [](const DataStruct &ds1, const DataStruct &ds2) {
            if (ds1.key1 != ds2.key1)
                return ds1.key1 < ds2.key1;
            if (abs(ds1.key2) != abs(ds2.key2))
                return abs(ds1.key2) < abs(ds2.key2);
            return ds1.key3.length() < ds2.key3.length();
        }
    );
    copy(ds_original.begin(), ds_original.end(), ostream_iterator<DataStruct>(cout, "\n"));
    return 0;
}

