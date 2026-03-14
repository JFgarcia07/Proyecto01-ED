//
// Created by jfgarcianata on 14/03/26.
//

#include "ListaProductosOrdenada.h"
#include <iostream>
using namespace std;

ListaProductosOrdenada::ListaProductosOrdenada(): cabeza(nullptr), size(0){}

ListaProductosOrdenada::~ListaProductosOrdenada()
{
    Nodo* actual = cabeza;
    while (actual != nullptr)
    {
        Nodo* aux = actual;
        cabeza = actual->siguiente;
        delete aux;
    }
    cabeza = nullptr;
    size = 0;
}


bool ListaProductosOrdenada::insertar(const Producto& producto)
{
    Nodo* nuevo = new Nodo(producto);
    if (nuevo == nullptr){ return false;}

    if (cabeza == nullptr || producto.nombre < cabeza->data.nombre)
    {
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        size++;
        return true;
    }

    Nodo* actual = cabeza;
    while (actual->siguiente != nullptr && actual->siguiente->data.nombre < producto.nombre)
    {
        actual = actual->siguiente;
    }

    nuevo->siguiente = cabeza->siguiente;
    actual->siguiente = nuevo;
    size++;
    return true;
}

Producto* ListaProductosOrdenada::buscarPorNombre(const string& nombre) const
{
    Nodo* actual = cabeza;
    while (actual != nullptr)
    {
        if (actual->data.nombre == nombre)
        {
            return &(actual->data);
        }

        if (actual->data.nombre < nombre)
        {
            return nullptr;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

Producto* ListaProductosOrdenada::buscarPorCodigo(const string& codigoBarra) const
{
    Nodo* actual = cabeza;
    while (actual != nullptr)
    {
        if (actual->data.codigoBarras ==  codigoBarra)
        {
            return &(actual->data);
        }
        actual  = actual->siguiente;
    }
    return nullptr;
}

bool ListaProductosOrdenada::remover(const string& codigoBarra)
{
    if (cabeza == nullptr)
    {
        return false;
    }

    if (cabeza->data.codigoBarras == codigoBarra)
    {
        Nodo* aux = cabeza;
        cabeza = cabeza->siguiente;
        size--;
        return true;
    }

    Nodo* actual = cabeza;
    while (actual->siguiente != nullptr)
    {
        if (actual->siguiente->data.codigoBarras == codigoBarra)
        {
            Nodo* aux = actual->siguiente;
            actual->siguiente = aux->siguiente;
            delete aux;
            size--;
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

void ListaProductosOrdenada::mostrarProductos() const
{
    Nodo* actual = cabeza;
    int contador = 1;
    while (actual != nullptr)
    {
        cout << "---Producto #" << contador << "---" << endl;
        actual->data.mostrarProducto();
        actual = actual->siguiente;
    }
    cout << "Hay un total de " << size << "productos (Ordenados por nombre)" << endl;
}

int ListaProductosOrdenada::getSize() const
{
    return size;
}

bool ListaProductosOrdenada::estaVacia() const
{
    return cabeza == nullptr;
}

Nodo* ListaProductosOrdenada::getCabeza() const
{
    return cabeza;
}
