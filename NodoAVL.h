#include<iostream>
using namespace std;

struct Paciente {
    string nombre;  
    string doctor;  
    string consultorio;  
    string horario;
};

struct Nodo{
    Nodo *izq;
    Nodo *der;
    Nodo *padre;
    int clave;
    int FE;
    Paciente p;
};


Nodo *crearNodo(int cl,  string nombre, string doctor, string consultorio, string horario){
    Nodo *aux = new Nodo();
    aux->izq = NULL;
    aux->der = NULL;
    aux->padre = NULL;
    aux->clave = cl;
    aux->p.nombre = nombre;
    aux->p.doctor = doctor;
    aux->p.consultorio = consultorio;
    aux->p.horario = horario;
    return aux;
}