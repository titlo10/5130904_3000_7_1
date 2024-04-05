#ifndef _DATASTRUCT_H_
#define _DATASTRUCT_H_

#include <iostream>
#include <vector>
#include <complex>

using namespace std;

struct DataStruct
{
    unsigned long long key1;
    complex<double> key2;
    string key3;
};

struct UllIO
{
    unsigned long long &ref;
};

struct ComplexIO
{
    complex<double> &ref;
};

struct StringIO
{
    string &ref;
};

struct DelimiterIO
{
    string delimiter;
};

class ResPars
{
public:
    ResPars(basic_ios<char> &strm);
    ~ResPars();

private:
    basic_ios<char> &strm_;
    char fill_;
    streamsize precision_;
    basic_ios<char>::fmtflags fmtFlags_;
};

istream& operator>>(istream &in, DelimiterIO&& dest);
istream& operator>>(istream &in, UllIO &dest);
istream& operator>>(istream &in, ComplexIO &dest);
istream& operator>>(istream &in, StringIO &dest);
istream& operator>>(istream &in, DataStruct &dest);
ostream& operator<<(ostream &out, const DataStruct &dest);

#endif

