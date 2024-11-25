// FuncionesInventario.h
#ifndef FUNCIONESINVENTARIO_H
#define FUNCIONESINVENTARIO_H

#include "NodoMedicamento.h"
#include <iostream>
#include <fstream>
#include <iomanip> // Para formatear la salida

class Inventario {
private:
    NodoMedicamento* cabeza;

public:
    Inventario() : cabeza(nullptr) {}

    ~Inventario() { limpiarInventario(); }

    void agregarMedicamento(int id, const std::string& nombre, int cantidad) {
        if (buscarMedicamento(id)) {
            std::cout << "Error: El medicamento con ID " << id << " ya existe.\n";
            return;
        }

        NodoMedicamento* nuevo = new NodoMedicamento(id, nombre, cantidad);
        nuevo->setSiguiente(cabeza);
        cabeza = nuevo;
        std::cout << "Medicamento agregado exitosamente.\n";
    }

    void actualizarCantidad(int id, int nuevaCantidad) {
        NodoMedicamento* medicamento = buscarMedicamento(id);
        if (medicamento) {
            medicamento->setCantidad(nuevaCantidad);
            std::cout << "Cantidad actualizada exitosamente.\n";
        } else {
            std::cout << "Error: Medicamento no encontrado.\n";
        }
    }

    void mostrarInventario() const {
        NodoMedicamento* actual = cabeza;
        if (!actual) {
            std::cout << "El inventario está vacío.\n";
            return;
        }
        std::cout << std::left << std::setw(10) << "ID" 
                  << std::setw(20) << "Nombre" 
                  << std::setw(10) << "Cantidad\n";
        std::cout << std::string(40, '-') << '\n';

        while (actual) {
            std::cout << std::left << std::setw(10) << actual->getId()
                      << std::setw(20) << actual->getNombre()
                      << std::setw(10) << actual->getCantidad() << '\n';
            actual = actual->getSiguiente();
        }
    }

    void verificarStock(int limite) const {
        NodoMedicamento* actual = cabeza;
        bool encontrado = false;
        while (actual) {
            if (actual->getCantidad() < limite) {
                std::cout << "Alerta: El medicamento " << actual->getNombre() 
                          << " (ID: " << actual->getId() << ") tiene un stock bajo.\n";
                encontrado = true;
            }
            actual = actual->getSiguiente();
        }
        if (!encontrado) {
            std::cout << "Todos los medicamentos tienen suficiente stock.\n";
        }
    }

    void generarReporte(const std::string& archivo) const {
        std::ofstream archivoSalida(archivo);
        if (!archivoSalida) {
            std::cout << "Error al abrir el archivo para el reporte.\n";
            return;
        }
        NodoMedicamento* actual = cabeza;
        archivoSalida << std::left << std::setw(10) << "ID" 
                      << std::setw(20) << "Nombre" 
                      << std::setw(10) << "Cantidad\n";
        archivoSalida << std::string(40, '-') << '\n';

        while (actual) {
            archivoSalida << std::left << std::setw(10) << actual->getId()
                          << std::setw(20) << actual->getNombre()
                          << std::setw(10) << actual->getCantidad() << '\n';
            actual = actual->getSiguiente();
        }
        archivoSalida.close();
        std::cout << "Reporte generado exitosamente en " << archivo << '\n';
    }

private:
    NodoMedicamento* buscarMedicamento(int id) const {
        NodoMedicamento* actual = cabeza;
        while (actual) {
            if (actual->getId() == id) {
                return actual;
            }
            actual = actual->getSiguiente();
        }
        return nullptr;
    }

    void limpiarInventario() {
        NodoMedicamento* actual = cabeza;
        while (actual) {
            NodoMedicamento* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }
        cabeza = nullptr;
    }
};

#endif
