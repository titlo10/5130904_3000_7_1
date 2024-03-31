#pragma once

#include <iostream>
#include <string>

struct DataStruct {
	std::string key1;
	std::string key2;
	std::string key3;
};

std::istream& operator>>(std::istream& is, DataStruct& data);
std::ostream& operator<<(std::ostream& os, const DataStruct& data);
bool compareDataStructs(const DataStruct& a, const DataStruct& b);
