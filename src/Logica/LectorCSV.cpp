//
// Created by jfgarcianata on 29/03/26.
//

#include "LectorCSV.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

LectorCSV::LectorCSV() {}
LectorCSV::~LectorCSV() {}

string LectorCSV::quitarComillas(const string& entrada) const
{
    string resultado = entrada;

    while (!resultado.empty() && resultado[0] == ' ')
    {
        resultado.erase(0, 1);
    }

    while (!resultado.empty() && resultado[resultado.size() - 1] == ' ')
    {
        resultado.erase(resultado.size() - 1);
    }

    if (resultado.size() >= 2 && resultado[0] == '"' && resultado[resultado.size() - 1] == '"')
    {
        resultado = resultado.substr(1, resultado.size() - 2);
    }
    return resultado;
}

bool LectorCSV::parsearLinea(const string& linea, Producto& producto)
{
    string entrada[7];
    int entradaIndex = 0;
    bool conComillas = false;
    string actual = "";

    for (int i = 0; i < (int)linea.size(); i++)
    {
        char c = linea[i];
        if (c == '"')
        {
            conComillas = !conComillas;
            actual = actual + c;
        } else if (c == ',' && !conComillas)
        {
            if (entradaIndex >= 7) {return false;}
            entrada[entradaIndex++] = actual;
            actual = "";
        } else
        {
            actual = actual + c;
        }
    }

    if (entradaIndex < 7)
    {
        entrada[entradaIndex++] = actual;
    }

    if (entradaIndex != 7) { return false;}

    producto.nombre = quitarComillas(entrada[0]);
    producto.codigoBarras = quitarComillas(entrada[1]);
    producto.categoria = quitarComillas(entrada[2]);
    producto.fechaExpiracion = quitarComillas(entrada[3]);
    producto.marca = quitarComillas(entrada[4]);

    string precioStr = quitarComillas(entrada[5]);
    try
    {
        producto.precio = stod(precioStr);
    } catch (...)
    {
        return false;
    }

    string stockStr = quitarComillas(entrada[6]);
    try
    {
        producto.stock = stoi(stockStr);
    } catch (...)
    {
        return false;
    }

    return true;
}

bool LectorCSV::validar(const Producto& producto, int numLinea, string& error)
{
    if (producto.nombre.empty())
    {
        error = "Linea " + to_string(numLinea) + " : nombre vacio";
        return false;
    }
    if (producto.codigoBarras.empty())
    {
        error = "Linea " + to_string(numLinea) + ": codigo de barras vacio";
        return false;
    }
    if (producto.categoria.empty())
    {
        error = "Linea " + to_string(numLinea) + ": categoria vacia";
        return false;
    }
    if (producto.fechaExpiracion.empty() || producto.fechaExpiracion.size() != 10)
    {
        error = "Linea " + to_string(numLinea) + " fecha invalida " + producto.fechaExpiracion;
        return false;
    }
    if (producto.precio < 0)
    {
        error = "Linea " + to_string(numLinea) + " : precio negativo";
        return false;
    }
    if (producto.stock < 0)
    {
        error = "Linea " + to_string(numLinea) + " : stock negativo";
        return false;
    }
    return true;
}

int LectorCSV::cargar(const string& nombreArchivo, Catalogo& catalogo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "Error: no se puede abrir el archivo '" << nombreArchivo << "'" << endl;
        return -1;
    }

    system("mkdir -p logs");
    ofstream errorArchivo("logs/errores.log");
    if (!errorArchivo.is_open())
    {
        cout << "Advertencia: no se puede crear errors.log" << endl;
    }

    string linea;
    int liniaNum = 0;
    int cargado = 0;
    int errores = 0;
    int duplicados = 0;

    if (getline(archivo, linea))
    {
        liniaNum++;
        if (!linea.empty() && linea[linea.size() - 1] == '\r')
        {
            linea.erase(linea.size() - 1);
        }
    }

    while (getline(archivo, linea))
    {
        liniaNum++;

        if (!linea.empty() && linea[linea.size() - 1] == '\r')
        {
            linea.erase(linea.size() - 1);
        }

        if (linea.empty()) { continue;}

        Producto producto;

        if (!parsearLinea(linea, producto))
        {
            errores++;
            if (errorArchivo.is_open())
            {
                errorArchivo << "Linea " << liniaNum << ": formato malformado - " << linea << endl;
            }
            continue;
        }

        //VALIDAMOS LOS CAMPOS
        string mensajeErr;
        if (!validar(producto, liniaNum, mensajeErr))
        {
            errores++;
            if (errorArchivo.is_open())
            {
                errorArchivo << mensajeErr << endl;
            }
            continue;
        }

        //INSERTAR EN EL CATALOGO
        if (catalogo.agregarProducto(producto))
        {
            cargado++;
        } else
        {
            duplicados++;
            if (errorArchivo.is_open())
            {
                errorArchivo << "Linea " << liniaNum << ": barcode duplicado '"
                         << producto.codigoBarras << "'" << endl;
            }
        }
    }

    archivo.close();
    if (errorArchivo.is_open()) {errorArchivo.close();}

    cout << "===== ARCHIVO CARGADO CORRECTAMENTE =====" << endl;
    cout << "Archivo: " << nombreArchivo << endl;
    cout << "Lineas: " << liniaNum << endl;
    cout << "Cargados: " << cargado << endl;
    cout << "Duplicados: " << duplicados << endl;
    cout << "Errores: " << errores << endl;
    if (errores > 0 || duplicados > 0)
    {
        cout << "Ver detalles en: logs/errores.log" << endl;
    }

    return cargado;
}
