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

