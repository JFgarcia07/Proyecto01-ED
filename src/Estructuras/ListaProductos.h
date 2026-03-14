//
// Created by jfgarcianata on 12/03/26.
//

#ifndef UNTITLED1_LISTAPRODUCTOS_H
#define UNTITLED1_LISTAPRODUCTOS_H
#include "Producto.h"
#include "Nodo.h"

class ListaProductos
{
    private:
    Nodo* cabeza;
    int size;

    public:
    ListaProductos();
    ~ListaProductos();

    bool insertar(const Producto& producto);
    Producto* obtenerPorNombre(const string& nombre) const;
    Producto* obtenerPorBarra(const string& codigoBarra) const;
    bool remover(const string& codigoBarra);

    void mostrarProductos() const;

    int getSize() const;
    bool estaVacia() const;
    Nodo* getCabeza() const;
};

#endif //UNTITLED1_LISTAPRODUCTOS_H