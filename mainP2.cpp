#include <iostream>
#include "Admi.h"
#include "MenuAtencionEmergencia.h"
#include "Nutricion.h"
#include "Farmacia.h"
using namespace std;

int main()
{
    int opcion;
    do
    {
        cout<<"\tHospital\t\n";
        cout<<"==========================\n";
        cout<<"1. Admision\n";
        cout<<"2. Atencion de emergencias\n";
        cout<<"3. Farmacia\n";
        cout<<"4. Mantenimiento de equipos medicos\n";
        cout<<"5. Nutricion\n";
        cout<<"6. Salir\n\n";

        cout<<"Ingrese un area: ";
        cin>>opcion;

        system("cls");

        switch (opcion)
        {
            case 1:
                admision();
                system("pause");
                system("cls");
                break;
            
            case 2:
                MenuAtencionEmergencia();
                system("pause");
                system("cls");
                break;
            case 3:
                Farmacia();
                system("pause");
                system("cls");
                break;
            case 4:
                break;
            case 5:
                break;
        }
    } while (opcion != 6);
    
}
