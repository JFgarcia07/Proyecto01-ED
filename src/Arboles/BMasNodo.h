//
// Created by jfgarcianata on 26/03/26.
//

#ifndef UNTITLED1_BMASNODO_H
#define UNTITLED1_BMASNODO_H

#include "../Estructuras/Producto.h"
#include <string>

class BMasNodo
{
public:
    string* claves;
    BMasNodo** hijo;
    Producto* data;
    BMasNodo* siguiente;

    int numClaves;
    int grado;
    bool esHoja;

    BMasNodo(int grado, bool esHoja);
    ~BMasNodo();
};

#endif //UNTITLED1_BMASNODO_H
