//
// Created by jfgarcianata on 30/03/26.
//

#include <iostream>
#include <string>
#include "MotorDelSistema.h"

#include <limits>

#include "Catologo.h"
#include "LectorCSV.h"

using namespace std;

void MotorDelSistema::header()
{
    cout << "+=============================================+" << endl;
    cout << "|   CATALOGO DE PRODUCTOS - SUPERMERCADO      |" << endl;
    cout << "|   Estructuras de Datos - CUNOC 2026         |" << endl;
    cout << "+=============================================+" << endl;
}

void MotorDelSistema::menu()
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

void MotorDelSistema::cargarCSV(Catalogo& catalogo)
{
    string nombreArchivo;
    cin.ignore();
    cout << "\nRuta del archivo CSV (ej: data/productos.csv): ";
    getline(cin, nombreArchivo);

    LectorCSV lector;
    int cargado = lector.cargar(nombreArchivo, catalogo);
    if (cargado > 0)
    {
        cout << "\nCatalogo tiene ahora " << catalogo.getTotal() << " productos" << endl;
    }
}

void MotorDelSistema::agregarProducto(Catalogo& catalogo)
{
    Producto producto;

    cout << "\n--- Agregar nuevo producto ---" << endl;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

    bool precioValido = false;
    while (!precioValido) {
        cout << "Precio: ";
        string inputPrecio;
        cin >> inputPrecio;
        try {
            size_t pos;
            producto.precio = stod(inputPrecio, &pos);
            if (pos != inputPrecio.size()) throw invalid_argument("caracteres extra");
            if (producto.precio < 0) throw invalid_argument("negativo");
            precioValido = true;
        } catch (...) {
            cout << "Error: ingrese un numero valido para el precio (ej: 12.50)" << endl;
        }
    }

    bool stockValido = false;
    while (!stockValido) {
        cout << "Stock: ";
        string inputStock;
        cin >> inputStock;
        try {
            size_t pos;
            long val = stol(inputStock, &pos);
            if (pos != inputStock.size()) throw invalid_argument("caracteres extra");
            if (val < 0) throw invalid_argument("negativo");
            producto.stock = static_cast<int>(val);
            stockValido = true;
        } catch (...) {
            cout << "Error: ingrese un numero entero valido para el stock (ej: 10)" << endl;
        }
    }

    if (catalogo.agregarProducto(producto))
    {
        cout << "\nProcucto agegado correctamente" << endl;
        cout << "Total de productos: " << catalogo.getTotal() << endl;
    } else
    {
        cout << "\nError: no se pudo agregar. Posible duplicado de barcode o nombre." << endl;
    }
}

void MotorDelSistema::removerProducto(Catalogo& catalogo)
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

void MotorDelSistema::buscarPorNombre(Catalogo& catalogo)
{
    string nombre;
    cout << "\nNombre del producto: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, nombre);

    Producto* producto = catalogo.buscarPorNombre(nombre);
    if (producto)
    {
        cout << "\nProducto encontrado " << endl;
        producto->mostrarProducto();
    } else
    {
        cout << "\nProducto '" << nombre << "' no encontrado." << std::endl;
    }
}

void MotorDelSistema::buscarPorCodigoBarras(Catalogo& catalogo)
{
    string codigoBarras;
    cout << "\nCodigo de barras del producto: ";
    //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin >> codigoBarras;

    Producto* producto = catalogo.buscarPorCodigoBarras(codigoBarras);
    if (producto)
    {
        cout << "\nProducto encontrado " << endl;
        producto->mostrarProducto();
    } else
    {
        cout << "\nProducto con codigo'" << codigoBarras << "' no encontrado." << std::endl;
    }
}

void MotorDelSistema::buscarPorCategoria(Catalogo& catalogo)
{
    string categoria;
    cout << "\nCodigo de categoria";
    cin >> categoria;

    cout << endl;
    catalogo.buscarPorCategoria(categoria);
}

void MotorDelSistema::buscarPorRangoFecha(Catalogo& catalogo)
{
    string fechaInicio, fechaFin;
    cout << "\nFecha de inicio (YYYY - MM - DD): ";
    cin >> fechaInicio;
    cout << "\nFecha final (YYYY - MM - DD): ";
    cin >> fechaFin;

    cout << endl;
    catalogo.buscarPorFechas(fechaInicio, fechaFin);
}

void MotorDelSistema::generarDot(Catalogo& catalogo)
{
    if (catalogo.estaVacio())
    {
        cout << "\nEl catalogo esta vacio. Cargue datos primero." << endl;
        return;
    }

    system("mkdir -p output");

    catalogo.generarArchivosDot();

    cout << "\nArchivos generados en output/:" << endl;
    cout << "Archivos .dot" << endl;
    cout << "  - avl_tree.dot" << endl;
    cout << "  - b_tree.dot" << endl;
    cout << "  - bplus_tree.dot" << endl;

    cout << "Archivos .png" << endl;
    cout << "  - avl_tree.png" << endl;
    cout << "  - b_tree.png" << endl;
    cout << "  - bplus_tree.png" << endl;
}

void MotorDelSistema::mostrarDatosHash(Catalogo& catalogo)
{
    if (catalogo.estaVacio()) {
        cout << "\nEl catalogo esta vacio." << endl;
        return;
    }
    cout << std::endl;
    catalogo.getTablaHash().mostrarEstadisticas();
}

void MotorDelSistema::motorDelSistema()
{
    Catalogo catalogo;
    int opcion = -1;

    header();

    while (opcion != 0)
    {
        menu();
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                cargarCSV(catalogo);
                break;
            case 2:
                agregarProducto(catalogo);
                break;
            case 3:
                removerProducto(catalogo);
                break;
            case 4:
                buscarPorNombre(catalogo);
                break;
            case 5:
                buscarPorCodigoBarras(catalogo);
                break;
            case 6:
                buscarPorCategoria(catalogo);
                break;
            case 7:
                buscarPorRangoFecha(catalogo);
                break;
            case 8:
                catalogo.listaPorNombres();
                break;
            case 9:
                generarDot(catalogo);
                break;
            case 10:
                mostrarDatosHash(catalogo);
                break;
            case 0:
                cout << "\nSaliendo del programa..." << endl;
                break;
            default:
                cout << "\nOpcion no valida." << endl;
                break;
        }
    }
}