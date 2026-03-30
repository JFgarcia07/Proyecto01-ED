//
// Created by jfgarcianata on 20/03/26.
//

#include "ArbolB.h"
#include <iostream>
#include <fstream>
#include <strings.h>

ArbolB::ArbolB(int grado) : raiz(nullptr), grado(grado), size(0){}

ArbolB::~ArbolB()
{
    destruirArbol(raiz);
    raiz = nullptr;
    size = 0;
}

void ArbolB::destruirArbol(BNodo* nodo)
{
    if (nodo == nullptr){ return; }

    if (!nodo->esHoja)
    {
        for (int i = 0; i < nodo->numClaves; i++)
        {
            destruirArbol(nodo->hijos[i]);
        }
    }
    delete nodo;
}

//BUSQUEDA
int ArbolB::encontrarClave(BNodo* nodo, const string& fecha) const
{
    int indice = 0;
    while (indice < nodo->numClaves && nodo->claves[indice].fechaExpiracion < fecha)
    {
        indice++;
    }
    return indice;
}

Producto* ArbolB::buscar(const string& fecha) const
{
    if (raiz == nullptr){return nullptr;}
    return buscarPriv(raiz, fecha);
}

Producto* ArbolB::buscarPriv(BNodo* nodo, const string& fecha) const
{
    int i = encontrarClave(nodo, fecha);

    if (i < nodo->numClaves && nodo->claves[i].fechaExpiracion == fecha)
    {
        return &(nodo->claves[i]);
    }

    if (nodo->esHoja){return nullptr;}

    return buscarPriv(nodo->hijos[i], fecha);
}

void ArbolB::rangoBusqueda(const string& fechaInicio, const string& fechaFinal) const
{
    if (raiz == nullptr)
    {
        cout << "El arbol B esta vacio" << endl;
        return;
    }

    cout << "Productos con fechas entre " << fechaInicio << " y " << fechaFinal << endl;
    int contador = 0;
    rangoBusquedaPriv(raiz, fechaInicio, fechaFinal, contador);
    cout << "Total de encontrados: " << contador <<endl;
}


void ArbolB::rangoBusquedaPriv(BNodo* nodo, const string& fechaInicio, const string& fechaFinal, int& contador) const
{
    int i = 0;

    for (i = 0; i < nodo->numClaves; i++) {
        // Si no es hoja, recorrer hijo izquierdo si puede tener claves en rango
        if (!nodo->esHoja && nodo->claves[i].fechaExpiracion >= fechaInicio) {
            rangoBusquedaPriv(nodo->hijos[i], fechaInicio, fechaFinal, contador);
        }

        // Si la clave está en el rango, mostrarla
        if (nodo->claves[i].fechaExpiracion >= fechaInicio &&
            nodo->claves[i].fechaExpiracion <= fechaFinal) {
            nodo->claves[i].mostrarProducto();
            contador++;
            }

        // Si la clave ya es mayor que fecha de expiracion, no seguir
        if (nodo->claves[i].fechaExpiracion > fechaFinal) {
            return;
        }

        //Recorrer el ultimo hijo si no es hoja
        if (!nodo->esHoja)
        {
            rangoBusquedaPriv(nodo->hijos[i], fechaInicio, fechaFinal, contador);
        }
    }
}

bool ArbolB::insertar(const Producto& producto)
{
    if (raiz == nullptr)
    {
        //SIGNIFICA QUE ESTA VACIO EL ARBOL, SE DEBE DE CREAR LA RAIZ
        raiz = new BNodo(grado, true);
        raiz->claves[0] = producto;
        raiz->numClaves = 1;
    } else if (raiz->numClaves == 2*grado -1)
    {
        //LA RAIZ ESTA LLENAL HAY QUE CREAR UN NUEVA Y DIVIDIR
        BNodo* nuevaRaiz = new BNodo(grado, false);
        nuevaRaiz->hijos[0] = raiz;
        separarHijos(nuevaRaiz, 0, raiz);

        int i = 0;
        if (nuevaRaiz->claves[0].fechaExpiracion < producto.fechaExpiracion)
        {
            i++;
        }
        insertarNoCompleto(nuevaRaiz->hijos[i], producto);
        raiz = nuevaRaiz;
    } else
    {
        insertarNoCompleto(raiz, producto);
    }

    size++;
    return true;
}

void ArbolB::separarHijos(BNodo* padre, int i, BNodo* hijo)
{
    BNodo* nuevoNodo = new BNodo(hijo->grado, padre->esHoja);
    nuevoNodo->numClaves = grado - 1;

    //COPIAMOS LAS ULTIMAS T-1 CLAVES DEL HIJO AL NUEVO NODO
    for (int j=0; j < grado-1; j++)
    {
        nuevoNodo->claves[j] = hijo->claves[j + grado];
    }

    //COPIAMOS LOS ULTIMOS HIJOS SI NO ES HOJA
    if (!hijo->esHoja)
    {
        for (int j = 0; j < grado; j++)
        {
            nuevoNodo->hijos[j] = hijo->hijos[j + grado];
        }
    }

    hijo->numClaves = grado - 1;

    //HACEMOS ESPACIO PARA EL NUEVO HIJO DEL PAFRE
    for (int j = padre->numClaves; j >= i + 1; j--)
    {
        padre->claves[j+1] = padre->claves[j];
    }

    //LA CLAVE DEL MEDIO DEL HIJO SUBE AL PADRE
    padre->claves[i] = padre->claves[grado - 1];
    padre->numClaves++;
}

void ArbolB::insertarNoCompleto(BNodo* nodo, const Producto& producto)
{
    int i =  nodo->numClaves - 1;

    if (nodo->esHoja)
    {
        //DESPLAZAR CLAVES PARA HACER ESPACIO
        while (i >= 0 && nodo->claves[i].fechaExpiracion > producto.fechaExpiracion)
        {
            nodo->claves[i+1] = nodo->claves[i];
            i--;
        }
        nodo->claves[i+1] = producto;
        nodo->numClaves++;
    } else
    {
        //ENCONTRAR EL HIJO DONDE DEBE IR
        while (i >= 0 && nodo->claves[i].fechaExpiracion > producto.fechaExpiracion)
        {
            i--;
        }
        i++;

        //SI EL HIJO ESTA LLENO, HAY QUE DIVIDIRLO
        if (nodo->hijos[i]->numClaves == 2 * grado - 1)
        {
            separarHijos(nodo, i, nodo->hijos[i]);
            //DECIDIR QUE HIJO VAMO A UTILIZAR
            if (nodo->claves[i].fechaExpiracion < producto.fechaExpiracion)
            {
                i++;
            }
        }
        insertarNoCompleto(nodo->hijos[i], producto);
    }
}

bool ArbolB::remover(const string& fecha)
{
    if (raiz == nullptr) {return false;}

    if (buscar(fecha) == nullptr){ return false;}

    removerDelNodo(raiz, fecha);

    //SI LA RAIZ QUEDO VACIA Y TIENE UN HIJO, SE HIJO AHORA SERA LA RAIZ
    if (raiz->numClaves == 0)
    {
        BNodo* raizVieja = raiz;
        if (raiz->esHoja)
        {
            raiz = nullptr;
        } else
        {
            raiz = raiz->hijos[0];
        }
        //DEBEMOS DE EVITAR QUE EL DESTRUCTOR ELIMINE A LOS HIJOS
        raizVieja->hijos[0] = nullptr;
        delete raizVieja;
    }

    size--;
    return true;
}

void ArbolB::removerDelNodo(BNodo* nodo, const string& fecha)
{
    int indice = encontrarClave(nodo, fecha);

    //SI LA CLAVE ESTA EN ESTE NODO
    if (indice < nodo->numClaves && nodo->claves[indice].fechaExpiracion == fecha)
    {
        if (nodo->esHoja)
        {
            removerDeHoja(nodo, indice);
        } else
        {
            removerDeInterno(nodo, indice);
        }
    } else
    {
        //SI LA CLAVE NO ESTA EN ESTE NODO, HAY QUE BAJAR AL HIJO
        if (nodo->esHoja){return;}

        bool ultimoHijo = (indice == nodo->numClaves);

        //HAY QUE ASEGURASE QUE TENGA AL MENO T CLAVES
        if (nodo->hijos[indice]->numClaves < grado)
        {
            llenar(nodo, indice);
        }

        //SI EL ULTIMO HIJO SE FUCIONO, HAY QUE IR AL ANTERIOR
        if (ultimoHijo && indice > nodo->numClaves)
        {
            removerDelNodo(nodo->hijos[indice-1], fecha);
        } else
        {
            removerDelNodo(nodo->hijos[indice], fecha);
        }
    }
}

void ArbolB::removerDeHoja(BNodo* nodo, int indice)
{
    //DESPALAZAR CLAVES A LA IZQ
    for (int i = indice + 1; i < nodo->numClaves; i++)
    {
        nodo->claves[i-1] = nodo->claves[i];
    }
    nodo->numClaves--;
}

void ArbolB::removerDeInterno(BNodo* nodo, int indice)
{
    string fecha = nodo->claves[indice].fechaExpiracion;

    //CASO A: SI EL HIJO IZQ TIENE >= T CLAVES, USAR EL PREDECESOR
    if (nodo->hijos[indice]->numClaves >= grado)
    {
        Producto pred = getPredecesor(nodo, indice);
        nodo->claves[indice] = pred;
        removerDelNodo(nodo->hijos[indice], pred.fechaExpiracion);
    }
    //CASO B: HIJO DERECHO TIENE >= T CLAVES, USAR SUCESOR
    else if (nodo->hijos[indice + 1]->numClaves >= grado)
    {
        Producto suce = getSucesor(nodo, indice);
        nodo->claves[indice] = suce;
        removerDelNodo(nodo->hijos[indice+1], suce.fechaExpiracion);
    }
    //CASO C: AMBOS HIJOS TIENEN T-1 CLAVES, HAY QUE FUCIONAR
    else
    {
        merge(nodo, indice);
        removerDelNodo(nodo->hijos[indice], fecha);
    }
}

Producto ArbolB::getPredecesor(BNodo* nodo, int indice)
{
    BNodo* actual = nodo->hijos[indice];
    while (!actual->esHoja)
    {
        actual = actual->hijos[actual->numClaves];
    }
    return actual->claves[actual->numClaves - 1];
}

Producto ArbolB::getSucesor(BNodo* nodo, int indice)
{
    BNodo* actual = nodo->hijos[indice + 1];
    while (!actual->esHoja)
    {
        actual = actual->hijos[0];
    }
    return actual->claves[0];
}

void ArbolB::llenar(BNodo* nodo, int indice)
{
    //INTERNAR TOMAR PRESTADO DEL HERMANO IZQ
    if (indice != 0 && nodo->hijos[indice-1]->numClaves >= grado)
    {
        prestarPrevio(nodo, indice);
    }
    // INTERNAR TOMAR PRESTADO DEL HERMANO DERECHO
    else if (indice != nodo->numClaves && nodo->hijos[indice + 1]->numClaves >= grado)
    {
        prestarSiguiente(nodo, indice);
    }
    //FUSIONAR CON UN HERMANO
    else
    {
        if (indice != nodo->numClaves)
        {
            merge(nodo, indice);
        } else
        {
            merge(nodo, indice-1);
        }
    }
}

void ArbolB::prestarPrevio(BNodo* nodo, int indice)
{
    BNodo* hijo = nodo->hijos[indice];
    BNodo* hermano = nodo->hijos[indice - 1];

    for (int i = hijo->numClaves -1; i >= 0; i--)
    {
        hijo->hijos[i+1] = hijo->hijos[i];
    }

    if (!hijo->esHoja)
    {
        for (int i = hijo->numClaves -1; i >= 0; i--)
        {
            hijo->hijos[i+1] = hijo->hijos[i];
        }
    }

    //LA CLAVE DEL PADRE BAJA AL HIJO
    hijo->claves[0] = nodo->claves[indice -1];

    //EL ULTIMO HIJO DEL HERMANO PASA A HIJO
    if (!hijo->esHoja)
    {
        hijo->hijos[0] = hermano->hijos[hermano->numClaves];
    }

    //LA ULTIMA CLAVE DEL HERMANO SUBE AL PADRE
    nodo->claves[indice -1] = hermano ->claves[hermano->numClaves - 1];

    hijo->numClaves++;
    hermano->numClaves--;
}

void ArbolB::prestarSiguiente(BNodo* nodo, int indice)
{
    BNodo* hijo = nodo->hijos[indice];
    BNodo* hermano = nodo->hijos[indice + 1];

    //LA CLAVE DEL PADRE BAJA AL FINAL DEL HIJO
    hijo->claves[hijo->numClaves] = nodo->claves[indice];

    //EL PRIMER HIJO DEL HERMANO PASA AL HIJO
    if (!hijo->esHoja)
    {
        hijo->hijos[hijo->numClaves + 1] = hermano->hijos[0];
    }

    nodo->claves[indice] = hermano->claves[0];

    //DESPLAZAR CLAVES E HIJOS DEL HERMANO A LA IZQ
    for (int i = 1; i < hermano->numClaves; i++)
    {
        hermano->claves[i - 1] = hermano->claves[i];
    }
    if (!hermano->esHoja)
    {
        for (int i = 1; i <= hermano->numClaves; i++)
        {
            hermano->hijos[i - 1] = hermano->hijos[i];
        }
    }

    hijo->numClaves++;
    hermano->numClaves--;
}

void ArbolB::merge(BNodo* nodo, int indice)
{
    BNodo* hijo = nodo->hijos[indice];
    BNodo* hermano = nodo->hijos[indice + 1];

    hijo->claves[grado - 1] = nodo->claves[indice];

    //COPIAR CLAVES DEL HERMANO AL HIJO
    for (int i = 0; i < hermano->numClaves; i++)
    {
        hijo->hijos[i + 1] = hermano->hijos[i];
    }

    //COPIR HIJOS DEL HERMANO AL HIJO
    if (!hijo->esHoja)
    {
        for (int i = 0; i <= hermano->numClaves; i++)
        {
            hijo->hijos[i + grado] = hermano->hijos[i];
        }
    }

    //DEZPLAZAR CLAVES E HIJOS DEL PADRE A LA IZQ
    for (int i = indice + 1; i < nodo->numClaves; i++)
    {
        nodo->hijos[i - 1] = nodo->hijos[i];
    }

    for (int i = indice + 2; i <= nodo->numClaves; i++)
    {
        nodo->hijos[i - 1] = nodo->hijos[i];
    }

    hijo->numClaves += hermano->numClaves + 1;
    nodo->numClaves--;

    //LIMPIAR PUNTEROS
    if (!hermano->esHoja)
    {
        for (int i = 0; i <= nodo->numClaves; i++)
        {
            hermano->hijos[i] = nullptr;
        }
    }
    delete hermano;
}

void ArbolB::generarDot(const string& nombreArchivo) const
{
    string dot = "digraph BTree {\n";
    dot += "    node [shape=record, style=filled, fillcolor=\"#E1F5EE\"];\n";
    dot += "    rankdir=TB;\n\n";

    if (raiz == nullptr) {
        dot += "    empty [label=\"Arbol vacio\"];\n";
    } else {
        int nodeId = 0;
        generarDotHelper(raiz, dot, nodeId);
    }

    dot += "}\n";

    ofstream file(nombreArchivo);
    if (file.is_open()) {
        file << dot;
        file.close();
        std::cout << "Archivo DOT generado: " << nombreArchivo << std::endl;
    } else {
        std::cout << "Error al crear archivo: " << nombreArchivo << std::endl;
    }
}

void ArbolB::generarDotHelper(BNodo* nodo, string& dot, int& nodoId) const
{
    int  idActual = nodoId++;

    // Construir etiqueta con todas las claves del nodo
    string label = "";
    for (int i = 0; i < nodo->numClaves; i++) {
        if (i > 0) label += " | ";
        label += "<f" + std::to_string(i) + "> " + nodo->claves[i].fechaExpiracion;
    }

    dot += "    node" + to_string(idActual) + " [label=\"" + label + "\"];\n";

    // Conexiones a hijos
    if (!nodo->esHoja) {
        for (int i = 0; i <= nodo->numClaves; i++) {
            int childId = nodoId;
            generarDotHelper(nodo->hijos[i], dot, nodoId);
            dot += "    node" + std::to_string(idActual) +
                   " -> node" + std::to_string(childId) + ";\n";
        }
    }
}

int ArbolB::getSize() const
{
    return size;
}

bool ArbolB::estaVacio() const
{
    return raiz == nullptr;
}
