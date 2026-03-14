//
// Created by jfgarcianata on 13/03/26.
//
#include "Nodo.h"

Nodo::Nodo(const Producto& producto):
    data(producto), siguiente(nullptr) {}

Nodo::~Nodo() {}