#include "tools.h"
#include <regex>
#include <iostream>

using namespace std;
int main() {
  // std::regex re("\\w+");
  std::smatch result;  // 在这个类型里存放匹配的选项
  std::string s = "root/a 1.txt(abcd) 2.txt(efgh)";

  vector<string> toks = split(s, " ");
  string & path = toks[0];

  std::regex re(R"((\w*\.\w*)\((\w*)\))"); // 使用R表示Raw string
  s = "1.txt(abcd)";
  if (!regex_match(s, result, re)) { // s表示待匹配的选项，也可以用迭代器
    cout << "Not found" << endl;
  }
  for (auto i: result) {
    cout << i << endl;
  }
  vector<int> v1{3,2};
  vector<int> v2{2,3};
  if (v1 < v2) {
    cout << "v1 < v2" << endl;
  }
}