#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>
#include "gotoxy.h"

using namespace std;

// Estructuras anidadas necesarias para la creacion de una nueva cita
struct Hora {
  int hora;
  int minuto;
  int segundo;
};

struct Fecha {
  int dia;
  int mes;
  int anio;
  Hora hora;
};

struct Paciente {
  string nombre;
  string apellido;
  string telefono;
};

struct Cita {
  Paciente paciente;
  string descripcion;
  Fecha fecha;
};

// Opciones de los menus
vector<string> mainMenuOptions = {"Crear cita", "Ver citas", "Modificar cita", "Eliminar cita", "Salir"};

// Declaración de funciones
// Funciones para imprimir las opciones del menu principal y manejar las opciones
void menuTemplate(vector<string> menuOptions);

// Funciones para la creacion, visualizacion, modificacion y eliminacion de citas
void crearCita(){}
void verCitas(){}
void modificarCita(){}
void eliminarCita(){}


int main(int argc, char *argv[]) {
  ocultarCursor();
  menuTemplate(mainMenuOptions);
  return 0;
}
void menuTemplate(vector<string> menuOptions) {
    bool repeat = true;
    int opt = 1; // Opción seleccionada
    const int numOptions = menuOptions.size();
    
    do {
        system("cls");
        for (int i = 0; i < numOptions; ++i) {
            if (i == opt - 1) {
                color(2);
                gotoxy(55, 5 + i);
                cout << "=>";
                color(2);
                gotoxy(57, 5 + i);
                cout << menuOptions[i] << endl;
                color(7);
            } else {
                gotoxy(57, 5 + i);
                cout << "   " << menuOptions[i] << endl;
            }
        }
        
        // Capturar la entrada del teclado
        char input = _getch();
        switch(input) {
            case 72: // Flecha arriba
                opt = (opt == 1) ? numOptions : opt - 1;
                break;
            case 80: // Flecha abajo
                opt = (opt == numOptions) ? 1 : opt + 1;
                break;
            case 13: // Tecla Enter
                switch(opt) {
                    case 1:
                        crearCita();
                        break;
                    case 2:
                        verCitas();
                        break;
                    case 3:
                        modificarCita();
                        break;
                    case 4:
                        eliminarCita();
                        break;
                    case 5:
                        cout << "Salir" << endl;
                        repeat = false;
                        break;
                }
                break;
        }
    } while (repeat);
}

// TODO: Implementar estuctura de datos para almacenar el nombre del paciente
/*
void crearCita() {
    Cita cita;
    system("cls");

    cout << "Nombre: ";
    cin.ignore();
    getline(cin, cita.nombre);

    cout << "Descripcion: ";
    getline(cin, cita.descripcion);

    cout << "Fecha (dd/mm/yyyy): ";
    cin >> cita.fecha.dia >> cita.fecha.mes >> cita.fecha.anio;
    cin.ignore();

    cout << "Hora (hh:mm:ss): ";
    cin >> cita.fecha.hora.hora >> cita.fecha.hora.minuto >> cita.fecha.hora.segundo;
    cin.ignore();

    cout << "Cita creada" << endl;
    system("pause");
}
*/
