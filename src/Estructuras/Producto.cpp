//
// Created by jfgarcianata on 12/03/26.
//
#include "Producto.h"
#include <iostream>

using namespace std;

Producto::Producto(): precio(0.0), stock(0){}

Producto::Producto(const string& nombre, const string& codigoBarras, const string& categoria, const string& fechaExpiracion,
    const string& marca, double precio, int stock): nombre(nombre), codigoBarras(codigoBarras), categoria(categoria),
    fechaExpiracion(fechaExpiracion), marca(marca), precio(precio), stock(stock){}

void Producto::mostrarProducto() const
{
    cout << "+-----------------------------------------+" << endl;
    cout << "| Nombre:    " << nombre << endl;
    cout << "| Codigo:    " << codigoBarras << endl;
    cout << "| Categoria: " << categoria << endl;
    cout << "| Caducidad: " << fechaExpiracion << endl;
    cout << "| Marca:     " << marca << endl;
    cout << "| Precio:    Q"<< precio << endl;
    cout << "| Stock:     " << stock << endl;
    cout << "+-----------------------------------------+" << endl;
}

bool Producto::operator>(const Producto& obj) const { return nombre > obj.nombre; }

bool Producto::operator<(const Producto& obj) const  { return nombre < obj.nombre; }

bool Producto::operator ==(const Producto& obj) const { return codigoBarras == obj.codigoBarras; }