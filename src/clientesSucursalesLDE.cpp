#include "../include/clientesSucursalesLDE.h"

struct rep_clientesSucursalesLDE {
 	TClientesABB clientesABB;
    rep_clientesSucursalesLDE *prev;
    rep_clientesSucursalesLDE *next;
};

TClientesSucursalesLDE crearTClientesSucursalesLDEVacia(){
	return NULL;
}

float calcularEdadPromedio(TClientesABB clientesABB) {
    return edadPromedioTClientesABB(clientesABB);
}

void insertarClientesABBTClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE, TClientesABB clientesABB, int idSucursal){
    rep_clientesSucursalesLDE *nuevoNodo = new rep_clientesSucursalesLDE;
    nuevoNodo->clientesABB = clientesABB;
    nuevoNodo->prev = NULL;
    nuevoNodo->next = NULL;
    
    float edadPromedioNuevo = calcularEdadPromedio(clientesABB);

    if (clientesSucursalesLDE == NULL) {
        clientesSucursalesLDE = nuevoNodo;
        return;
    }

    rep_clientesSucursalesLDE *actual = clientesSucursalesLDE;
    rep_clientesSucursalesLDE *prev = NULL;

    while (actual != NULL && calcularEdadPromedio(actual->clientesABB) < edadPromedioNuevo) {
        prev = actual;
        actual = actual->next;
    }

    if (prev == NULL) {
        nuevoNodo->next = clientesSucursalesLDE;
        clientesSucursalesLDE->prev = nuevoNodo;
        clientesSucursalesLDE = nuevoNodo;
    } else {
        nuevoNodo->next = actual;
        nuevoNodo->prev = prev;
        prev->next = nuevoNodo;
        if (actual != NULL) {
            actual->prev = nuevoNodo;
        }
    }
}

void liberarNodo(rep_clientesSucursalesLDE *nodo) {
    if (nodo != NULL) {
        liberarTClientesABB(nodo->clientesABB);

        delete nodo;
    }
}

void liberarTClientesSucursalesLDE(TClientesSucursalesLDE &clientesSucursalesLDE){
 	rep_clientesSucursalesLDE *actual = clientesSucursalesLDE;
    rep_clientesSucursalesLDE *siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->next;
        liberarNodo(actual);
        actual = siguiente;
    }

    clientesSucursalesLDE = NULL;
}

void calcularSumaYConteo(TClientesABB nodo, int &sumaEdad, int &conteoClientes) {
    if (nodo != NULL) {
        calcularSumaYConteo(nodo->izq, sumaEdad, conteoClientes);
        
        sumaEdad += edadTCliente(nodo->cliente);
        conteoClientes++;
        
        calcularSumaYConteo(nodo->der, sumaEdad, conteoClientes);
    }
}

float edadPromedioTClientesABB(TClientesABB clientesABB) {
    int sumaEdad = 0;
    int conteoClientes = 0;
    
    calcularSumaYConteo(clientesABB, sumaEdad, conteoClientes);
    
    if (conteoClientes == 0) {
        return 0.0;
    }
    
    return static_cast<float>(sumaEdad) / conteoClientes;
}

void imprimirTClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
  rep_clientesSucursalesLDE *actual = clientesSucursalesLDE;
    
    printf("clientesSucursalesLDE de grupos:\n");
    
    while (actual != NULL) {
        float edadPromedio = edadPromedioTClientesABB(actual->clientesABB);
        
        printf("Grupo con edad promedio %.2f:\n", edadPromedio);
        imprimirTClientesABB(actual->clientesABB);
        
        actual = actual->next;
    }
}

void imprimirInvertidoRec(TClientesSucursalesLDE lista) {
    if (lista != NULL) {
        imprimirInvertidoRec(lista->siguiente);

        float edadPromedio = edadPromedioTClientesABB(lista->clientesABB);
        printf("Grupo con edad promedio %.2f:\n", edadPromedio);
        imprimirTClientesABB(lista->clientesABB);
        printf("\n");
    }
}

void imprimirInvertidoTClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	imprimirInvertidoRec(clientesSucursalesLDE);
}

nat cantidadTClientesABBClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	nat cantidad = 0;
    TClientesSucursalesLDE actual = clientesSucursalesLDE;

    while (actual != NULL) {
        cantidad++;
        actual = actual->siguiente;
    }

    return cantidad;
}

TClientesABB obtenerPrimeroClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
    if (clientesSucursalesLDE == NULL || clientesSucursalesLDE->inicio == NULL) {
        return NULL;
    }
    
    return clientesSucursalesLDE->inicio->clientesABB;
}

TClientesABB obtenerNesimoClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE, int n){
    if (n <= 0) {
        return NULL;
    }

    rep_clientesSucursalesLDE *actual = clientesSucursalesLDE->inicio;
    
    int contador = 1;

    while (actual != NULL && contador < n) {
        actual = actual->siguiente;
        contador++;
    }

    if (actual != NULL) {
        return actual->clientesABB;
    } else {
        return NULL;
    }
}

TClientesABB removerUltimoClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
    if (clientesSucursalesLDE->inicio == NULL) {
        return NULL;
    }

    rep_clientesSucursalesLDE *actual = clientesSucursalesLDE->fin;
    TClientesABB clientesABB = actual->clientesABB;

    if (clientesSucursalesLDE->inicio == clientesSucursalesLDE->fin) {
        clientesSucursalesLDE->inicio = NULL;
        clientesSucursalesLDE->fin = NULL;
    } else {
        clientesSucursalesLDE->fin = actual->anterior;
        clientesSucursalesLDE->fin->siguiente = NULL;
    }

    delete actual;

    return clientesABB;
}

TClientesABB removerNesimoClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE, int n){
    if (n <= 0) {
        return NULL;
    }

    rep_clientesSucursalesLDE *actual = clientesSucursalesLDE->inicio;
    int index = 1;

    while (actual != NULL && index < n) {
        actual = actual->siguiente;
        index++;
    }

    if (actual == NULL) {
        return NULL;
    }

    TClientesABB clientesABB = actual->clientesABB;

    if (actual->anterior != NULL) {
        actual->anterior->siguiente = actual->siguiente;
    } else {
        clientesSucursalesLDE->inicio = actual->siguiente;
    }

    if (actual->siguiente != NULL) {
        actual->siguiente->anterior = actual->anterior;
    } else {
        clientesSucursalesLDE->fin = actual->anterior;
    }

    delete actual;

    return clientesABB;
}

void recorrerYContar(TClientesABB clientesABB, std::unordered_map<int, int>& frecuencia) {
    if (clientesABB == NULL) {
        return;
    }

    recorrerYContar(clientesABB->izq, frecuencia);
    
    int idCliente = idTCliente(clientesABB->cliente);
    frecuencia[idCliente]++;
    
    recorrerYContar(clientesABB->der, frecuencia);
}

TCliente obtenerClientePorId(TClientesSucursalesLDE clientesSucursalesLDE, int idCliente) {
    rep_clientesSucursalesLDE *actual = clientesSucursalesLDE->inicio;

    while (actual != NULL) {
        TClientesABB clientesABB = actual->clientesABB;
        if (existeTClienteTClientesABB(clientesABB, idCliente)) {
            return obtenerTClienteTClientesABB(clientesABB, idCliente);
        }
        actual = actual->siguiente;
    }

    return NULL;
}

TCliente clienteMasRepetido(TClientesSucursalesLDE clientesSucursalesLDE){
    std::unordered_map<int, int> frecuencia;
    int maxFrecuencia = 0;
    int clienteMasFrecuenteId = INT_MAX;

    rep_clientesSucursalesLDE *actual = clientesSucursalesLDE->inicio;

    while (actual != NULL) {
        TClientesABB clientesABB = actual->clientesABB;
        recorrerYContar(clientesABB, frecuencia);

        actual = actual->siguiente;
    }

    for (const auto& par : frecuencia) {
        int idCliente = par.first;
        int freq = par.second;
        if (freq > maxFrecuencia || (freq == maxFrecuencia && idCliente < clienteMasFrecuenteId)) {
            maxFrecuencia = freq;
            clienteMasFrecuenteId = idCliente;
        }
    }

    if (clienteMasFrecuenteId == INT_MAX) {
        return NULL;
    }

    return obtenerClientePorId(clientesSucursalesLDE, clienteMasFrecuenteId);
}
