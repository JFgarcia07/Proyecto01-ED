//
// Created by jfgarcianata on 14/03/26.
//


#include "AVLNodo.h"

AVLNodo::AVLNodo(const Producto& producto): data(producto), derecha(nullptr), izquierda(nullptr), altura(1){}

AVLNodo::~AVLNodo() {}