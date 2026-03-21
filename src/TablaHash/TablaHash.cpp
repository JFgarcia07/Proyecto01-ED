//
// Created by jfgarcianata on 16/03/26.
//

#include "TablaHash.h"
#include <iostream>

using namespace std;

TablaHash::TablaHash(int capacidad): capacidad(capacidad), size(0)
{
    tabla = new NodoHash*[capacidad];
    for (int i = 0; i < capacidad; i++) {
        tabla[i] = nullptr;
    }
}

TablaHash::~TablaHash() {
    for (int i = 0; i < capacidad; i++) {
        destruirCadena(tabla[i]);
    }
    delete[] tabla;
    tabla = nullptr;
    size = 0;
}

void destruirCadena(NodoHash* nodo)
{
    while (nodo != nullptr)
    {
        NodoHash* aux = nodo;
        nodo = nodo->siguiente;
        delete aux;
    }
}

//FUNCION HASH
int TablaHash::funcionHash(const string& llave) const
{
    unsigned long hash = 0;
    for (int i = 0; i < (int)llave.length(); i++)
    {
        hash = hash * 31 + llave[i];
    }
    return hash % capacidad;
}

//INSERCION
bool TablaHash::insertar(const Producto& producto)
{
    int indice = funcionHash(producto.codigoBarras);

    //DEBEMOS VERIFICAR SI YA EXISTE
    NodoHash* actual = tabla[indice];
    while (actual != nullptr)
    {
        if (actual->producto.codigoBarras == producto.codigoBarras)
        {
            return false;
        }
        actual = actual->siguiente;
    }

    NodoHash* nuevoNodo = new NodoHash(producto);
    if (nuevoNodo == nullptr) { return false;}

    nuevoNodo->siguiente = tabla[indice];
    tabla[indice] = nuevoNodo;
    size++;
    return true;
}

Producto* TablaHash::buscar(const string& codigoBarras) const
{
    int indice = funcionHash(codigoBarras);

    NodoHash* actual = tabla[indice];
    while (actual != nullptr)
    {
        if (actual->producto.codigoBarras == codigoBarras)
        {
            return &(actual->producto);
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool TablaHash::remover(const string& codigoBarras)
{
    int indice = funcionHash(codigoBarras);

    if (tabla[indice] == nullptr)
    {
        return false;
    }

    //CASO ESPECIAL: EL NODO A ELIMINAR ES EL PRIMERO EN LA CADENA
    if (tabla[indice]->producto.codigoBarras == codigoBarras)
    {
        NodoHash* aux = tabla[indice];
        tabla[indice] = tabla[indice]->siguiente;
        delete aux;
        size--;
        return true;
    }

    //BUSCAR EN EL RESTO DE LA CADENA
    NodoHash* actual = tabla[indice];
    while (actual->siguiente != nullptr)
    {
        if (actual->siguiente->producto.codigoBarras == codigoBarras)
        {
            NodoHash* aux = actual->siguiente;
            actual->siguiente = aux->siguiente;
            delete aux;
            size--;
            return true;
        }
        actual = actual->siguiente;
    }

    return false;
}

void TablaHash::mostrarEstadisticas() const
{
    int cubosUsados = 0;
    int cadenaMax = 0;
    int totalCadenas = 0;

    for (int i = 0; i < capacidad; i++)
    {
        if (tabla[i] != nullptr)
        {
            cubosUsados++;
            int cadenaLongitud = 0;
            NodoHash* actual = tabla[i];
            while (actual != nullptr)
            {
                cadenaLongitud++;
                actual = actual->siguiente;
            }
            if (cadenaLongitud > cadenaMax) { cadenaMax = cadenaLongitud; }
            totalCadenas += cadenaLongitud;
        }
    }

    cout << "+-----------------------------------------+" << endl;
    cout << "| ESTADISTICAS TABLA HASH                 |" << endl;
    cout << "+-----------------------------------------+" << endl;
    cout << "| Capacidad:       " << capacidad << endl;
    cout << "| Elementos:       " << size << endl;
    cout << "| Factor de carga: " << getLoadFactor() << endl;
    cout << "| Buckets usados:  " << cubosUsados << " / " << capacidad << endl;
    cout << "| Cadena mas larga:" << cadenaMax << endl;
    if (cubosUsados > 0) {
        cout << "| Cadena promedio: " << (double)totalCadenas / cubosUsados << endl;
    }
    cout << "+-----------------------------------------+" << endl;
}

void TablaHash::mostrar() const
{
    for (int i = 0; i < capacidad; i++)
    {
        NodoHash* actual = tabla[i];
        while (actual != nullptr)
        {
            actual->producto.mostrarProducto();
            actual = actual->siguiente;
        }
    }
    cout << "Total: " << size << " productos"<< endl;
}

int TablaHash::getSize() const
{
    return size;
}

int TablaHash::getCapacidad() const
{
    return capacidad;
}

//FACTO DE CARGA = ELEMENTOS / CAPACIDAD
double TablaHash::getLoadFactor() const
{
    return (double)size / (double)capacidad;
}

bool TablaHash::estaVacia() const
{
    return size == 0;
}
