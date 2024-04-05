#include<iostream>
#include<string>
#include<limits>
#include"DataStruct.h"
using namespace std;

istream& operator>>(istream& in,DelimiterIO&& dest)
{
 istream::sentry sentry(in);
 if (!sentry)
 {
  return in;
 }
 string del;
 size_t tSize=dest.delimiter.length();
 in>>setw(tSize)>>del;
 if (!in)
 {
  return in;
 }
 if (dest.delimiter!=del)
 {
  in.setstate(ios_base::failbit);
 }
 return in;
}

istream& operator>>(istream& in,UllIO&& dest)
{
 istream::sentry sentry(in);
 ResPars rGard(in);
 if (!sentry)
 {
  return in;
 }
 if (!(in>>oct>>dest.ref))
 {
  return in;
 }
 return in;
}

istream& operator>>(istream& in,ComplexIO&& dest)
{
 istream::sentry sentry(in);
 if (!sentry)
 {
  return in;
 }
 string del;
 double real,imag;
 if (!(in>>DelimiterIO{"#c("}))
 {
  return in;
 }
 if (!(in>>real>>imag))
 {
  return in;
 }
 if (!(in>>DelimiterIO{")"}))
 {
  return in;
 }
 dest.ref=complex<double>(real,imag);
 return in;
}

istream& operator>>(istream& in,StringIO&& dest)
{
 istream::sentry sentry(in);
 if (!sentry)
 {
  return in;
 }
 return getline(in>>DelimiterIO{"\""},dest.ref,'"');
}

istream& operator>>(istream& in,DataStruct& dest)
{
 istream::sentry sentry(in);
 if (!sentry)
 {
  return in;
 }
 in>>DelimiterIO{"(:"};
 if (!in)
  return in;

 for (int i=0; i<3; i++)
 {
  string key;
  if (!(in>>key))
   return in;

  if (key=="key1")
  {
   if (!(in>>UllIO{dest.key1}))
    return in;
  }
  else if (key=="key2")
  {
   if (!(in>>ComplexIO{dest.key2}))
    return in;
  }
  else if (key=="key3")
  {
   if (!(in>>StringIO{dest.key3}))
    return in;
  }
  else
  {
   in.setstate(ios_base::failbit);
   return in;
  }
  in>>DelimiterIO{":"};
  if (!in)
   return in;
 }
 in>>DelimiterIO{")"};

 return in;
}

ostream& operator<<(ostream& out,const DataStruct& dest)
{
 ostream::sentry sentry(out);
 if (!sentry)
 {
  return out;
 }

 ResPars rGard(out);

 out<<"(:key1 "<<"0"<<oct<<dest.key1<<
      ":key2 "<<"#c("<<fixed<<setprecision(1)<<dest.key2.real()<<" "<<
      fixed<<setprecision(1)<<dest.key2.imag()<<")"<<
      ":key3 \""<<dest.key3<<"\":)";
 return out;
}

ResPars::ResPars(basic_ios<char>& strm):
  strm_(strm),
  fill_(strm.fill()),
  precision_(strm.precision()),
  fmtFlags_(strm.flags())
{}

ResPars::~ResPars()
{
  strm_.fill(fill_);
  strm_.precision(precision_);
  strm_.flags(fmtFlags_);
}

