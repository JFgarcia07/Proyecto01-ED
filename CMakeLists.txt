cmake_minimum_required(VERSION 3.28)
project(Proy1EDD)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proy1EDD main.cpp
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
        src/Arboles/ArbolAVL.h
        src/Arboles/ArbolAVL.cpp
        src/TablaHash/NodoHash.h
        src/TablaHash/NodoHash.cpp
        src/TablaHash/TablaHash.h
        src/TablaHash/TablaHash.cpp
        src/Arboles/BNodo.h
        src/Arboles/BNodo.cpp
        src/Arboles/ArbolB.h
        src/Arboles/ArbolB.cpp
        src/Arboles/BMasNodo.h
        src/Arboles/BMasNodo.cpp
        src/Arboles/ArbolBMas.h
        src/Arboles/ArbolBMas.cpp
        src/Logica/Catologo.h
        src/Logica/Catologo.cpp
        src/Logica/LectorCSV.h
        src/Logica/LectorCSV.cpp
        src/Logica/MotorDelSistema.cpp
        src/Logica/MotorDelSistema.h
)
