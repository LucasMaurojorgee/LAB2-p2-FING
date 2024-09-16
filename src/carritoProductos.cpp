#include "../include/carritoProductos.h"

struct rep_carritoProductos{
    TProducto producto;
    TCarritoProductos sig;
};


TCarritoProductos crearCarritoProductosVacio(){
    return NULL;
}

void insertarProductoCarritoProductos(TCarritoProductos &carritoProductos, TProducto producto){
    TCarritoProductos nuevoProducto = new rep_carritoProductos;
    nuevoProducto->producto = producto;
    nuevoProducto->sig = NULL;

    if (carritoProductos == NULL) {
        carritoProductos = nuevoProducto;
    } else {
        TCarritoProductos aux = carritoProductos;
        TCarritoProductos prev = NULL;
        while (aux != NULL && idTProducto(aux->producto) < idTProducto(producto)) {
            prev = aux;
            aux = aux->sig;
        }
        if (prev == NULL) {
            nuevoProducto->sig = carritoProductos;
            carritoProductos = nuevoProducto;
        } else {
            prev->sig = nuevoProducto;
            nuevoProducto->sig = aux;
        }
    }

}

void imprimirCarritoProductos(TCarritoProductos carritoProductos){
    TCarritoProductos aux = carritoProductos;
    while (aux != NULL){
        imprimirTProducto(aux->producto);
        aux = aux->sig;
    }
}

void liberarCarritoProductos(TCarritoProductos &carritoProductos){
    TCarritoProductos aux;
    while (carritoProductos != NULL){
        aux = carritoProductos;
        carritoProductos = carritoProductos->sig;
        liberarTProducto(aux->producto);
        delete aux;
    }
}

bool esVacioCarritoProductos(TCarritoProductos carritoProductos){
    return carritoProductos == NULL;
}

bool existeProductoCarritoProductos(TCarritoProductos carritoProductos, int idProducto){
    TCarritoProductos aux = carritoProductos;
    while (aux != NULL) {
        if (idTProducto(aux->producto) == idProducto) {
            return true;
        }
        aux = aux->sig;
    }
    return false;
}

TProducto obtenerProductoCarritoProductos(TCarritoProductos carritoProductos, int idProducto){
    TCarritoProductos aux = carritoProductos;
    while (aux != NULL) {
        if (idTProducto(aux->producto) == idProducto) {
            return aux->producto;
        }
        aux = aux->sig;
    }
    return NULL;

}

void removerProductoCarritoProductos(TCarritoProductos &carritoProductos, int idProducto){
    TCarritoProductos aux = carritoProductos;
    TCarritoProductos prev = NULL;
    while (aux != NULL) {
        if (idTProducto(aux->producto) == idProducto) {
            if (prev == NULL) {
                carritoProductos = aux->sig;
            } else {
                prev->sig = aux->sig;
            }
            liberarTProducto(aux->producto);
            delete aux;
            return;
        }
        prev = aux;
        aux = aux->sig;
    }

}