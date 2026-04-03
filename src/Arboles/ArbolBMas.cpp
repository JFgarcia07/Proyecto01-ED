//
// Created by jfgarcianata on 27/03/26.
//

#include "ArbolBMas.h"

#include <atomic>
#include <iostream>
#include <fstream>

#include "BNodo.h"

using namespace std;

ArbolBMas::ArbolBMas(int grado) : raiz(nullptr), grado(grado), size(0){}

ArbolBMas::~ArbolBMas()
{
    destruirArbol(raiz);
    raiz = nullptr;
    size = 0;
}

void ArbolBMas::destruirArbol(BMasNodo* nodo)
{
    if(nodo == nullptr){return;}
    if(!nodo->esHoja)
    {
        for(int i = 0; i <= nodo->numClaves ; i++)
        {
            destruirArbol(nodo->hijo[i]);
        }
    }
    delete nodo;
}

int ArbolBMas::encontrarClave(BMasNodo* nodo, const string& categoria) const
{
    int indice = 0;

    while(indice < nodo->numClaves && nodo->claves[indice] < categoria)
    {
        indice++;
    }
    return indice;
}

bool ArbolBMas::insertar(const Producto& producto)
{
    if(raiz == nullptr)
    {
        raiz = new BMasNodo(grado, true);
        raiz->claves[0] = producto.categoria;
        raiz->data[0] = producto;
        raiz->numClaves = 1;
        size++;
        return true;
    }

    //SI LA RAIZ ESTA LLENA, CREAR UNA NUEVA RAIZ Y DIVIDIR
    if(raiz->numClaves == 2*grado -1)
    {
        BMasNodo* nuevaRaiz = new BMasNodo(grado, false);
        nuevaRaiz->hijo[0] = raiz;
        separarHijoPriv(nuevaRaiz, 0, raiz);

        //HAY QUE DECIDIR EN CUAL HIJO INSERTAR
        int i = 0;
        if (nuevaRaiz->claves[0] < producto.categoria)
        {
            i++;
        }
        insertarNoLlenoPriv(nuevaRaiz->hijo[i], producto);
        raiz = nuevaRaiz;
    } else
    {
        insertarNoLlenoPriv(raiz, producto);
    }

    size++;
    return true;
}

//DIVIDIR UN HIJO LLENO DEL NODO PADRE
void ArbolBMas::separarHijoPriv(BMasNodo* padre, int i, BMasNodo* hijo)
{
    BMasNodo* nuevoNodo = new BMasNodo(hijo->grado, hijo->esHoja);

    if (hijo->esHoja)
    {
        //HOJA: COPIAR LA MITAD DERECHA AL NUEVO NODO
        nuevoNodo->numClaves = hijo->numClaves - (grado - 1);
        for (int j = 0; j < nuevoNodo->numClaves; j++)
        {
            nuevoNodo->claves[j] = hijo->claves[j + grado - 1];
            nuevoNodo->data[j] = hijo->data[j + grado - 1];
        }
        hijo->numClaves = grado - 1;

        //ENLAZA HOJAS
        nuevoNodo->siguiente = hijo->siguiente;
        hijo->siguiente = nuevoNodo;

        //COPIAR LA PRIMERA CLAVE DEL NUEVO NODO AL PADRE -- HACER ESPACIO EN EL PADRE
        for (int j = padre->numClaves; j > i; j--)
        {
            padre->claves[j] = padre->claves[j - 1];
            padre->hijo[j + 1] = padre->hijo[j];
        }
        padre->claves[i] = nuevoNodo->claves[0];
        padre->hijo[i + 1] = nuevoNodo;
        padre->numClaves++;
    } else
    {
        //LA CLAVE DE EN MEDIO SUBE
        nuevoNodo->numClaves = grado - 1;
        for (int j = 0; j < grado - 1; j++)
        {
            nuevoNodo->claves[j] = hijo->claves[j + grado];
        }

        for (int j = 0; j < grado; j++)
        {
            nuevoNodo->hijo[j] = hijo->hijo[j + grado];
        }
        hijo->numClaves =  grado - 1;

        //HACE ESPACIO PARA EL PADRE
        for (int j = padre->numClaves; j > i; j--)
        {
            padre->claves[j] = padre->claves[j - 1];
            padre->hijo[j + 1] = padre->hijo[j];
        }
        //LA CLAVE DE MEDIO SUBE AL PADRE
        padre->claves[i] = hijo->claves[grado - 1];
        padre->hijo[i + 1] = nuevoNodo;
        padre->numClaves++;
    }
}

void ArbolBMas::insertarNoLlenoPriv(BMasNodo* nodo, const Producto& producto)
{
    int i = nodo->numClaves - 1;

    if (nodo->esHoja)
    {
        //DEZPLAZAR PARA HACER ESPACIO Y LUEGO INSERTAR ORDENADAMENTE
        while (i >= 0 && nodo->claves[i] > producto.categoria)
        {
            nodo->claves[i + 1] = nodo->claves[i];
            nodo->data[i + 1] = nodo->data[i];
            i--;
        }
        nodo->claves[i + 1] = producto.categoria;
        nodo->data[i + 1] = producto;
        nodo->numClaves++;
    } else
    {
        //ENCONTAR DONDE DEBE DE IR
        while (i>=0 && nodo->claves[i] > producto.categoria)
        {
            i--;
        }
        i++;

        //SI EL HIJO ESTA LLENO, HAY QUE DIVIDIRLO
        if (nodo->hijo[i]->numClaves == 2*grado - 1)
        {
            separarHijoPriv(nodo, i, nodo->hijo[i]);
            if (nodo->claves[i] < producto.categoria)
            {
                i++;
            }
        }
        insertarNoLlenoPriv(nodo->hijo[i], producto);
    }
}

void ArbolBMas::buscarPorCategoria(const string& categoria) const
{
    if (raiz == nullptr)
    {
        cout << "Arbol b+ vacio";
        return;
    }

    //NAVEGAR HASTA LA HOJA CORRESPONDIENTE
    BMasNodo* actual = raiz;
    while (!actual->esHoja)
    {
        int i = encontrarClave(actual, categoria);
        actual = actual->hijo[i];
    }

    int contador = 0;
    cout << "Productos en la categoria " << categoria << ": "<< endl;

    while (actual != nullptr)
    {
        bool encontrado = false;
        for (int i = 0; i < actual->numClaves; i++)
        {
            if (actual->claves[i] == categoria)
            {
                actual->data[i].mostrarProducto();
                contador++;
                encontrado = true;
            } else if (actual->claves[i] > categoria)
            {
                cout << "Total de productos encontrados: " << contador << endl;
                return;
            }
        }

        if (!encontrado && contador > 0) {
            break;
        }
        actual = actual->siguiente;
    }

    cout << "Total de productos encontrados: " << contador << endl;
}

bool ArbolBMas::remover(const string& categoria, const string& codigoBarras)
{
    if (raiz == nullptr){return false;}

    removerDelNodoPriv(raiz, categoria, codigoBarras);

    //SI LA RAIZ QUEDA VACIA
    if (raiz->numClaves == 0)
    {
        BMasNodo* raizVieja = raiz;
        if (raiz->esHoja)
        {
            raiz = nullptr;
        } else
        {
            raiz = raiz->hijo[0];
            raizVieja->hijo[0] = nullptr;
        }
        delete raizVieja;
    }

    size--;
    return true;
}

void ArbolBMas::removerDelNodoPriv(BMasNodo* nodo, const string& categoria, const string& codigoBarras)
{
    if (nodo->esHoja)
    {
        //BUSCAR EL PRODUCTO CON LA CATEGORIA Y EL CODIGO DE BARRAS
        for (int i = 0; i < nodo->numClaves; i++)
        {
            if (nodo->claves[i] == categoria && nodo->data[i].codigoBarras == codigoBarras)
            {
                removerDeHojaPriv(nodo, i);
                return;
            }
        }
        return;
    }

    int indice = encontrarClave(nodo, categoria);

    if (indice < nodo->numClaves && nodo->claves[indice] == categoria)
    {
        //ASEGURAR QUE EL HIJO TENGA SUFICIENTES CLAVES
        if (nodo->hijo[indice]->numClaves < grado)
        {
            llenar(nodo, indice);
        }

        //DESPUES DE LLANAR RECALCULAR
        indice = encontrarClave(nodo, categoria);
    }

    if (nodo->hijo[indice]->numClaves < grado)
    {
        llenar(nodo, indice);
    }

    indice = encontrarClave(nodo, categoria);
    if (indice > nodo->numClaves)
    {
        indice = nodo->numClaves;
    }

    removerDelNodoPriv(nodo->hijo[indice], categoria, codigoBarras);

    if (indice > 0 && nodo->hijo[indice]->esHoja && nodo->hijo[indice]->numClaves > 0)
    {
        nodo->claves[indice - 1] = nodo->hijo[indice]->claves[0];
    }
}

void ArbolBMas::removerDeHojaPriv(BMasNodo* nodo, int indice)
{
    for (int i = indice + 1; i < nodo->numClaves; i++)
    {
        nodo->claves[i -1] = nodo->claves[i];
        nodo->data[i - 1] = nodo->data[i];
    }
    nodo->numClaves--;
}

void ArbolBMas::llenar(BMasNodo* nodo, int indice)
{
    if (indice != 0 && nodo->hijo[indice - 1]->numClaves >= grado)
    {
        prestarPrevio(nodo, indice);
    } else if (indice != nodo->numClaves && nodo->hijo[indice + 1]->numClaves >= grado)
    {
        prestarSiguiente(nodo, indice);
    } else
    {
        if (indice != nodo->numClaves)
        {
            merge(nodo, indice);
        } else
        {
            merge(nodo, indice - 1);
        }
    }
}

void ArbolBMas::prestarPrevio(BMasNodo* nodo, int indice)
{
    BMasNodo* hijo = nodo->hijo[indice];
    BMasNodo* hermano =  nodo->hijo[indice - 1];

    if (hijo->esHoja)
    {
        //DESPLAZAR LOS DATOS A LA DERECHA
        for (int i = hijo->numClaves - 1; i >= 0; i--)
        {
            hijo->claves[i + 1] = hijo->claves[i];
            hijo->data[i + 1] = hijo->data[i];
        }
        //MOVER EL ULTIMO DATO DEL HERMANO A L HIJO
        hijo->claves[0] = hermano->claves[hermano->numClaves - 1];
        hijo->data[0] = hermano->data[hermano->numClaves - 1];

        nodo->claves[indice - 1] = hijo->claves[0];
    } else
    {
        for (int i = hijo->numClaves - 1; i >= 0; i--)
        {
            hijo->hijo[i + 1] = hijo->hijo[i];
        }
        for (int i = hijo->numClaves - 1; i >= 0; i--)
        {
            hijo->hijo[i + 1] = hijo->hijo[i];
        }
        hijo->claves[0] = nodo->claves[indice -1];
        hijo->hijo[0] = hermano->hijo[hermano->numClaves];
        nodo->claves[indice - 1] = hermano->claves[hermano->numClaves - 1];
    }

    hijo->numClaves++;
    hermano->numClaves--;
}

void ArbolBMas::prestarSiguiente(BMasNodo* nodo, int indice)
{
    BMasNodo* hijo = nodo->hijo[indice];
    BMasNodo* hermano =  nodo->hijo[indice + 1];

    if (hijo->esHoja)
    {
        //MOVER PRIMER DATO DEL HERMANO AL FINAL DEL HIJO
        hijo->claves[hijo->numClaves] = hermano->claves[0];
        hijo->data[hijo->numClaves] = hermano->data[0];

        //DESPLAZAR DATOS DEL HERMANO A LA IZQ
        for (int i = 1; i < hermano->numClaves; i++)
        {
            hermano->claves[i - 1] = hermano->claves[i];
            hermano->data[i - 1] = hermano->data[i];
        }
        nodo->claves[indice] = hermano->claves[0];
    } else
    {
        hijo->claves[hijo->numClaves] = nodo->claves[indice];
        hijo->hijo[hijo->numClaves + 1] = hermano->hijo[0];
        nodo->claves[indice] = hermano->claves[0];
        for (int i = 1; i < hermano->numClaves; i++)
        {
            hermano->claves[i - 1] = hermano->claves[i];
        }
        for (int i = 1; i <= hermano->numClaves; i++)
        {
            hermano->hijo[i - 1] = hermano->hijo[i];
        }
    }
    hijo->numClaves++;
    hermano->numClaves--;
}

void ArbolBMas::merge(BMasNodo* nodo, int indice)
{
    BMasNodo* hijo = nodo->hijo[indice];
    BMasNodo* hermano =  nodo->hijo[indice + 1];

    if (hijo->esHoja)
    {
        //COPIAR DATOS DEL HERMAMNO
        for (int i = 0; i < hermano->numClaves; i++)
        {
            hijo->claves[hijo->numClaves + i] = hermano->claves[i];
            hijo->data[hijo->numClaves + i] = hermano->data[i];
        }
        hijo->numClaves += hermano->numClaves;
        hijo->siguiente = hermano->siguiente;
    } else
    {
        //LA CLAVE DEL PADRE BAJA COMO SEPARADAOR
        hijo->claves[hijo->numClaves] = nodo->claves[indice];
        hijo->numClaves++;
        //COPIAR CLAVES E HIJOS DEL HERMANO
        for (int i = 0; i < hermano->numClaves; i++)
        {
            hijo->claves[hijo->numClaves + i] = hermano->claves[i];
        }
        for (int i = 1; i<= hermano->numClaves; i++)
        {
            hijo->hijo[hijo->numClaves + i] = hermano->hijo[i];
        }
        hijo->numClaves += hermano->numClaves;

        for (int i = 0; i <= hermano->numClaves; i++)
        {
            hermano->hijo[i] = nullptr;
        }
    }

    //MOCER LAS CLAVES E HIJOS DEL PADRE A LA IZQ
    for (int i = indice + 1; i < nodo->numClaves; i++)
    {
        nodo->claves[i - 1] = nodo->claves[i];
    }
    for (int i = indice + 2; i <= nodo->numClaves; i++)
    {
        nodo->hijo[i - 1] = nodo->hijo[i];
    }
    nodo->numClaves--;

    delete hermano;
}

void ArbolBMas::listarCategorias() const
{
    if (raiz == nullptr)
    {
        cout << "ARBOL B+ VACIO" << endl;
        return;
    }

    BMasNodo* actual = raiz;
    while (!actual->esHoja)
    {
        actual = actual->hijo[0];
    }

    int contador = 0;
    while (actual != nullptr)
    {
        for (int i = 0; i < actual->numClaves; i++)
        {
            cout << "[" << actual->claves[i] << "] ";
            cout << actual->data[i].nombre << endl;
            contador++;
        }
        actual = actual->siguiente;
    }
    cout << "Total: " << contador << " productos"<< endl;
}

void ArbolBMas::generarDot(const string& nombreDeArchivo) const
{
    string dot = "digraph BPlusTree {\n";
    dot += "    node [shape=record, style=filled, fillcolor=\"#EEEDFE\"];\n";
    dot += "    rankdir=TB;\n\n";

    if (raiz == nullptr)
    {
        dot += "    empty [label=\"Arbol vacio\"];\n";
    } else
    {
        int nodoId = 0;
        generarDotHelper(raiz, dot, nodoId);
    }

    dot += "}\n";

    ofstream file(nombreDeArchivo);
    if (file.is_open())
    {
        file << dot;
        file.close();
        cout << "Archivo DOT generado: " << nombreDeArchivo << endl;
    } else
    {
        cout << "Error al crear archivo: " << nombreDeArchivo << endl;
    }
}

void ArbolBMas::generarDotHelper(BMasNodo* nodo, string& dot, int& nodoId) const
{
    int idActual = nodoId++;

    string label = "";
    for (int i = 0; i < nodo->numClaves; i++)
    {
        if (i > 0) label += " | ";
        if (nodo->esHoja) {
            label += nodo->claves[i] + ": " + nodo->data[i].nombre;
        } else {
            label += "<f" + to_string(i) + "> " + nodo->claves[i];
        }
    }

    string color = nodo->esHoja ? "#E1F5EE" : "#EEEDFE";
    dot += "    node" + std::to_string(idActual) +
           " [label=\"" + label + "\", fillcolor=\"" + color + "\"];\n";

    if (!nodo->esHoja) {
        for (int i = 0; i <= nodo->numClaves; i++) {
            int hijoId = nodoId;
            generarDotHelper(nodo->hijo[i], dot, nodoId);
            dot += "    node" + std::to_string(idActual) +
                   " -> node" + std::to_string(hijoId) + ";\n";
        }
    }
}

int ArbolBMas::getSize() const
{
    return size;
}

bool ArbolBMas::estaVacio() const
{
    return raiz == nullptr;
}
