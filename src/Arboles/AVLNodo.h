//
// Created by jfgarcianata on 14/03/26.
//

#ifndef UNTITLED1_AVLNODO_H
#define UNTITLED1_AVLNODO_H

#include "../Estructuras/Producto.h"

class AVLNodo
{
    public:
    Producto data;
    AVLNodo* izquierda;
    AVLNodo* derecha;
    int altura;

    AVLNodo(const Producto& producto);
    ~AVLNodo();
};

#endif //UNTITLED1_AVLNODO_H