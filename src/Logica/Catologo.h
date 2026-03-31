//
// Created by jfgarcianata on 29/03/26.
//

#ifndef UNTITLED1_CATOLOGO_H
#define UNTITLED1_CATOLOGO_H

#include "../Estructuras/ListaProductos.h"
#include "../Estructuras/ListaProductosOrdenada.h"
#include "../Arboles/ArbolAVL.h"
#include "../Arboles/ArbolB.h"
#include "../Arboles/ArbolBMas.h"
#include "../TablaHash/TablaHash.h"
#include <string>
using namespace std;

class Catalogo
{
    private:
    ListaProductos listaProductos;
    ListaProductosOrdenada listaProductosOrdenada;
    ArbolAVL arbolAVL;
    TablaHash tablaHash;
    ArbolB arbolB;
    ArbolBMas arbolBMas;

    int totalProductos;

    public:
    Catalogo();
    ~Catalogo();

    bool agregarProducto(const Producto& producto);
    bool removerProducto(const string& codigoBarras);

    Producto* buscarPorNombre(const string& nombre) const;
    Producto* buscarPorCodigoBarras(const string& codigoBarras) const;
    void buscarPorCategoria(const string& categoria) const;
    void buscarPorFechas(const string& fechaInicio, const string& fechaFin) const;
    TablaHash& getTablaHash();

    void listaPorNombres() const;
    void generarArchivosDot() const;

    int getTotal() const;
    bool estaVacio() const;
};

#endif //UNTITLED1_CATOLOGO_H
