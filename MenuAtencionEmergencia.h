#include <iostream>
#include "AtencionEmergencia.h"
using namespace std;

void MenuAtencionEmergencia(){

    int opcion;

    do {
        menuAtencionEmergencia();
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarPacienteAE();
                break;
            case 2:
                administrarSuministroAE();

                break;
            case 3:
                asignarSuministroAE();
                break;
            case 4:
                atenderPaciente();
                break;
            case 5:
                mostrarPacientes();
                break;
            case 6:
                cout<<"Saliendo del sistema...\n";
                break;
            default:
                cout<<"Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 6);

}