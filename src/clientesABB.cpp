#include "../include/clientesABB.h"

struct rep_clientesABB {
    TCliente cliente;
    rep_clientesABB *izq;
    rep_clientesABB *der;
};

TClientesABB crearTClientesABBVacio(){
    return NULL;
}

void insertarTClienteTClientesABB(TClientesABB &clientesABB, TCliente cliente){
 if (clientesABB == NULL) {
        clientesABB = new rep_clientesABB;
        clientesABB->cliente = cliente;
        clientesABB->izq = NULL;
        clientesABB->der = NULL;
    } else {
        int idNuevoCliente = idTCliente(cliente);
        int idClienteActual = idTCliente(clientesABB->cliente);
        
        if (idNuevoCliente < idClienteActual) {
            insertarTClienteTClientesABB(clientesABB->izq, cliente);
        } else if (idNuevoCliente > idClienteActual) {
            insertarTClienteTClientesABB(clientesABB->der, cliente);
        }
    }
}

void imprimirTClientesABB(TClientesABB clientesABB){
     if (clientesABB != NULL) {
        imprimirTClientesABB(clientesABB->izq);
        imprimirTCliente(clientesABB->cliente);
        imprimirTClientesABB(clientesABB->der);
    }
}

void liberarTClientesABB(TClientesABB &clientesABB){
 if (clientesABB != NULL) {
        liberarTClientesABB(clientesABB->izq);
        liberarTClientesABB(clientesABB->der);
        liberarTCliente(clientesABB->cliente);
        delete clientesABB;
        clientesABB = NULL;
    }
}

bool existeTClienteTClientesABB(TClientesABB clientesABB, int idCliente){
    if (clientesABB == NULL) {
        return false;
    } else if (idTCliente(clientesABB->cliente) == idCliente) {
        return true;
    } else if (idCliente < idTCliente(clientesABB->cliente)) {
        return existeTClienteTClientesABB(clientesABB->izq, idCliente);
    } else {
        return existeTClienteTClientesABB(clientesABB->der, idCliente);
    }
}

TCliente obtenerTClienteTClientesABB(TClientesABB clientesABB, int idCliente){
    if (clientesABB == NULL) {
        return NULL;
    } else if (idTCliente(clientesABB->cliente) == idCliente) {
        return clientesABB->cliente;
    } else if (idCliente < idTCliente(clientesABB->cliente)) {
        return obtenerTClienteTClientesABB(clientesABB->izq, idCliente);
    } else {
        return obtenerTClienteTClientesABB(clientesABB->der, idCliente);
    }
}

nat alturaTClientesABB(TClientesABB clientesABB){
    if (clientesABB == NULL) {
        return 0;
    } else {
        nat alturaIzq = alturaTClientesABB(clientesABB->izq);
        nat alturaDer = alturaTClientesABB(clientesABB->der);
        
        return 1 + (alturaIzq > alturaDer ? alturaIzq : alturaDer);
    }
}

TCliente maxIdTClienteTClientesABB(TClientesABB clientesABB){
    if (clientesABB == NULL) {
        return NULL;
    }
    
    while (clientesABB->der != NULL) {
        clientesABB = clientesABB->der;
    }
    
    return clientesABB->cliente;
}

void removerTClienteTClientesABB(TClientesABB &clientesABB, int idCliente){
  if (clientesABB == NULL) return;

    if (idCliente < idTCliente(clientesABB->cliente)) {
        removerTClienteTClientesABB(clientesABB->izq, idCliente);
    } else if (idCliente > idTCliente(clientesABB->cliente)) {
        removerTClienteTClientesABB(clientesABB->der, idCliente);
    } else {
        if (clientesABB->izq == NULL) {
            TClientesABB nodoAEliminar = clientesABB;
            clientesABB = clientesABB->der;
            liberarTCliente(nodoAEliminar->cliente);
            delete nodoAEliminar;
        } else if (clientesABB->der == NULL) {
            TClientesABB nodoAEliminar = clientesABB;
            clientesABB = clientesABB->izq;
            liberarTCliente(nodoAEliminar->cliente);
            delete nodoAEliminar;
        } else {
            TClientesABB mayorIzq = maxIdTClienteTClientesABB(clientesABB->izq);
            clientesABB->cliente = copiarTCliente(mayorIzq);
            removerTClienteTClientesABB(clientesABB->izq, idTCliente(mayorIzq));
        }
    }
}

int cantidadClientesTClientesABB(TClientesABB clientesABB){
    if (clientesABB == NULL) {
        return 0;
    } else {
        int cantidadIzq = cantidadClientesTClientesABB(clientesABB->izq);
        int cantidadDer = cantidadClientesTClientesABB(clientesABB->der);
        
        return 1 + cantidadIzq + cantidadDer;
    }
}

float edadPromedioTClientesABB(TClientesABB clientesABB){
    void sumarEdadesYContar(TClientesABB nodo, int &sumaEdades, int &contador) {
        if (nodo != NULL) {
            sumaEdades += edadTCliente(nodo->cliente);
            contador++;
            
            sumarEdadesYContar(nodo->izq, sumaEdades, contador);
            sumarEdadesYContar(nodo->der, sumaEdades, contador);
        }
    }

    int sumaEdades = 0;
    int contador = 0;
    
    sumarEdadesYContar(clientesABB, sumaEdades, contador);
    
    if (contador == 0) {
        return 0.0;
    } else {
        return static_cast<float>(sumaEdades) / contador;
    }
}

TCliente obtenerNesimoClienteTClientesABB(TClientesABB clientesABB, int n){
    TCliente obtenerClienteEnOrden(TClientesABB nodo, int &n, int &contador) {
        if (nodo == NULL) {
            return NULL;
        }
        
        TCliente resultado = obtenerClienteEnOrden(nodo->izq, n, contador);
        if (resultado != NULL) {
            return resultado;
        }
        
        contador++;
        if (contador == n) {
            return nodo->cliente;
        }
        
        return obtenerClienteEnOrden(nodo->der, n, contador);
    }
    
    int contador = 0;
    return obtenerClienteEnOrden(clientesABB, n, contador);
}

