// NodoMedicamento.h
#ifndef NODOMEDICAMENTO_H
#define NODOMEDICAMENTO_H

#include <string>

class NodoMedicamento {
private:
    int id;
    std::string nombre;
    int cantidad;
    NodoMedicamento* siguiente;

public:
    NodoMedicamento(int id, const std::string& nombre, int cantidad)
        : id(id), nombre(nombre), cantidad(cantidad), siguiente(nullptr) {}

    int getId() const { return id; }
    const std::string& getNombre() const { return nombre; }
    int getCantidad() const { return cantidad; }
    void setCantidad(int nuevaCantidad) { cantidad = nuevaCantidad; }

    NodoMedicamento* getSiguiente() const { return siguiente; }
    void setSiguiente(NodoMedicamento* nodo) { siguiente = nodo; }
};

#endif
