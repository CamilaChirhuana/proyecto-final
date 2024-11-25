#ifndef FUNCIONESCITA_H
#define FUNCIONESCITA_H

#include "NodoP2.h"
#include "ArbolAVL.h"
#include <iostream>
#include <fstream>
using namespace std;

const int TAM_HASH = 20;

int hashFunc(string persona) {
    for (int i = 0; i < persona.length(); i++) {
        persona[i] = toupper(persona[i]);
    }
    
    int acum = 0;

    for (char c : persona) {
        acum = (acum * 31 + c) % TAM_HASH; // Ajuste para prevenir desbordamiento
    }
    return acum;
}

string minuscula(string str) {
    for (char &c : str) {
        c = tolower(c);
    }
    return str;
}

void ordenarCitas(NodoCita **tablaHash) {
    for (int i = 0; i < TAM_HASH; i++) {
        // Solo ordenamos si hay más de un elemento en la lista
        if (tablaHash[i] != NULL) {
            NodoCita* actual;
            NodoCita* siguiente;
            bool intercambiado;
            
            do {
                intercambiado = false;
                actual = tablaHash[i];

                while (actual != NULL && actual->getSiguiente() != NULL) {
                    siguiente = actual->getSiguiente();

                    // Convertimos ambos nombres a minúsculas antes de compararlos
                    if (minuscula(actual->getPaciente()) > minuscula(siguiente->getPaciente())) {
                        // Intercambiamos los valores de los nodos
                        string tempPaciente = actual->getPaciente();
                        string tempDoctor = actual->getDoctor();
                        string tempConsultorio = actual->getConsultorio();
                        int tempNumeroCita = actual->getNumeroCita();

                        actual->setPaciente(siguiente->getPaciente());
                        actual->setDoctor(siguiente->getDoctor());
                        actual->setConsultorio(siguiente->getConsultorio());
                        actual->setNumeroCita(siguiente->getNumeroCita());

                        siguiente->setPaciente(tempPaciente);
                        siguiente->setDoctor(tempDoctor);
                        siguiente->setConsultorio(tempConsultorio);
                        siguiente->setNumeroCita(tempNumeroCita);

                        intercambiado = true;
                    }
                    actual = actual->getSiguiente();
                }
            } while (intercambiado);
        }
    }
}

void agregarCita(NodoCita **tablaHash, int numeroCita, string &paciente, string &doctor, string &consultorio, string horario) 
{
    int indice = hashFunc(paciente);
    NodoCita *nuevaCita = new NodoCita(numeroCita, paciente, doctor, consultorio, horario);
    nuevaCita->setSiguiente(tablaHash[indice]);
    tablaHash[indice] = nuevaCita;

    

    cout << "Cita agregada exitosamente.\n";
}

void eliminarCita(NodoCita **tablaHash, string &persona) 
{
    int indice = hashFunc(persona);
    NodoCita* actual = tablaHash[indice];
    NodoCita* anterior = NULL;

    while (actual != NULL && actual->getPaciente() != persona) 
    {
        anterior = actual;
        actual = actual->getSiguiente();
    }

    if (actual == NULL) 
    {
        cout << "Cita no encontrada.\n";
        return;
    }

    if (anterior == NULL) {
        tablaHash[indice] = actual->getSiguiente();
    } else {
        anterior->setSiguiente(actual->getSiguiente());
    }

    delete actual;
    cout << "Cita eliminada exitosamente.\n";
}

void mostrarCitas(NodoCita **tablaHash) {
    ordenarCitas(tablaHash);
    cout<<"----------------------\n";
    cout << "Lista de Citas:\n";
    cout<<"----------------------\n";
    for (int i = 0; i < TAM_HASH; i++) {
        NodoCita* actual = tablaHash[i];
        while (actual != NULL) {
            cout << "Numero de Cita: " << actual->getNumeroCita()
                 << endl<<"Paciente: " << actual->getPaciente()
                 << endl<<"Doctor: " << actual->getDoctor()
                 << endl<<"Consultorio: " << actual->getConsultorio() << "\n";
                 cout<<"----------------------\n";
            actual = actual->getSiguiente();
        }
    }
}

void generarReporte(NodoCita **tablaHash) {
    ofstream archivo("reporte_citas.txt");
    if (!archivo) {
        cout << "Error al crear el archivo.\n";
        return;
    }

    archivo << "Reporte de Citas:\n";
    for (int i = 0; i < TAM_HASH; i++) {
        NodoCita* actual = tablaHash[i];
        while (actual != NULL) {
            archivo <<endl<< "Número de Cita: " << actual->getNumeroCita() 
                    <<endl<< "Paciente: " << actual->getPaciente() 
                    <<endl<< "Doctor: " << actual->getDoctor() 
                    <<endl<< "Consultorio: " << actual->getConsultorio() << "\n"
                    <<endl;
                    cout<<"----------------------\n";
            actual = actual->getSiguiente();
        }
    }

    archivo.close();
    cout << "Reporte generado exitosamente.\n";
}

void modificarCita(NodoCita **tablaHash, int numeroCita, string paciente,string doctor, string consultorio) 
{
    int indice = hashFunc(paciente); 
    NodoCita *current = tablaHash[indice];
     while (current != NULL) 
    {
        if (current->getPaciente() == paciente) 
        {
            current->setNumeroCita(numeroCita);
            current->setDoctor(doctor);
            current->setConsultorio(consultorio);
            cout << "Modificacion exitosa.\n";
            return;
        }
        current = current->getSiguiente();
    }
    cout << "Persona no encontrada en la relacion de pacientes.\n";
}

void horarios(Arbol *arbolHorarios) {
    int opcionHorarios;
    string horarioInicio, horarioFin;
    
    do {
        cout << "\nMini menu de Horarios\n";
        cout << "=========================\n";
        cout << "1. Reprogramar cita\n";
        cout << "2. Buscar citas por rango de horarios\n";
        cout << "3. Mostrar horarios ocupados\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";  
        cin >> opcionHorarios;

        switch (opcionHorarios) {
            case 1:
                {
                    int numeroCita;
                    string nuevoHorario;
                    cout << "Ingrese el código de cita a reprogramar: ";
                    cin >> numeroCita;
                    cout << "Ingrese nuevo horario (hh:mm): ";
                    cin >> nuevoHorario;
                    reprogramarCita(arbolHorarios, numeroCita, nuevoHorario);  
                }
                break;
            case 2:
                {
                    cout << "Ingrese horario de inicio (hh:mm): ";
                    cin >> horarioInicio;
                    cout << "Ingrese horario de fin (hh:mm): ";
                    cin >> horarioFin;
                    buscarPorRangoHorarios(arbolHorarios, horarioInicio, horarioFin); 
                }
                break;
            case 3:
                mostrarHorariosOcupados(arbolHorarios); 
                break;
            case 4:
                cout << "Saliendo del mini menú de horarios...\n";
                break;
            default:
                cout << "Opción no válida. Por favor, intente de nuevo.\n";
                break;
        }
    } while (opcionHorarios != 4);
}
#endif 
