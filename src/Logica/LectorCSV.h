//
// Created by jfgarcianata on 29/03/26.
//

#ifndef UNTITLED1_LECTORCSV_H
#define UNTITLED1_LECTORCSV_H

#include "Catologo.h"
#include <string>

using namespace std;

class LectorCSV
{
    private:
    bool parsearLinea(const string& linea, Producto& producto);
    bool validar(const Producto& producto, int numLinea, string& error);

    string quitarComillas(const string& entrada) const;

    public:
    LectorCSV();
    ~LectorCSV();

    int cargar(const string& nombreArchivo, Catalogo& catalogo);
};
#endif //UNTITLED1_LECTORCSV_H