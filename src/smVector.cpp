//-------------------------------------------------------------------
//-------------------------------------------------------------------

#include "smVector.hpp"

using namespace std;

//-------------------------------------------------------------------


inline static
istream &eatChar(char c,istream &buf) {
  char r;
  buf >> r;
  if (r!=c) {
    buf.clear(buf.rdstate() | ios::failbit);
  }
  return buf;
}

//-------------------------------------------------------------------

istream &operator>>(istream &strm,SmVector3 &v) {
  ios::fmtflags orgFlags = strm.setf(ios::skipws);
  eatChar('[',strm);
  strm >> v[0];
  eatChar(',',strm);
  strm >> v[1];
  eatChar(',',strm);
  strm >> v[2];
  eatChar(']',strm);
  strm.flags(orgFlags);
  return strm;
}
  

ostream &operator<<(ostream &strm,const SmVector3 &v) {
  strm << "[";
  strm << v[0]; strm << ",";
  strm << v[1]; strm << ",";
  strm << v[2]; strm << "]";
  return strm;
}

//-------------------------------------------------------------------


istream &operator>>(istream &strm,SmVector2 &v) {
  ios::fmtflags orgFlags = strm.setf(ios::skipws);
  eatChar('[',strm);
  strm >> v[0];
  eatChar(',',strm);
  strm >> v[1];
  eatChar(']',strm);
  strm.flags(orgFlags);
  return strm;
}
  

ostream &operator<<(ostream &strm,const SmVector2 &v) {
  strm << "[";
  strm << v[0]; strm << ",";
  strm << v[1]; strm << "]";
  return strm;
}

//-------------------------------------------------------------------


