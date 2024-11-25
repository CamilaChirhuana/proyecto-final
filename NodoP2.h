#ifndef NODOPOO_H
#define NODOPOO_H
#include <iostream>
using namespace std;

class NodoCita {
protected:
    int numeroCita;
    string paciente;
    string doctor;
    string consultorio;
    string horario;
    NodoCita *siguiente;

public:
    // Constructor por defecto
    NodoCita() {}

    // Constructor con parámetros
    NodoCita(int num, string pac, string doc, string cons, string hor) {
        numeroCita = num;
        paciente = pac;
        doctor = doc;
        consultorio = cons;
        horario = hor;
        siguiente = NULL;
    }
    NodoCita(int num, string pac, string doc, string cons, string hor, NodoCita *sig) {
        numeroCita = num;
        paciente = pac;
        doctor = doc;
        consultorio = cons;
        horario = hor;
        siguiente = sig;
    }

    // Destructor
    ~NodoCita() {}

    // Getters y setters
    int getNumeroCita() { return numeroCita; }
    void setNumeroCita(int num) { numeroCita = num; }

    string getPaciente() { return paciente; }
    void setPaciente(const string &pac) { paciente = pac; }

    string getDoctor() { return doctor; }
    void setDoctor(const string &doc) { doctor = doc; }

    string getConsultorio() { return consultorio; }
    void setConsultorio(const string &cons) { consultorio = cons; }

    string getHorario() { return horario; }
    void setsetHorario(const string &hor) { horario = hor; }

    NodoCita *getSiguiente() { return siguiente; }
    void setSiguiente(NodoCita *sig) { siguiente = sig; }
};
#endif 