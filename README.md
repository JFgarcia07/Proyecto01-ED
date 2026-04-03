# Catálogo de Productos - Supermercado

Sistema de gestión de catálogo de productos utilizando múltiples estructuras de datos implementadas desde cero en C++.

**Proyecto 1** — Estructuras de Datos, Primer Semestre 2026 
CUNOC — Universidad de San Carlos de Guatemala

---

## Requisitos

- Linux (probado en Zorin OS)
- g++ con soporte C++17
- CMake
- make
- Graphviz (para generar imágenes de los árboles)

### Instalar dependencias

```bash
sudo apt install build-essential cmake graphviz
```

---

## Compilación

```bash
rm -rf build
mkdir build
cd build
cmake ..
make
```

Para limpiar y recompilar desde cero, repetir los mismos pasos.

---

## Ejecución

Desde la carpeta `build`:

```bash
./Proy1EDD
```

---

## Formato del archivo CSV

El archivo debe tener 7 campos entre comillas, separados por comas. La primera línea es el header.

```
"Nombre","CodigoBarra","Categoria","FechaCaducidad","Marca","Precio","Stock"
"Leche Entera 1L","7501001234567","Lacteos","2026-06-15","Parma","12.50","100"
```

- **FechaCaducidad** debe estar en formato `YYYY-MM-DD` (10 caracteres).
- **CodigoBarra** debe ser único por producto.
- **Precio** y **Stock** deben ser valores numéricos no negativos.

---

## Menú del programa

```
1.  Cargar catálogo desde CSV
2.  Agregar producto manualmente
3.  Eliminar producto
4.  Buscar por nombre (AVL)
5.  Buscar por código de barra (Hash)
6.  Buscar por categoría (B+)
7.  Buscar por rango de fechas (B)
8.  Listar por nombre (AVL in-order)
9.  Generar archivos DOT (Graphviz)
10. Estadísticas de la tabla hash
0.  Salir
```

---

## Autor

Juan Fernando García Natareno
