//
// Created by jfgarcianata on 13/03/26.
//

#ifndef UNTITLED1_LISTAPRODUCTOSORDENADA_H
#define UNTITLED1_LISTAPRODUCTOSORDENADA_H
#include "Nodo.h"

class ListaProductosOrdenada
{
private:
    Nodo* cabeza;
    int size;

public:
    ListaProductosOrdenada();
    ~ListaProductosOrdenada();

    bool insertar(const Producto& producto);
    bool remover(const string& codigoBarra);

    Producto* buscarPorNombre(const string& nombre) const;
    Producto* buscarPorCodigo(const string& codigoBarra) const;

    void mostrarProductos() const;

    int getSize() const;
    bool estaVacia() const;
    Nodo* getCabeza() const;
};

#endif //UNTITLED1_LISTAPRODUCTOSORDENADA_H