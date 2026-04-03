//
// Created by jfgarcianata on 14/03/26.
//

#include "ArbolAVL.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "../Estructuras/Nodo.h"

ArbolAVL::ArbolAVL(): raiz(nullptr), size(0) {}

ArbolAVL::~ArbolAVL()
{
    destruirArbol(raiz);
    raiz = nullptr;
    size = 0;
}

void ArbolAVL::destruirArbol(AVLNodo* nodo)
{
    if (nodo == nullptr){ return; }

    destruirArbol(nodo->izquierda);
    destruirArbol(nodo->derecha);
    delete nodo;
}

int ArbolAVL::getAltura(AVLNodo* nodo) const
{
    if (nodo == nullptr){ return -0; }
    return nodo->altura;
}

/*
 * FACTOR DE BALANCE = ALTURA(IZQ) - ALTURA(DER)
 * SI ES +2 IZQUIERDA PESADO, SI ES -2 DERECHA PESADO
 */
int ArbolAVL::getBalance(AVLNodo* nodo) const
{
    if (nodo == nullptr){ return 0; }
    return getAltura(nodo->izquierda) - getAltura(nodo->derecha);
}

int ArbolAVL::max(int a, int b) const
{
    return (a > b) ? a : b;
}

/*
 * ROTACION IZQ: CUANDO EL SUBARBOL DERECHO ES MAS PESADO
 */
AVLNodo* ArbolAVL::rotacionIzquierda(AVLNodo* x)
{
    AVLNodo* y = x->derecha;
    AVLNodo* T2 = y->izquierda;

    //ROTAMOS
    y->izquierda = x;
    x->derecha = T2;

    //SE DEBE DE ACTUALIZAR LAS ALTURAS
    x->altura = max(getAltura(x->izquierda), getAltura(x->derecha)) + 1;
    y->altura = max(getAltura(y->izquierda), getAltura(y->derecha)) + 1;

    return y;
}

AVLNodo* ArbolAVL::rotacionDerecha(AVLNodo* y)
{
    AVLNodo* x = y->izquierda;
    AVLNodo* T2 = x->derecha;

    // Rotación
    x->derecha = y;
    y->izquierda = T2;

    // Actualizar alturas
    y->altura = max(getAltura(y->izquierda), getAltura(y->derecha)) + 1;
    x->altura = max(getAltura(x->izquierda), getAltura(x->derecha)) + 1;

    return x;
}

AVLNodo* ArbolAVL::insertarPriv(AVLNodo* nodo, const Producto& producto, bool& aprovado)
{
    //HACER INSERCION
    if (nodo == nullptr)
    {
        aprovado = true;
        return new AVLNodo(producto);
    }

    if (producto.nombre < nodo->data.nombre)
    {
        nodo->izquierda = insertarPriv(nodo->izquierda, producto, aprovado);
    } else if (producto.nombre > nodo->data.nombre)
    {
        nodo->derecha = insertarPriv(nodo->derecha, producto, aprovado);
    } else
    {
        aprovado = false;
        return nodo;
    }

    //ACTUALIZAR ALTURAS
    nodo->altura = max(getAltura(nodo->izquierda), getAltura(nodo->derecha)) + 1;

    //FACTOR DE BALANCE
    int balance = getBalance(nodo);

    //MANEJAR DESBALANCES

    //CASO LL
    if (balance > 1 && producto.nombre < nodo->izquierda->data.nombre)
    {
        return rotacionDerecha(nodo);
    }

    //CASO RR
    if (balance < -1 && producto.nombre > nodo->derecha->data.nombre)
    {
        return rotacionIzquierda(nodo);
    }

    //CASO RL
    if (balance < -1 && producto.nombre < nodo->derecha->data.nombre) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    //CASO LR
    if (balance > 1 && producto.nombre > nodo->izquierda->data.nombre) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }

    return nodo;
}

bool ArbolAVL::insertar(const Producto& producto)
{
    bool aprovado = false;
    raiz = insertarPriv(raiz, producto, aprovado);
    if (aprovado) size++;
    return aprovado;
}

Producto* ArbolAVL::buscar(const string& nombre) const
{
    return buscarPriv(raiz, nombre);
}

Producto* ArbolAVL::buscarPriv(AVLNodo* nodo, const string& nombre) const
{
    if (nodo == nullptr){ return nullptr; }

    if (nombre == nodo->data.nombre)
    {
        return &(nodo->data);
    } else if (nombre < nodo->data.nombre)
    {
        return buscarPriv(nodo->izquierda, nombre);
    } else
    {
        return buscarPriv(nodo->derecha, nombre);
    }
}

bool ArbolAVL::remover(const string& nombre)
{
    bool aprovado = false;
    raiz = removerPriv(raiz, nombre, aprovado);
    if (aprovado) {size--;}
    return aprovado;
}

AVLNodo* ArbolAVL::getNodoMinimoPriv(AVLNodo* nodo) const
{
    AVLNodo* actual = nodo;
    while (actual->izquierda != nullptr)
    {
        actual = actual->izquierda;
    }
    return actual;
}

AVLNodo* ArbolAVL::removerPriv(AVLNodo* nodo, const string& nombre, bool& aprovado)
{
    if (nodo == nullptr)
    {
        aprovado = false;
        return nullptr;
    }

    if (nombre < nodo->data.nombre)
    {
        nodo->izquierda = removerPriv(nodo->izquierda, nombre, aprovado);
    } else if (nombre > nodo->data.nombre)
    {
        nodo->derecha = removerPriv(nodo->derecha, nombre, aprovado);
    } else
    {
        aprovado = true;

        //CASO NODO CON 0 O 1 HIJO
        if (nodo->izquierda == nullptr || nodo->derecha == nullptr)
        {
            AVLNodo* temporal = nodo->izquierda ? nodo->izquierda : nodo->derecha;

            if (temporal == nullptr)
            {
                //SIGNIFICA QUE NO TIENE HIJOS
                temporal = nodo;
                nodo = nullptr;
            } else
            {
                //NODO CON HIJO, COPIAR LA INFO DEL HIJO Y ELIMINARLO
                *nodo = *temporal;
            }
            delete temporal;
        } else
        {
            //CASO NODO CON 2 HIJOS
            AVLNodo* sucesor = getNodoMinimoPriv(nodo->derecha);

            //COPIAMOS LOS DATOA DEL SUCESOR
            nodo->data = sucesor->data;
            string nombreSucesor = sucesor->data.nombre;

            nodo->derecha = removerPriv(nodo->derecha, nombreSucesor, aprovado);
            aprovado = true;
        }
    }

    if (nodo == nullptr) {return nullptr;}

    nodo->altura = max(getAltura(nodo->izquierda), getAltura(nodo->derecha)) + 1;

    int balance = getBalance(nodo);

    // Caso LL
    if (balance > 1 && getBalance(nodo->izquierda) >= 0) {
        return rotacionDerecha(nodo);
    }

    // Caso LR
    if (balance > 1 && getBalance(nodo->izquierda) < 0) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }

    // Caso RR
    if (balance < -1 && getBalance(nodo->derecha) <= 0) {
        return rotacionIzquierda(nodo);
    }

    // Caso Derecha-Izquierda
    if (balance < -1 && getBalance(nodo->derecha) > 0) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

void ArbolAVL::inOrden() const
{
    if (raiz == nullptr)
    {
        cout << "EL ARBOL ESTA VACIO" << endl;
        return;
    }
    inOrdenPriv(raiz);
    cout << "Total de productos: " << size << endl;
}

void ArbolAVL::inOrdenPriv(AVLNodo* nodo) const
{
    if (nodo == nullptr) { return; }
    inOrdenPriv(nodo->izquierda);
    nodo->data.mostrarProducto();
    inOrdenPriv(nodo->derecha);
}

void ArbolAVL::generarDotPriv(AVLNodo* nodo, string& dot) const
{
    if (nodo == nullptr) return;

    dot += "    \"" + nodo->data.nombre + "\" [label=\"" + nodo->data.nombre + "\\n(" + to_string(nodo->altura) + ")\"];\n";

    if (nodo->izquierda)
    {
        dot += "    \"" + nodo->data.nombre + "\" -> \"" + nodo->izquierda->data.nombre + "\";\n";
        generarDotPriv(nodo->izquierda, dot);
    }
    if (nodo->derecha)
    {
        dot += "    \"" + nodo->data.nombre + "\" -> \"" + nodo->derecha->data.nombre + "\";\n";
        generarDotPriv(nodo->derecha, dot);
    }
}

void ArbolAVL::generarDot(const string& nombre) const
{
    string dot = "digraph ArbolAVL {\n";
    dot += "    node [shape=ellipse, style=filled, fillcolor=\"#D6EAF8\"];\n\n";

    if (raiz == nullptr)
    {
        dot += "    empty [label=\"Arbol vacio\"];\n";
    } else
    {
        generarDotPriv(raiz, dot);
    }

    dot += "}\n";

    ofstream file(nombre);
    if (file.is_open())
    {
        file << dot;
        file.close();
        cout << "Archivo DOT generado: " << nombre << endl;
    } else
    {
        cout << "Error al crear archivo: " << nombre << endl;
    }
}

int ArbolAVL::getSize() const
{
    return size;
}

bool ArbolAVL::estaVacio() const
{
    return raiz == nullptr;
}
