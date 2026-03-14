cmake_minimum_required(VERSION 4.1)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled1 main.cpp
        src/Estructuras/Producto.h
        src/Estructuras/Producto.cpp
        src/Estructuras/ListaProductos.h
        src/Estructuras/Nodo.h
        src/Estructuras/ListaProductos.cpp
        src/Estructuras/Nodo.cpp
        src/Estructuras/ListaProductosOrdenada.h
        src/Estructuras/LIstaProductosOrdenada.cpp
        src/Arboles/AVLNodo.cpp
        src/Arboles/AVLNodo.h
        src/Arboles/ArbolAVL.h)
