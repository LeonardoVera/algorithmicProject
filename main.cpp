#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <conio.h>
#include <windows.h>
#include "gotoxy.h"

using namespace std;

// Estructuras anidadas necesarias para la creacion de una nueva cita
struct Hora {
  int hora;
  int minuto;
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
  int id;
};

// Opciones de los menus
vector<string> mainMenuOptions = {"Crear cita", "Ver citas", "Modificar cita", "Eliminar cita","Imprimir cita", "Salir"};

vector<Cita> citas;

// Declaración de funciones
// Funciones para imprimir las opciones del menu principal y manejar las opciones
void menuTemplate(vector<string> menuOptions);

// Funciones para la creacion, visualizacion, modificacion y eliminacion de citas
void crearCita();
void verCitas();
void modificarCita(){}
void eliminarCita(){}
void imprimirCita();
string getFechaActual();


int main() {
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
        gotoxy(50, 2);
        cout << "*****************************************************" << endl;
        gotoxy(50, 3);
        cout << "*                                                   *" << endl; 
        gotoxy(50, 4);
        cout << "*     GESTION DE CITAS - CLINICA COLITA DE RANA     *" << endl;
        gotoxy(50, 5);
        cout << "*                                                   *" << endl; 
        gotoxy(50, 6);
        cout << "*  RUC: 20131257750                                 *" << endl; 
        gotoxy(50, 7);
        cout << "*  SEDE: San Borja - Lima                           *" << endl; 
        gotoxy(50, 8);
        cout << "*****************************************************" << endl;

        for (int i = 0; i < numOptions; ++i) {
            if (i == opt - 1) {
                color(2);
                gotoxy(55, 10 + i);
                cout << "=>";
                color(2);
                gotoxy(57, 10 + i);
                cout << menuOptions[i] << endl;
                color(7);
            } else {
                gotoxy(57, 10 + i);
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
                        imprimirCita();
                        break;
                    case 6:
                        cout << "Salir" << endl;
                        repeat = false;
                        break;
                }
                break;
        }
    } while (repeat);
}

// Definición de funciones
void crearCita() {
    Cita cita;
    system("cls");

    cout << "Nombre del paciente: ";
    cin.ignore();
    getline(cin, cita.paciente.nombre);

    cout << "Apellido del paciente: ";
    getline(cin, cita.paciente.apellido);

    cout << "Telefono del paciente: ";
    getline(cin, cita.paciente.telefono);

    cout << "Descripcion del suceso: ";
    getline(cin, cita.descripcion);

    cout << "Fecha a programar (dd/mm/yyyy): ";
    cin >> cita.fecha.dia >> cita.fecha.mes >> cita.fecha.anio;
    cin.ignore();

    cout << "Hora (hh:mm): ";
    cin >> cita.fecha.hora.hora >> cita.fecha.hora.minuto;
    cin.ignore();

    cout << "Asigne un ID a la cita: ";
    cin >> cita.id;

    citas.push_back(cita);
    cout << "Cita creada" << endl;
    system("pause");
}

void verCitas() {
    system("cls");
    for (int i = 0; i < citas.size(); ++i) {
        cout << "Cita " << i + 1 << endl;
        cout << "Nombre: " << citas[i].paciente.nombre << " " << citas[i].paciente.apellido << endl;
        cout << "Telefono: " << citas[i].paciente.telefono << endl;
        cout << "Descripcion: " << citas[i].descripcion << endl;
        cout << "Fecha Programada: " << citas[i].fecha.dia << "/" << citas[i].fecha.mes << "/" << citas[i].fecha.anio << endl;
        cout << "Hora Programada: " << citas[i].fecha.hora.hora << ":" << citas[i].fecha.hora.minuto << endl;
        cout << "ID: " << citas[i].id << endl;
        cout << endl;
    }
    system("pause");
}

string getFechaActual() {
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);

    stringstream ss;

    ss << put_time(localtime(&now_c), "%Y-%m-%d %X");
    return ss.str();
}

void imprimirCita(){
  ofstream archivo("citas.txt", ios::app);
  system("cls");
  int id;
  cout << "Ingrese el ID de la cita a imprimir: ";
  cin >> id;

  for (int i = 0; i < citas.size(); ++i) {
    if (citas[i].id == id) {
      archivo << "Cita " << i + 1 << endl;
      archivo << "Nombre: " << citas[i].paciente.nombre << " " << citas[i].paciente.apellido << endl;
      archivo << "Telefono: " << citas[i].paciente.telefono << endl;
      archivo << "Descripcion: " << citas[i].descripcion << endl;
      archivo << "Fecha programada: " << citas[i].fecha.dia << "/" << citas[i].fecha.mes << "/" << citas[i].fecha.anio << endl;
      archivo << "Hora programada: " << citas[i].fecha.hora.hora << ":" << citas[i].fecha.hora.minuto << endl;
      archivo << "Fecha de impresion: " << getFechaActual() << endl;
      archivo << endl;
    }
  }
  archivo.close();
  cout << "Cita impresa" << endl;
}
