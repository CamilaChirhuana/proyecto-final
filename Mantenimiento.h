#ifndef MANTENIMIENTO_H
#define MANTENIMIENTO_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Definición de constantes
const int TAM_HASH = 10;

// Clase NodoMantenimiento
class NodoMantenimiento {
private:
	int idEquipo;
	string nombreEquipo;
	string fechaMantenimiento;
	string tipoMantenimiento;
	string responsable;
	string estado;
	NodoMantenimiento* siguiente;
	
public:
	// Constructor
	NodoMantenimiento(int id, string nombre, string fecha, string tipo, string resp, string est)
		: idEquipo(id), nombreEquipo(nombre), fechaMantenimiento(fecha), 
		tipoMantenimiento(tipo), responsable(resp), estado(est), siguiente(nullptr) {}
	
	// Getters
	int getIdEquipo() const { return idEquipo; }
	string getNombreEquipo() const { return nombreEquipo; }
	string getFechaMantenimiento() const { return fechaMantenimiento; }
	string getTipoMantenimiento() const { return tipoMantenimiento; }
	string getResponsable() const { return responsable; }
	string getEstado() const { return estado; }
	NodoMantenimiento* getSiguiente() const { return siguiente; }
	
	// Setters
	void setSiguiente(NodoMantenimiento* nodo) { siguiente = nodo; }
};

// Tabla hash para almacenar mantenimientos
vector<NodoMantenimiento*> tablaHash(TAM_HASH, nullptr);

// Función hash
int hashFunc(int idEquipo) {
	return idEquipo % TAM_HASH;
}

// Agregar mantenimiento
void agregarMantenimiento(int id, string nombre, string fecha, string tipo, string resp, string est) {
	int indice = hashFunc(id);
	NodoMantenimiento* nuevo = new NodoMantenimiento(id, nombre, fecha, tipo, resp, est);
	
	if (tablaHash[indice] == nullptr) {
		tablaHash[indice] = nuevo;
	} else {
		NodoMantenimiento* actual = tablaHash[indice];
		while (actual->getSiguiente() != nullptr) {
			actual = actual->getSiguiente();
		}
		actual->setSiguiente(nuevo);
	}
	cout << "Mantenimiento agregado con éxito.\n";
}

// Mostrar mantenimientos
void mostrarMantenimientos() {
	for (int i = 0; i < TAM_HASH; i++) {
		NodoMantenimiento* actual = tablaHash[i];
		if (actual != nullptr) {
			cout << "Indice " << i << ":\n";
			while (actual != nullptr) {
				cout << "ID: " << actual->getIdEquipo() << ", Nombre: " << actual->getNombreEquipo()
					<< ", Fecha: " << actual->getFechaMantenimiento() << ", Tipo: " << actual->getTipoMantenimiento()
					<< ", Responsable: " << actual->getResponsable() << ", Estado: " << actual->getEstado() << endl;
				actual = actual->getSiguiente();
			}
		}
	}
}

// Eliminar mantenimiento
void eliminarMantenimiento(int id) {
	int indice = hashFunc(id);
	NodoMantenimiento* actual = tablaHash[indice];
	NodoMantenimiento* anterior = nullptr;
	
	while (actual != nullptr && actual->getIdEquipo() != id) {
		anterior = actual;
		actual = actual->getSiguiente();
	}
	
	if (actual == nullptr) {
		cout << "Mantenimiento no encontrado.\n";
		return;
	}
	
	if (anterior == nullptr) {
		tablaHash[indice] = actual->getSiguiente();
	} else {
		anterior->setSiguiente(actual->getSiguiente());
	}
	
	delete actual;
	cout << "Mantenimiento eliminado con éxito.\n";
}

// Ordenar mantenimientos por ID
void ordenarMantenimientos() {
	vector<NodoMantenimiento*> listaMantenimientos;
	
	for (int i = 0; i < TAM_HASH; i++) {
		NodoMantenimiento* actual = tablaHash[i];
		while (actual != nullptr) {
			listaMantenimientos.push_back(actual);
			actual = actual->getSiguiente();
		}
	}
	
	sort(listaMantenimientos.begin(), listaMantenimientos.end(), [](NodoMantenimiento* a, NodoMantenimiento* b) {
		return a->getIdEquipo() < b->getIdEquipo();
	});
	
	for (int i = 0; i < TAM_HASH; i++) {
		tablaHash[i] = nullptr;
	}
	
	for (NodoMantenimiento* nodo : listaMantenimientos) {
		int indice = hashFunc(nodo->getIdEquipo());
		nodo->setSiguiente(tablaHash[indice]);
		tablaHash[indice] = nodo;
	}
	
	cout << "Los mantenimientos se han ordenado exitosamente por ID.\n";
}

// Generar reporte
void generarReporte() {
	ofstream archivo("reporte_mantenimientos.txt");
	for (int i = 0; i < TAM_HASH; i++) {
		NodoMantenimiento* actual = tablaHash[i];
		while (actual != nullptr) {
			archivo << "ID: " << actual->getIdEquipo() << ", Nombre: " << actual->getNombreEquipo()
				<< ", Fecha: " << actual->getFechaMantenimiento() << ", Tipo: " << actual->getTipoMantenimiento()
				<< ", Responsable: " << actual->getResponsable() << ", Estado: " << actual->getEstado() << endl;
			actual = actual->getSiguiente();
		}
	}
	archivo.close();
	cout << "Reporte generado con éxito.\n";
}

// Mostrar el menú principal
void mostrarMenu() {
	int opcion, idEquipo;
	string nombreEquipo, fechaMantenimiento, tipoMantenimiento, responsable, estado;
	
	do {
		cout << "===============================\n";
		cout << "Gestión de Mantenimiento de Equipos Médicos\n";
		cout << "1. Agregar Mantenimiento\n";
		cout << "2. Eliminar Mantenimiento\n";
		cout << "3. Mostrar Mantenimientos\n";
		cout << "4. Ordenar Mantenimientos por ID\n";
		cout << "5. Generar Reporte\n";
		cout << "6. Salir\n";
		cout << "===============================\n";
		cout << "Escoja una opción (1 - 6): ";
		cin >> opcion;
		
		switch (opcion) {
		case 1:
			cout << "Ingrese el ID del equipo: ";
			cin >> idEquipo;
			cin.ignore();
			cout << "Ingrese el nombre del equipo: ";
			getline(cin, nombreEquipo);
			cout << "Ingrese la fecha de mantenimiento: ";
			getline(cin, fechaMantenimiento);
			cout << "Ingrese el tipo de mantenimiento: ";
			getline(cin, tipoMantenimiento);
			cout << "Ingrese el responsable: ";
			getline(cin, responsable);
			cout << "Ingrese el estado: ";
			getline(cin, estado);
			agregarMantenimiento(idEquipo, nombreEquipo, fechaMantenimiento, tipoMantenimiento, responsable, estado);
			break;
		case 2:
			cout << "Ingrese el ID del equipo a eliminar: ";
			cin >> idEquipo;
			eliminarMantenimiento(idEquipo);
			break;
		case 3:
			mostrarMantenimientos();
			break;
		case 4:
			ordenarMantenimientos();
			break;
		case 5:
			generarReporte();
			break;
		case 6:
			cout << "Saliendo del sistema...\n";
			break;
		default:
			cout << "Opción no válida.\n";
		}
	} while (opcion != 6);
}

#endif // MANTENIMIENTO_H
