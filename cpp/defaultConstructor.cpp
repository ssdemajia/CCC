#include <iostream>

class A {
public:
    A() { std::cout << "A Constructor\n"; }
};

class B {
public:
    B() { std::cout << "B Constructor\n"; }
};

class C {
public:
    C() { std::cout << "C Constructor\n"; }
};

class E {
public:
    E(int i) { std::cout << "E Constructor\n" << x << " " << c << std::endl;}
    int x;
    int* c;
};

class D {
public:
    D() :e(1){ 
        // A C B的默认构造函数会插入到这里    
        std::cout << "D Constructor\n"; 
    }

    A a;
    C c;
    E e;
    int f;
    B b;
};
int main()
{
    D d;
}