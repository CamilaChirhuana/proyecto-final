#ifndef ARBOLAVL_H
#define ARBOLAVL_H
#include<iostream>
#include "NodoAVL.h"
#include "FunP2.h"

using namespace std;

struct Arbol{
    Nodo *root;
};

Arbol *crearArbol(){
    Arbol *aux = new Arbol();
    aux->root = NULL;
    return aux;
}

int alturaNodo(Nodo *nodo){
    if(nodo != NULL){
        int hIzq = alturaNodo(nodo->izq);
        int hDer = alturaNodo(nodo->der);
        if(hIzq>hDer){
            return hIzq + 1;
        } else {
            return hDer + 1;
        }
    } else {
        return 0;
    }
}

int factorEquilibrio(Nodo *nodo){
    return alturaNodo(nodo->der) - alturaNodo(nodo->izq);
}

void rotacionIzquierda(Arbol *arbol, Nodo *nodo){
    Nodo *aux, *p, *q;
    aux = nodo->der;
    q = aux->izq;
    p = nodo->padre;

    nodo->der = q;
    aux->izq = nodo;

    if(q!=NULL){
        q->padre = nodo;
    }
    nodo->padre = aux;
    if(p==NULL){ //Si el nodo es la root
        arbol->root = aux;
        aux->padre = NULL;
    }
    else {
        aux->padre = p;
        if(aux->clave < p->clave){
            p->izq = aux;
        } else {
            p->padre = aux;
        }
    }
}

void rotacionDerecha(Arbol *arbol, Nodo *nodo){
    Nodo *aux, *p, *q;
    aux = nodo->izq;
    q = aux->der;
    p = nodo->padre;

    nodo->izq = q;
    aux->der = nodo;

    if (q!=NULL) {
        q->padre = nodo;
    }
    nodo->padre = aux;
    if(p==NULL){
        arbol->root = aux;
        aux->padre = NULL;
    }
    else {
        aux->padre = p;
        if(aux->clave < p->clave){
            p->izq = aux;
        } else {
            p->padre = aux;
        }
    }
}

void rotacionDobleIzquierda(Arbol *arbol, Nodo *nodo){
    rotacionDerecha(arbol, nodo->der);
    rotacionIzquierda(arbol, nodo);
}

void rotacionDobleDerecha(Arbol *arbol, Nodo *nodo){
    rotacionIzquierda(arbol, nodo->izq);
    rotacionDerecha(arbol, nodo);
}

void balancear(Arbol *arbol, Nodo *nodo){
    Nodo *padre;
    if(nodo!=NULL){
        padre = nodo->padre;
        nodo->FE = factorEquilibrio(nodo);
        if(nodo->FE > 1){ //Desbalanceo derecho
            if(factorEquilibrio(nodo->der)<0){ //desbalanceo doble
                rotacionDobleIzquierda(arbol, nodo);
            } else {
                rotacionIzquierda(arbol, nodo);
            }
        } else if(nodo->FE < -1){ //desbalanceo izquierdo
            if(factorEquilibrio(nodo->izq) > 0){ //doble desbalanceo
                rotacionDobleDerecha(arbol, nodo);
            } else {
                rotacionDerecha(arbol, nodo);
            }
        }
        balancear(arbol, padre);
    }
}

void insertarNodo(Arbol *arbol, Nodo *nodo){
    Nodo *aux, *padre;
    if(arbol->root == NULL){
        arbol->root = nodo;
    } else {
        aux=arbol->root;
        while(aux!=NULL){
            padre = aux;
            if(nodo->clave<aux->clave){
                aux=aux->izq;
            } else {
                aux=aux->der;
            }
        }
        nodo->padre = padre;
        if(nodo->clave<padre->clave){
            padre->izq = nodo;
        } else {
            padre->der = nodo;
        }
        balancear(arbol, padre);
    }
}

void mostrarNodos(Nodo *nodo){
    if(nodo != NULL){
        cout << "Cita Numero: " << nodo->clave << endl;
        cout << "Paciente: " << nodo->p.nombre << endl;
        cout << "Doctor: " << nodo->p.doctor << endl;
        cout << "Consultorio: " << nodo->p.consultorio << endl;
        cout << "Horario: " << nodo->p.horario << endl;
        cout << "=========================" << endl;
        mostrarNodos(nodo->izq);
        mostrarNodos(nodo->der);
    }
}

void mostrarArbol(Arbol *arbol){
    if(arbol->root==NULL){
        cout<<"No hay elementos que mostrar";
    } else {
        mostrarNodos(arbol->root);
    }
}

Nodo *buscarNodo(Arbol *arbol, int clave){
    Nodo *aux = NULL;
    if(arbol->root!=NULL) {
        aux = arbol->root;
        while (aux!=NULL && aux->clave!=clave) {
            if(clave < aux->clave){
                aux = aux->izq;
            } else{
                aux = aux->der;
            }
        }
    }
    return aux;
}

Nodo *hijoNoNull(Nodo *nodo){
    if(nodo->izq != NULL){
        return nodo->izq;
    }
    return nodo->der;
}

void eliminarNodo(Arbol *arbol, int clave){
    Nodo *aux = buscarNodo(arbol,clave);
    Nodo *aux2;
    Nodo *padre;
    if(aux!=NULL){
        padre = aux->padre;
        if(aux->izq==NULL && aux->der == NULL){
            if(padre!=NULL){
                if(aux->clave < padre->clave){
                    padre->izq = NULL;
                } else{
                    padre->der = NULL;
                }
            } else{
                arbol->root = NULL;
            }
            delete aux;
        } else if(aux->der==NULL || aux->izq == NULL){
            if(padre!=NULL){
                if(aux->clave < padre->clave){
                    padre->izq = hijoNoNull(aux);
                    padre->izq->padre = padre;
                } else{
                    padre->der = hijoNoNull(aux);
                    padre->der->padre = padre;
                }
            } else{
                arbol->root = hijoNoNull(aux);
                arbol->root->padre = NULL;
            }
            delete aux;
        } else{
            aux2 = aux->izq;
            while(aux2->der != NULL){
                aux2 = aux2->der;
            }
            
            padre = aux2->padre;

            if(aux2->clave < padre->clave){
                padre->izq = aux2->izq;
            } else{
                padre->der = aux2->izq;
            }
            aux->clave = aux2->clave;
            delete aux2;
        }
        balancear(arbol,padre);
    }
}

void insertarHorario(Arbol *arbol, int numeroCita, string nombre, string doctor, string consultorio, string horario) {
    Nodo *nuevoNodo = crearNodo(numeroCita, nombre, doctor, consultorio, horario);
    insertarNodo(arbol, nuevoNodo);
}

void buscarPorRangoNodos(Nodo *nodo, string inicio, string fin)
{
    if (nodo != NULL)
    {
        if (nodo->p.horario >= inicio)
        {
            buscarPorRangoNodos(nodo->izq, inicio, fin);
        }
        if (nodo->p.horario >= inicio && nodo->p.horario <= fin)
        {
            cout << nodo->clave << " - Horario: " << nodo->p.horario << endl;
        }
        if (nodo->p.horario <= fin)
        {
            buscarPorRangoNodos(nodo->der, inicio, fin);
        }
    }
}

void reprogramarCita(Arbol *arbol, int numeroCita, string nuevoHorario) {
    Nodo *nodo = buscarNodo(arbol, numeroCita);
    if (nodo != NULL) {
        cout << "Reprogramando cita del paciente " << nodo->p.nombre << ".\n";
        nodo->p.horario = nuevoHorario;
        cout << "Horario actualizado: " << nuevoHorario << endl;
    } else {
        cout << "Cita no encontrada en el árbol AVL.\n";
    }
}

void buscarPorRangoHorarios(Arbol *arbol, string inicio, string fin)
{
    cout << "Citas entre " << inicio << " y " << fin << ":\n";
    buscarPorRangoNodos(arbol->root, inicio, fin);
}

void mostrarHorariosOcupados(Arbol *arbol)
{
    cout << "Horarios ocupados:\n";
    mostrarNodos(arbol->root);  
}
#endif 