//
// Created by jfgarcianata on 30/03/26.
//

#include <iostream>
#include <string>
#include "Catologo.h"
#include "LectorCSV.h"

using namespace std;

void header()
{
    cout << "+=============================================+" << endl;
    cout << "|   CATALOGO DE PRODUCTOS - SUPERMERCADO      |" << endl;
    cout << "|   Estructuras de Datos - CUNOC 2026         |" << endl;
    cout << "+=============================================+" << endl;
}

void menu()
{
    cout << "\n+---------------------------------------------+" << endl;
    cout << "| MENU PRINCIPAL                               |" << endl;
    cout << "+----------------------------------------------+" << endl;
    cout << "| 1. Cargar catalogo desde CSV                 |" << endl;
    cout << "| 2. Agregar producto manualmente              |" << endl;
    cout << "| 3. Eliminar producto                         |" << endl;
    cout << "| 4. Buscar por nombre (AVL)                   |" << endl;
    cout << "| 5. Buscar por codigo de barra (Hash)         |" << endl;
    cout << "| 6. Buscar por categoria (B+)                 |" << endl;
    cout << "| 7. Buscar por rango de fechas (B)            |" << endl;
    cout << "| 8. Listar por nombre (AVL in-order)          |" << endl;
    cout << "| 9. Generar archivos DOT (Graphviz)           |" << endl;
    cout << "| 10. Estadisticas de la tabla hash            |" << endl;
    cout << "| 0. Salir                                     |" << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << "Opcion: ";
}

void cargarCSV(Catalogo& catalogo)
{
    string nombreArchivo;
    cout << "\nRuta del archivo CSV (ej: data/productos.csv): ";
    std::cin >> nombreArchivo;

    LectorCSV lector;
    int cargado = lector.cargar(nombreArchivo, catalogo);
    if (cargado > 0)
    {
        cout << "\nCatalogo tiene ahora " << catalogo.getTotal() << " productos" << endl;
    }
}

void agregarProducto(Catalogo& catalogo)
{
    Producto producto;

    cout << "\n--- Agregar nuevo producto ---" << endl;;
    cout << "Nombre: ";
    getline(cin, producto.nombre);

    cout << "Codigo de barras: ";
    getline(cin, producto.codigoBarras);

    cout << "Categoria: ";
    getline(cin, producto.categoria);

    cout << "Fecha de expiracion (YYYY - MM - DD): ";
    getline(cin, producto.fechaExpiracion);

    cout << "Marca: ";
    getline(cin, producto.marca);

    cout << "Precio: ";
    cin >> producto.precio;

    cout << "Stock: ";
    cin >> producto.stock;

    if (catalogo.agregarProducto(producto))
    {
        cout << "\nProcucto agegado correctamente" << endl;
        cout << "Total de productos: " << catalogo.getTotal() << endl;
    } else
    {
        cout << "\nError: no se pudo agregar. Posible duplicado de barcode o nombre." << endl;
    }
}

void removerProducto(Catalogo& catalogo)
{
    string codigoBarras;
    cout << "\nCodigo de barras del producto a eliminar" << endl;
    cin >> codigoBarras;

    if (catalogo.removerProducto(codigoBarras))
    {
        cout << "\nProcucto eliminado correctamente" << endl;
        cout << "\nError: no se pudo agregar. Posible duplicado de barcode o nombre." << endl;
    }
}

void buscarPorNombre()
{
    string nombre;
    cout << "\nNombre del producto";
    getline(cin, nombre);
}