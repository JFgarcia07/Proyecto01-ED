//
// Created by jfgarcianata on 13/03/26.
//

#ifndef UNTITLED1_NODO_H
#define UNTITLED1_NODO_H
#include "Producto.h"

class Nodo
{
    public:
    Producto data;
    Nodo* siguiente;

    Nodo(const Producto& producto);
    ~Nodo();
};
#endif //UNTITLED1_NODO_H