#ifndef NUTRICION_H
#define NUTRICION_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Paciente {
	string nombre;
	int edad;
	double peso, talla;
	string condicion_medica;
	bool alergia_lactosa, alergia_nueces, alergia_mariscos;
	string dieta[7]; // Plan de comidas para cada día de la semana (lunes a domingo)
	Paciente* siguiente; // Nodo siguiente en la lista enlazada
};

// Funciones del sistema
Paciente* agregarPaciente(Paciente* cabeza);
void asignarDieta(Paciente* paciente);
void imprimirDieta(const Paciente* paciente);
void guardarEnArchivo(const Paciente* cabeza);
void menu();

int main() {
	Paciente* listaPacientes = cargarDesdeArchivo();
	menu();
	int opcion;
	do {
		cout << "\nOpciones: \n1. Agregar Paciente \n2. Imprimir Dieta \n3. Guardar y Salir\nSeleccione una opción: ";
		cin >> opcion;
		cin.ignore();
		switch (opcion) {
		case 1:
			listaPacientes = agregarPaciente(listaPacientes);
			break;
		case 2:
			imprimirDieta(listaPacientes);
			break;
		case 3:
			guardarEnArchivo(listaPacientes);
			cout << "Guardando datos y cerrando el programa.\n";
			break;
		default:
			cout << "Opción no válida.\n";
		}
	} while (opcion != 3);
	return 0;
}

Paciente* agregarPaciente(Paciente* cabeza) {
	Paciente* nuevoPaciente = new Paciente;
	cout << "Nombre del paciente: ";
	getline(cin, nuevoPaciente->nombre);
	cout << "Edad: ";
	cin >> nuevoPaciente->edad;
	cout << "Peso (kg): ";
	cin >> nuevoPaciente->peso;
	cout << "Talla (m): ";
	cin >> nuevoPaciente->talla;
	cout << "Condición médica (diabetes, hipertensión, anemia): ";
	cin >> nuevoPaciente->condicion_medica;
	cout << "¿Alergia a la lactosa? (1-Sí, 0-No): ";
	cin >> nuevoPaciente->alergia_lactosa;
	cout << "¿Alergia a nueces? (1-Sí, 0-No): ";
	cin >> nuevoPaciente->alergia_nueces;
	cout << "¿Alergia a mariscos? (1-Sí, 0-No): ";
	cin >> nuevoPaciente->alergia_mariscos;
	
	nuevoPaciente->siguiente = cabeza;
	asignarDieta(nuevoPaciente);
	
	return nuevoPaciente;
}

void asignarDieta(Paciente* paciente) {
	string dietaDiabetes[7] = {"Ensalada de verduras", "Pescado a la plancha", "Pollo a la parrilla", "Sopa de verduras", "Quinua con vegetales", "Pavo asado", "Salmón a la plancha"};
	string dietaHipertension[7] = {"Ensalada sin sal", "Pescado al vapor", "Pollo sin piel", "Verduras cocidas", "Arroz integral", "Pavo sin sal", "Frutas frescas"};
	string dietaAnemia[7] = {"Hígado de res", "Espinacas con huevo", "Pollo con verduras", "Lentejas", "Carne magra", "Quinua con carne", "Espinacas y remolacha"};
	
	if (paciente->condicion_medica == "diabetes") {
		for (int i = 0; i < 7; i++) paciente->dieta[i] = dietaDiabetes[i];
	} else if (paciente->condicion_medica == "hipertension") {
		for (int i = 0; i < 7; i++) paciente->dieta[i] = dietaHipertension[i];
	} else if (paciente->condicion_medica == "anemia") {
		for (int i = 0; i < 7; i++) paciente->dieta[i] = dietaAnemia[i];
	}
	
	for (int i = 0; i < 7; i++) {
		if (paciente->alergia_lactosa && paciente->dieta[i].find("leche") != string::npos) {
			paciente->dieta[i].replace(paciente->dieta[i].find("leche"), 5, "leche de almendras");
		}
		if (paciente->alergia_nueces && paciente->dieta[i].find("nueces") != string::npos) {
			paciente->dieta[i].replace(paciente->dieta[i].find("nueces"), 6, "semillas de girasol");
		}
		if (paciente->alergia_mariscos && paciente->dieta[i].find("mariscos") != string::npos) {
			paciente->dieta[i].replace(paciente->dieta[i].find("mariscos"), 8, "pollo");
		}
	}
}

void imprimirDieta(const Paciente* paciente) {
	while (paciente != nullptr) {
		cout << "\nDieta semanal para: " << paciente->nombre << endl;
		for (int i = 0; i < 7; i++) {
			cout << "Día " << i + 1 << ": " << paciente->dieta[i] << endl;
		}
		paciente = paciente->siguiente;
	}
}

void guardarEnArchivo(const Paciente* cabeza) {
	ofstream archivo("pacientes.txt");
	while (cabeza != nullptr) {
		archivo << cabeza->nombre << "," << cabeza->edad << "," << cabeza->peso << "," << cabeza->talla << "," << cabeza->condicion_medica << ","
			<< cabeza->alergia_lactosa << "," << cabeza->alergia_nueces << "," << cabeza->alergia_mariscos << endl;
		for (int i = 0; i < 7; i++) {
			archivo << cabeza->dieta[i] << endl;
		}
		cabeza = cabeza->siguiente;
	}
	archivo.close();
}



void menu() {
	cout << "=== Sistema de Nutrición para Hospital ===" << endl;
}
#endif
