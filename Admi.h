#include "NodoP2.h"
#include "FunP2.h"
#include "ArbolAVL.h"
#include <iostream>

using namespace std;

void admision() {
    NodoCita **tablaHash;
    Arbol *arbolHorarios = crearArbol();
    tablaHash = new NodoCita*[TAM_HASH];
    for (int i = 0; i < TAM_HASH; i++) 
    {
        tablaHash[i] = NULL;
    }
    int opcion, numeroCita;
    string paciente, doctor, consultorio;
    string horario;

    do {
        cout << "\nGestion de Citas\n";
        cout<<"=========================\n";
        cout << "1. Agregar cita\n";
        cout << "2. Modificar cita\n";
        cout << "3. Eliminar cita\n";
        cout << "4. Mostrar citas\n";
        cout << "5. Generar reporte\n";
        cout << "6. Horarios\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        system("cls");

        switch (opcion) {
            case 1:
                cout << "Ingrese el numero de cita: ";
                cin >> numeroCita;
                cout<<"Ingrese el nombre del paciente: ";
                cin>>paciente;
                cout << "Ingrese el nombre del doctor: ";
                cin.ignore();
                getline(cin, doctor);
                cout << "Ingrese el consultorio: ";
                getline(cin, consultorio);
                cout << "Ingrese el horario de la cita (hh:mm): ";  // Pedimos el horario
                cin >> horario;
                agregarCita(tablaHash, numeroCita, paciente, doctor, consultorio, horario);
                insertarHorario(arbolHorarios, numeroCita, paciente, doctor, consultorio, horario);
                system("pause");
                system("cls");
                break;
            case 2:
                cout << "Ingrese el nombre del paciente a modificar: "; cin>>paciente;
                cout << "Ingrese nueva cita: "; cin >> numeroCita;
                cout << "Ingrese nuevo doctor: ";
                cin.ignore();
                getline(cin, doctor);
                cout << "Ingrese nuevo consultorio: ";
                getline(cin, consultorio);
                modificarCita(tablaHash, numeroCita, paciente, doctor, consultorio);
                system("pause");
                system("cls");
                break;
            case 3:
                cout << "Ingrese el paciente a eliminar: ";
                cin >> paciente;
                eliminarCita(tablaHash, paciente);
                system("pause");
                system("cls");
                break;
            case 4:
                mostrarCitas(tablaHash);
                system("pause");
                system("cls");
                break;
            case 5:
                generarReporte(tablaHash);
                system("pause");
                system("cls");
                break;
            case 6:
                horarios(arbolHorarios);
                system("pause");
                system("cls");
                break;
            case 7:
                cout<<"Salida exitosa\n";
            default:
                cout << "Opcion invalida. Por favor, intente de nuevo.\n";
                break;
        }
    } while (opcion != 7);


    for (int i = 0; i < TAM_HASH; i++) 
    {
        NodoCita *temp = tablaHash[i];
        while (temp != NULL) {
            NodoCita *siguiente = temp->getSiguiente();
            delete temp;
            temp = siguiente;
        }
    }
    delete[] tablaHash;
    delete arbolHorarios;
}
