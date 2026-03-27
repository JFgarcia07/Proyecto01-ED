//
// Created by jfgarcianata on 20/03/26.
//

#ifndef UNTITLED1_BNODO_H
#define UNTITLED1_BNODO_H

#include "../Estructuras/Producto.h"

class BNodo
{
    public:
    Producto* claves;
    BNodo** hijos;
    int numClaves;
    int grado;
    bool esHoja;

    BNodo(int grado, bool esHoja);
    ~BNodo();
};

#endif //UNTITLED1_BNODO_H