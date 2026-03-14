//
// Created by jfgarcianata on 13/03/26.
//

#include "ListaProductos.h"
#include <iostream>

using namespace std;

ListaProductos::ListaProductos(): cabeza(nullptr), size(0){}

ListaProductos::~ListaProductos()
{
    Nodo* actual = cabeza;
    while (actual != nullptr)
    {
        Nodo* aux = actual;
        actual = actual->siguiente;
        delete aux;
    }

    cabeza = nullptr;
    size = 0;
}

bool ListaProductos::insertar(const Producto& producto)
{
    Nodo* nuevo = new Nodo(producto);

    if (nuevo == nullptr)
    {
        return false;
    }

    nuevo->siguiente = cabeza;
    cabeza = nuevo;
    size++;
    return true;
}

Producto* ListaProductos::obtenerPorNombre(const string& nombre) const
{
    Nodo* actual = cabeza;
    while (actual != nullptr)
    {
        if (actual->data.nombre == nombre)
        {
            return &(actual->data);
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

Producto* ListaProductos::obtenerPorBarra(const string& codigoBarra) const
{
    Nodo* actual = cabeza;
    while (actual != nullptr)
    {
        if (actual->data.codigoBarras == codigoBarra)
        {
            return &(actual->data);
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool ListaProductos::remover(const string& codigoBarra)
{
    if (cabeza == nullptr) {return false;}

    if (cabeza->data.codigoBarras == codigoBarra)
    {
        Nodo* aux = cabeza;
        cabeza = cabeza->siguiente;
        delete aux;
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

void ListaProductos::mostrarProductos() const
{
    Nodo* actual = cabeza;
    int contador = 1;
    while (actual != nullptr)
    {
        cout << "---Producto #" << contador++ << "---" << endl;
        actual->data,mostrarProductos();
        actual = actual->siguiente;
    }
    cout << "Hay un total de: " << size << " productos" <<endl;
}

int ListaProductos::getSize() const
{
    return size;
}

bool ListaProductos::estaVacia() const
{
    return cabeza == nullptr;
}

Nodo* ListaProductos::getCabeza() const
{
    return cabeza;
}