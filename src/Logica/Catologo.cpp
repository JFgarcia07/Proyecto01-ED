//
// Created by jfgarcianata on 29/03/26.
//
#include "Catologo.h"
#include <iostream>

using namespace std;

Catalogo::Catalogo() : tablaHash(1009), arbolB(3), arbolBMas(3), totalProductos(0){}

Catalogo::~Catalogo() {}

bool Catalogo::agregarProducto(const Producto& producto)
{
    //BUSCAR SI HAY CODIGO DE BARRAS DUPLICADAS
    if (tablaHash.buscar(producto.codigoBarras) != nullptr)
    {
        return false;
    }

    //PASO 1 -- LISTA NO ORDENADA
    if (!listaProductos.insertar(producto))
    {
        return false;
    }

    //PASO 2 -- LISTA ORDENADA
    if (!listaProductosOrdenada.insertar(producto))
    {
        //HAY QUE HACER ROLLBACK DEL PASE 1
        listaProductos.remover(producto.codigoBarras);
        return false;
    }

    //PASO 3 -- AVL
    if (!arbolAVL.insertar(producto))
    {
        //ROLLBACK DE PASO 1 Y 2
        listaProductos.remover(producto.codigoBarras);
        listaProductosOrdenada.remover(producto.codigoBarras);
        return false;
    }

    //PASO 4 -- TABLA HASH
    if (!tablaHash.insertar(producto))
    {
        // ROLLBACK -- PASO 1,2 Y 3
        listaProductos.remover(producto.codigoBarras);
        listaProductosOrdenada.remover(producto.codigoBarras);
        arbolAVL.remover(producto.nombre);
        return false;
    }

    //PASO 5 -- ARBOL B
    if (!arbolB.insertar(producto))
    {
        //ROLLBACK -- PASO 1,2,3 Y4
        listaProductos.remover(producto.codigoBarras);
        listaProductosOrdenada.remover(producto.codigoBarras);
        arbolAVL.remover(producto.nombre);
        tablaHash.remover(producto.codigoBarras);
        return false;
    }

    //PASO 6 ARBOL B+ SIEMPRE RETORNA TRUE
    arbolBMas.insertar(producto);

    totalProductos++;
    return true;
}

bool Catalogo::removerProducto(const string& codigoBarras)
{
    //PRIMERO BUSCAR EL PRODUCTO PARA TENER SUS DATOS
    Producto* producto = tablaHash.buscar(codigoBarras);
    if (producto == nullptr)
    {
        cout << "Producto con codigo -" << codigoBarras << "- no encontrado" << endl;
        return false;
    }

    Producto copia = *producto;

    //ELIMINAR TODAS EN TODAS LAS ESTRUCTURAS
    listaProductos.remover(copia.codigoBarras);
    listaProductosOrdenada.remover(copia.codigoBarras);
    arbolAVL.remover(copia.nombre);
    tablaHash.remover(copia.codigoBarras);
    arbolB.remover(copia.fechaExpiracion);
    arbolBMas.remover(copia.categoria, copia.codigoBarras);

    totalProductos--;
    cout << "Producto " << copia.nombre  << " eliminado correctamente "<< endl;

    return true;
}

Producto* Catalogo::buscarPorNombre(const string& nombre) const
{
    return arbolAVL.buscar(nombre);
}

Producto* Catalogo::buscarPorCodigoBarras(const string& codigoBarras) const
{
    return tablaHash.buscar(codigoBarras);
}

void Catalogo::buscarPorCategoria(const string& categoria) const
{
    arbolBMas.buscarPorCategoria(categoria);
}

void Catalogo::buscarPorFechas(const string& fechaInicio, const string& fechaFin) const
{
    arbolB.rangoBusqueda(fechaInicio, fechaFin);
}

void Catalogo::listaPorNombres() const
{
    cout << "\n=== Productos ordenados por nombre ===" << endl;
    arbolAVL.inOrden();
}

void Catalogo::generarArchivosDot() const
{
    arbolAVL.generarDot("output/avl_tree.dot");
    arbolB.generarDot("output/avl_tree.dot");
    arbolBMas.generarDot("output/avl_tree.dot");
}

TablaHash& Catalogo::getTablaHash()
{
    return tablaHash;
}

int Catalogo::getTotal() const
{
    return totalProductos;
}

bool Catalogo::estaVacio() const
{
    return totalProductos == 0;
}
