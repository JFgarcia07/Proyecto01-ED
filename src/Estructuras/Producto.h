//
// Created by jfgarcianata on 12/03/26.
//

#ifndef UNTITLED1_PRODUCTO_H
#define UNTITLED1_PRODUCTO_H
#include <string>

using namespace::std;

struct Producto
{
    string nombre;
    string codigoBarras;
    string categoria;
    string fechaExpiracion;
    string marca;
    double precio;
    int stock;

    Producto();
    Producto(const string& nombre, const string& codigoBarras, const string& categoria, const string& fechaExpiracion,
        const string& marca, double precio, int stock);

    void mostrarProducto() const;

    bool operator == (const Producto& obj) const;
    bool operator < (const Producto& obj) const;
    bool operator > (const Producto& obj) const;
};

#endif //UNTITLED1_PRODUCTO_H