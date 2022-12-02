#include <iostream>
// c++ -std=c++17 property.cpp -fdeclspec
using namespace std;
class IEntity
{
public:
    __declspec(property(get=_GetTransform, put=_SetTransform))
    int _Transform;

    int const & _GetTransform() {
        std::cout << "1";
        return 1;
    }

    void _SetTransform(int const & newValue) {
        std::cout << "_SetTransform\n";

    }
};

int main()
{
    IEntity entity;
    entity._Transform = 1;
}