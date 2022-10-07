#include <fstream>
#include <iostream>

int main()
{
    const int pts = 2;
    std::ifstream ifs;
    std::string fname = "iostream.txt";
    ifs.open(fname.c_str());

    double *dumypT        = new double [pts];
    double *dumyAmplitude = new double [pts];
    double * a = dumypT;
    double *b = dumyAmplitude;
    for (int i = 0; i < pts; ++i)
    {
        ifs >> *dumypT >> *dumyAmplitude;   // --- 怎样才能自增的读入数据元素？

        std::cout << i << " " << a[i] << " " << b[i] << std::endl;

        dumypT++; dumyAmplitude++;
    }
}

