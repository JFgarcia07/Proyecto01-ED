//
// Created by jfgarcianata on 26/03/26.
//

#ifndef UNTITLED1_ARBOLBMAS_H
#define UNTITLED1_ARBOLBMAS_H

#include "BMasNodo.h"
#include <string>

using namespace std;

class ArbolBMas
{
    private:
    BMasNodo* raiz;
    int grado;
    int size;

    void separarHijoPriv(BMasNodo* padre, int i, BMasNodo* hijo);
    void insertarNoLlenoPriv(BMasNodo* nodo, const Producto& producto);

    void removerDelNodoPriv(BMasNodo* nodo, const string& categoria, const string& codigoBarras);
    void removerDeHojaPriv(BMasNodo* nodo, int indice);
    int encontrarClave(BMasNodo* nodo, const string& categoria) const;
    void llenar(BMasNodo* nodo, int indice);
    void prestarPrevio(BMasNodo* nodo, int indice);
    void prestarSiguiente(BMasNodo* nodo, int indice);
    void merge(BMasNodo* nodo, int indice);
    void actualizarClavePadre(BMasNodo* nodo, const string& claveAntigua, const string& claveNueva);

   void generarDotHelper(BMasNodo* nodo, string& dot, int& nodoId) const;

    void destruirArbol(BMasNodo* nodo);

    public:
    ArbolBMas(int grado = 3);
    ~ArbolBMas();

    bool insertar(const Producto& producto);

    void buscarPorCategoria(const string& categoria) const;

    bool remover(const string& categoria, const string& codigoBarras);

    void listarCategorias() const;

    void generarDot(const string& nombreDeArchivo) const;

    int getSize() const;
    bool estaVacio() const;
};

#endif //UNTITLED1_ARBOLBMAS_H
