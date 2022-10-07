#include <iostream>

using namespace std;

class String
{
public:
    String(): s(nullptr), len(0) {}
    String(char* ss): s(ss), len(strlen(ss)){}
    char* s;
    int len;
};

class Object
{
public:
    Object() {}
    Object(char* ss): s(ss) {}
    String s;
};
int main()
{
    String s("test");
    String b = s;
    cout << b.s << endl;
    Object o1("test2");
   
    Object o2;
    o2 = o1;
    cout << o2.s.s << endl;
}