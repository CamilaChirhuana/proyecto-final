#include <iostream>
#include <string>
#include <stack>
#include <map>
using namespace std;

struct Paciente{
    string nombre;
    int prioridad;
    string* suministrosAsignados;
    int cantidadSuministros;
    int capacidadSuministros;
    Paciente* siguiente;

    Paciente(string nombre, int prioridad) : nombre(nombre), prioridad(prioridad), cantidadSuministros(0), capacidadSuministros(2), siguiente(nullptr) {
        suministrosAsignados = new string[capacidadSuministros];
    }
    ~Paciente(){
        delete[] suministrosAsignados;
    }

    void agregarSuministro(const string& suministro){
        if(cantidadSuministros == capacidadSuministros){
            capacidadSuministros *= 2;
            string* nuevoArreglo = new string[capacidadSuministros];
            for(int i = 0; i < cantidadSuministros; i++){
                nuevoArreglo[i] = suministrosAsignados[i];
            }
            delete[] suministrosAsignados;
            suministrosAsignados = nuevoArreglo;
        }
        suministrosAsignados[cantidadSuministros++] = suministro;
    }
};


map<string, stack<string>> suministros;
Paciente* inicio = nullptr;

void agregarPaciente(string nombre, int prioridad){
    Paciente* nuevo = new Paciente(nombre, prioridad);

    if(inicio == nullptr || nuevo->prioridad < inicio->prioridad){
        nuevo->siguiente = inicio;
        inicio = nuevo;
    }else{
        Paciente* actual = inicio;
        while(actual->siguiente != nullptr && actual->siguiente->prioridad <= nuevo->prioridad){
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
    cout<<"Paciente agregado: "<<nombre<<" con prioridad "<<prioridad<<".\n";
    system("pause");
}

void asignarSuministro(string nombrePaciente, string tipoSuministro){
    if (inicio == nullptr){
        cout<<"No hay pacientes en espera.\n";
        system("pause");
        return;
    }

    Paciente* actual = inicio;
    while(actual != nullptr){
        if (actual->nombre == nombrePaciente){
            if(!suministros[tipoSuministro].empty()){
                string suministro = suministros[tipoSuministro].top();
                suministros[tipoSuministro].pop();
                actual->agregarSuministro(suministro);
                cout<<"Suministro \""<<suministro<<"\" asignado a "<<nombrePaciente<<".\n";
                system("pause");
            }else{
                cout<<"No hay suministros disponibles en la categoría "<<tipoSuministro<<".\n";
                system("pause");
            }
            return;
        }
        actual = actual->siguiente;
    }
    cout<<"Paciente no encontrado.\n";
    system("pause");
}

void atenderPaciente(){
    if (inicio == nullptr){
        cout<<"No hay pacientes en espera.\n";
        system("pause");
        return;
    }

    Paciente* atendido = inicio;
    inicio = inicio->siguiente;

    cout<<"\nAtendiendo a "<<atendido->nombre<<" con prioridad "<<atendido->prioridad<<".\n";
    if(atendido->cantidadSuministros > 0){
        cout<<"Suministros utilizados:\n";
        for(int i = 0; i < atendido->cantidadSuministros; i++){
            cout<<"- "<<atendido->suministrosAsignados[i]<<"\n";
            system("pause");
        }
    }else{
        cout<<"No hay suministros asignados a este paciente.\n";
        system("pause");
    }

    delete atendido;
}

void mostrarPacientes(){
    if(inicio == nullptr){
        cout << "No hay pacientes en espera.\n";
        system("pause");
        return;
    }

    Paciente* actual = inicio;
    cout<<"\nPacientes en espera:\n";
    while(actual != nullptr) {
        cout<<"Nombre: "<<actual->nombre<<", Prioridad: "<<actual->prioridad<<", Suministros asignados: "<< actual->cantidadSuministros<<"\n";
        actual = actual->siguiente;
        system("pause");
    }
}
void agregarSuministro(string tipo, string suministro){
    suministros[tipo].push(suministro);
    cout<<"Suministro agregado: "<<suministro<<" en la categoría "<<tipo<<".\n";
    system("pause");
}

void mostrarSuministros(){
    if(suministros.empty()){
        cout<<"No hay suministros disponibles.\n";
        system("pause");
        return;
    }
    cout<<"\nSuministros disponibles por categoría:\n";
    for(auto& categoria : suministros){
        cout<<"Categoría: "<<categoria.first<<"\n";
        stack<string> temp = categoria.second;
        while(!temp.empty()){
            cout<<"- "<<temp.top()<<"\n";
            temp.pop();
        }
    }
    system("pause");
}

void menuAtencionEmergencia(){
    cout<<"\n------- Sistema de Atencion de Emergencias ------\n";
    cout<<"1. Agregar paciente\n";
    cout<<"2. Administrar suministros\n";
    cout<<"3. Asignar suministro a paciente\n";
    cout<<"4. Atender paciente\n";
    cout<<"5. Mostrar pacientes en espera\n";
    cout<<"6. Salir\n";
    cout<<"Seleccione una opcion: ";
}

void agregarPacienteAE(){
    string nombre;
    int prioridad;
    cout<<"Ingrese el nombre del paciente: ";
    cin.ignore();
    getline(cin, nombre);
    cout<<"Ingrese la prioridad (1: Alta, 2: Media, 3: Baja): ";
    cin>>prioridad;
    agregarPaciente(nombre, prioridad);
    system("pause");
}

void asignarSuministroAE(){
    string nombrePaciente, tipoSuministro;
    cout<<"Ingrese el nombre del paciente: ";
    cin.ignore();
    getline(cin, nombrePaciente);
    cout<<"Ingrese la categoría del suministro (medicamento/equipo): ";
    getline(cin, tipoSuministro);
    asignarSuministro(nombrePaciente, tipoSuministro);
    system("pause");
}

void administrarSuministroAE(){
    int subOpcion;
    cout<<"\n1. Agregar suministro\n";
    cout<<"2. Mostrar suministros\n";
    cout<<"Seleccione una opción: ";
    cin>>subOpcion;
    cin.ignore();
    if(subOpcion == 1){
        string tipo, suministro;
        cout<<"Ingrese la categoría del suministro (medicamento/equipo): ";
        getline(cin, tipo);
        cout<<"Ingrese el nombre del suministro: ";
        getline(cin, suministro);
        agregarSuministro(tipo, suministro);
        system("pause");
    }else if(subOpcion == 2){
        mostrarSuministros();
        system("pause");
    }else{
        cout<<"Opción no válida.\n";
        system("pause");
    }

}