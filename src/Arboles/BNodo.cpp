//
// Created by jfgarcianata on 20/03/26.
//

#include "BNodo.h"

BNodo::BNodo(int grado, bool esHoja): numClaves(0), grado(grado), esHoja(esHoja)
{
    //MAX DE CLAVES = 2T -1
    //MAX DE HIJOS = 2T
    claves = new Producto[2*grado - 1];
    hijos = new BNodo*[2*grado];
    for (int i = 0; i < 2*grado - 1; i++)
    {
        hijos[i] = nullptr;
    }
}

BNodo::~BNodo()
{
    delete[] hijos;
    delete[] claves;
}
