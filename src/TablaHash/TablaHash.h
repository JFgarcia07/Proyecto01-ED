//
// Created by jfgarcianata on 16/03/26.
//

#ifndef UNTITLED1_TABLAHASH_H
#define UNTITLED1_TABLAHASH_H

#include "NodoHash.h"
#include <string>
using namespace std;

class TablaHash
{
private:
    NodoHash** tabla;
    int capacidad;
    int size;

    int funcionHash(const string& llave) const;
    void destruirCadena(NodoHash* nodo);

public:
    TablaHash(int capacidad = 1009);
    ~TablaHash();

    bool insertar(const Producto& producto);
    bool remover(const string& codigoBarras);
    Producto* buscar(const string& codigoBarras) const;

    void mostrarEstadisticas() const;
    void mostrar() const;

    int getSize() const;
    int getCapacidad() const;
    double getLoadFactor() const;
    bool estaVacia() const;
};

#endif //UNTITLED1_TABLAHASH_H