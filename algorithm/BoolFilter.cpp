/*
布隆过滤器
*/
#include <iostream>
#include <functional>
#include <string>

using namespace std;

function<int(string&)> h1 = [](string & s) {
  int hash = 131452033;
  for (char c : s) {
    hash ^= ((hash<<5) + c + (hash >> 2));
  }
  return hash;
};

int main() {
  
}
