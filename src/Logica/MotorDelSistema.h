//
// Created by jfgarcianata on 30/03/26.
//

#ifndef UNTITLED1_MOTORDELSISTEMA_H
#define UNTITLED1_MOTORDELSISTEMA_H

#include "Catologo.h"

class MotorDelSistema
{
private:
    void header();
    void menu();
    void cargarCSV(Catalogo& catalogo);
    void agregarProducto(Catalogo& catalogo);
    void removerProducto(Catalogo& catalogo);
    void buscarPorNombre(Catalogo& catalogo);
    void buscarPorCodigoBarras(Catalogo& catalogo);
    void buscarPorCategoria(Catalogo& catalogo);
    void buscarPorRangoFecha(Catalogo& catalogo);
    void generarDot(Catalogo& catalogo);
    void mostrarDatosHash(Catalogo& catalogo);
public:
    void motorDelSistema();
};

#endif //UNTITLED1_MOTORDELSISTEMA_H
