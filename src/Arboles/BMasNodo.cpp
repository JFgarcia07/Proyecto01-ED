//
// Created by jfgarcianata on 26/03/26.
//

#include "BMasNodo.h"

using namespace std;

BMasNodo::BMasNodo(int grado, bool esHoja): siguiente(nullptr), numClaves(0), grado(grado), esHoja(esHoja)
{
    claves = new string[2*grado -1];
    if (esHoja)
    {
        data = new Producto[2*grado -1];
        hijo = nullptr;
    } else
    {
        data = nullptr;
        hijo =  new BMasNodo*[2*grado];

        for (int i = 0; i < 2*grado; i++)
        {
            hijo[i] = nullptr;
        }
    }
}

BMasNodo::~BMasNodo()
{
    delete[] claves;
    if (data != nullptr) {delete[] data;}
    if (hijo != nullptr){ delete[] hijo;}
}
