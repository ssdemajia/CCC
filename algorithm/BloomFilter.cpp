/*
布隆过滤器
*/
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

function<unsigned int(string&)> hashfunc1 = [](string & s) {
  unsigned int hash = 131452033;
  for (char c : s) {
    hash ^= ((hash<<5) + c + (hash >> 2));
  }
  return hash;
};

function<unsigned int(string&)> hashfunc2 = [](string & s) {
  int hash = 0xAAAAAAA;
  for (char c : s) {
    hash ^= ((c & 1) == 0) ? (  (hash <<  7) ^ c * (hash >> 3)) :  
                               (~((hash << 11) + c ^ (hash >> 5)));  
  }
  return hash;
};

function<unsigned int(string&)> hashfunc3 = [](string & s) {
  unsigned int hash = 0xA92B1;
  for (char c : s) {
    hash ^= ((hash<< c) + (hash ^ c) | (hash ));
  }
  return hash;
};

class BloomFilter {
  public:
    BloomFilter(int length = 32):length(length) {
      hashs = {hashfunc1, hashfunc2, hashfunc3};
    }
    void add(string s) {
      for (auto f: hashs) {
        unsigned int h = f(s)%length;
        set_bit(h);
      }
    }
    bool isExist(string s) {
      for (auto f: hashs) {
        if (!has_bit(f(s))) return false;
      }
      return true;
    }
  private:
    void set_bit(int pos) {
      cont |= (1 << pos);
    }
    bool has_bit(int pos) {
      return (cont&(1<<pos)) != 0;
    }
    vector<function<unsigned int(string&)>> hashs;
    int length;
    unsigned int cont;
};
int main() {
  BloomFilter f;
  f.add("shao");
  f.add("shuai");
  assert(f.isExist("shao"));
  assert(f.isExist("shuai"));
}
