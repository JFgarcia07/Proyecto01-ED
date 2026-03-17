//
// Created by jfgarcianata on 16/03/26.
//

#ifndef UNTITLED1_NODOHASH_H
#define UNTITLED1_NODOHASH_H
#include "../Estructuras/Producto.h"

class NodoHash
{
    public:
    Producto producto;
    NodoHash* siguiente;

    NodoHash(const Producto& produto);
    ~NodoHash();
};

#endif //UNTITLED1_NODOHASH_H