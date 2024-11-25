#include <string>

struct Paciente {
    std::string nombre;
    int edad;
    double peso, talla;
    std::string condicion_medica;
    bool alergia_lactosa, alergia_nueces, alergia_mariscos;
    std::string dieta[7];
    Paciente* siguiente;
};

Paciente* agregarPaciente(Paciente* cabeza);
void asignarDieta(Paciente* paciente);
void imprimirYGuardarDietas(const Paciente* cabeza);
#include <iostream>
#include <fstream>
#include <string>
#include "nutricion.h"

Paciente* agregarPaciente(Paciente* cabeza) {
    Paciente* nuevoPaciente = new Paciente;
    std::cout << "Nombre del paciente: ";
    std::getline(std::cin, nuevoPaciente->nombre);
    std::cout << "Edad: ";
    std::cin >> nuevoPaciente->edad;
    std::cout << "Peso (kg): ";
    std::cin >> nuevoPaciente->peso;
    std::cout << "Talla (m): ";
    std::cin >> nuevoPaciente->talla;
    std::cout << "Condición médica (diabetes, hipertensión, anemia): ";
    std::cin >> nuevoPaciente->condicion_medica;
    std::cout << "¿Alergia a la lactosa? (1-Sí, 0-No): ";
    std::cin >> nuevoPaciente->alergia_lactosa;
    std::cout << "¿Alergia a nueces? (1-Sí, 0-No): ";
    std::cin >> nuevoPaciente->alergia_nueces;
    std::cout << "¿Alergia a mariscos? (1-Sí, 0-No): ";
    std::cin >> nuevoPaciente->alergia_mariscos;

    nuevoPaciente->siguiente = cabeza;
    asignarDieta(nuevoPaciente);

    return nuevoPaciente;
}

