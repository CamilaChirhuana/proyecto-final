#include "FuncionesInventario.h"
#include <iostream>
#include <limits> // Agregado para usar std::numeric_limits

void mostrarMenu() {
    std::cout << "\n--- Inventario de Farmacia ---\n";
    std::cout << "1. Agregar Medicamento\n";
    std::cout << "2. Actualizar Cantidad\n";
    std::cout << "3. Mostrar Inventario\n";
    std::cout << "4. Verificar Stock Bajo\n";
    std::cout << "5. Generar Reporte\n";
    std::cout << "6. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

int main() {
    Inventario inventario;
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;

        if (std::cin.fail()) { // Validar entrada no numérica
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer
            std::cout << "Entrada inválida. Intente de nuevo.\n";
            continue;
        }

        int id, cantidad, limite;
        std::string nombre, archivo;

        switch (opcion) {
            case 1:
                std::cout << "Ingrese ID del medicamento: ";
                std::cin >> id;
                std::cout << "Ingrese nombre del medicamento: ";
                std::cin.ignore(); // Limpiar buffer
                std::getline(std::cin, nombre); // Para leer nombres con espacios
                std::cout << "Ingrese cantidad: ";
                std::cin >> cantidad;
                inventario.agregarMedicamento(id, nombre, cantidad);
                break;
            case 2:
                std::cout << "Ingrese ID del medicamento a actualizar: ";
                std::cin >> id;
                std::cout << "Ingrese nueva cantidad: ";
                std::cin >> cantidad;
                inventario.actualizarCantidad(id, cantidad);
                break;
            case 3:
                inventario.mostrarInventario();
                break;
            case 4:
                std::cout << "Ingrese el límite mínimo de stock: ";
                std::cin >> limite;
                inventario.verificarStock(limite);
                break;
            case 5:
                std::cout << "Ingrese el nombre del archivo para el reporte: ";
                std::cin >> archivo;
                inventario.generarReporte(archivo);
                break;
            case 6:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opción no válida.\n";
                break;
        }
    } while (opcion != 6);

    return 0;
}
