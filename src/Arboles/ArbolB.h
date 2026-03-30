//
// Created by jfgarcianata on 20/03/26.
//

#ifndef UNTITLED1_ARBOLB_H
#define UNTITLED1_ARBOLB_H

#include "BNodo.h"
#include <string>

class ArbolB
{
private:
    BNodo* raiz;
    int grado;
    int size;

    void separarHijos(BNodo* padre, int i, BNodo* hijo);
    void insertarNoCompleto(BNodo* nodo, const Producto& producto);

    Producto* buscarPriv(BNodo* nodo, const string& fecha) const;

    void rangoBusquedaPriv(BNodo* nodo, const string& fechaInicio, const string& fechaFinal, int& contador) const;

    void removerDelNodo(BNodo* nodo, const string& fecha);
    void removerDeHoja(BNodo* nodo, int indice);
    void removerDeInterno(BNodo* nodo, int indice);
    Producto getPredecesor(BNodo* nodo, int indice);
    Producto getSucesor(BNodo* nodo, int indice);
    void llenar(BNodo* nodo, int indice);
    void prestarPrevio(BNodo* nodo, int indice);
    void prestarSiguiente(BNodo* nodo, int indice);
    void merge(BNodo* nodo, int indice);

    int encontrarClave(BNodo* nodo, const string& fecha) const;

    void generarDotHelper(BNodo* nodo,  string& dot, int& nodoId) const;

    void destruirArbol(BNodo* nodo);

    public:
    ArbolB(int grado = 3);
    ~ArbolB();

    bool insertar(const Producto& producto);

    Producto* buscar(const string& fecha) const;

    void rangoBusqueda(const string& fechaInicio, const string& fechaFinal) const;

    bool remover(const string& fecha);

    void generarDot(const string& nombreArchivo) const;

    int getSize() const;
    bool estaVacio() const;
};

#endif //UNTITLED1_ARBOLB_H