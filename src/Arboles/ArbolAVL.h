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
    AVLNodo* raiz;
    int size;

    //UTILIDADES INTERNAS
    int getAltura(AVLNodo* nodo) const;
    int getBalance(AVLNodo* nodo) const;
    int max(int a, int b) const;

    AVLNodo* rotacionDerecha(AVLNodo* y);
    AVLNodo* rotacionIzquierda(AVLNodo* x);

    //OPERACIONES RECURSIVAS
    AVLNodo* insertarPriv(AVLNodo* nodo, const Producto& producto, bool& aprovado);
    AVLNodo* removerPriv(AVLNodo* nodo, const string& nombre, bool& aprovado);
    AVLNodo* getNodoMinimoPriv(AVLNodo* nodo) const;
    Producto* buscarPriv(AVLNodo* nodo, const string& nombre) const;
    void inOrdenPriv(AVLNodo* nodo) const;
    void destruirArbol(AVLNodo* nodo);

    void generarDotPriv(AVLNodo* nodo, string& dot) const;

    public:
    ArbolAVL();
    ~ArbolAVL();

    bool insertar(const Producto& producto);
    bool remover(const string& nombre);

    Producto* buscar(const string& nombre) const;

    void inOrden() const;

    void generarDot(const string& nombre) const;

    int getSize() const;
    bool estaVacio() const;
};

#endif //UNTITLED1_ARBOLAVL_H