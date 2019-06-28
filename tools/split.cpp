#include "tools.h"

using namespace std;
vector<string> split(string &s, string delim) {
  int start = 0;
  int pos = -1;
  vector<string> result;
  do{
    pos = s.find(delim, start);
    if (pos == -1) {
      result.push_back(s.substr(start));
    }
    else {
      result.push_back(s.substr(start, pos-start));
    }
    start = pos+1;
  }while (pos != -1);
  return result;
}
