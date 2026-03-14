//
// Created by jfgarcianata on 14/03/26.
//

#ifndef UNTITLED1_ARBOLAVL_H
#define UNTITLED1_ARBOLAVL_H

#include "AVLNodo.h"
#include <string>

class ArbolAVL
{
    private:
    ALVNodo* raiz;
    int size;

    //UTILIDADES INTERNAS
    int getAltura(AVLNodo* nodo) const;
    int getBalance(ALVNodo* nodo) const;
    int max(int a, int b) const;

    AVLNodo* rotacionDerecha(AVLNodo* y);
    AVLNodo* rotacionIzquierda(AVLNodo* x);

    //OPERACIONES RECURSIVAS
    AVLNodo* insertar(AVLNodo* nodo, const Producto& producto, bool& aprovado);
    AVLNodo* remover(AVLNodo* nodo, const string& nombre, bool& aprovado);
    AVLNodo* getNodoMinimo(AVLNodo* nodo) const;
    Producto* buscar(AVLNodo* nodo, const string& nombre) const;
    void inOrden(AVLNodo* nodo) const;
    void destruirArbol(AVLNodo* nodo);

    public:

};

#endif //UNTITLED1_ARBOLAVL_H