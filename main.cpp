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
  int dni;
};

struct Cita {
  Paciente paciente;
  string descripcion;
  Fecha fecha;
  int id;
};

// Opciones de los menus
vector<string> mainMenuOptions = {"Crear cita", "Buscar Cita", "Modificar cita", "Eliminar cita","Imprimir cita", "Salir"};

vector<Cita> citas;

// Declaración de funciones
// Funciones para imprimir las opciones del menu principal y manejar las opciones
void mainMenu(vector<string> menuOptions);

// Funciones para la creacion, visualizacion, modificacion y eliminacion de citas
void crearCita();
void verCitas();
void modificarCita(){}
void eliminarCita(){}
void buscarCita();
void mostrarCita(int id);
void imprimirCita();
string getFechaActual();


int main() {
  ocultarCursor();
  mainMenu(mainMenuOptions);
  return 0;
}

void mainMenu(vector<string> menuOptions) {
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
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el búfer después de usar cin
                switch(opt) {
                    case 1:
                        crearCita();
                        break;
                    case 2:
                        buscarCita();
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

    gotoxy(50, 2);
    cout << "*****************************************************" << endl;
    gotoxy(50, 3);
    cout << "Nombre del paciente: ";
    getline(cin, cita.paciente.nombre);

    gotoxy(50, 4);
    cout << "Apellido del paciente: ";
    getline(cin, cita.paciente.apellido);

    gotoxy(50, 5);
    cout << "Telefono del paciente: ";
    getline(cin, cita.paciente.telefono);

    gotoxy(50, 6);
    cout << "Descripcion del suceso: ";
    getline(cin, cita.descripcion);

    gotoxy(50, 7);
    cout << "Fecha a programar (dd/mm/yyyy): ";
    cin >> cita.fecha.dia >> cita.fecha.mes >> cita.fecha.anio;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el búfer después de usar cin

    gotoxy(50, 8);
    cout << "Hora (hh:mm): ";
    cin >> cita.fecha.hora.hora >> cita.fecha.hora.minuto;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el búfer después de usar cin

    gotoxy(50, 9);
    cout << "Asigne un ID a la cita: ";
    cin >> cita.id;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el búfer después de usar cin

    citas.push_back(cita);
    gotoxy(50, 10);
    cout << "Cita creada exitosamente." << endl;
    system("pause");
}

void mostrarCita(int id){
  system("cls");
  for (int i = 0; i < citas.size(); ++i) {
    if (citas[i].id == id) {
      gotoxy(60, 3);
      color(3);
      cout << "TICKET DE CITA\n";
      color(7);
      gotoxy(40, 4);
      cout << "---------------------------------------------------------------------"<< endl;
      gotoxy(47, 5);
      cout << "Centro de salud Colita de Rana\n";
      gotoxy(47, 6);
      cout << "RUC: 20131257750\n";
      gotoxy(47, 7);
      cout << "Av. San Borja Sur 123 Lima, Peru\n";
      gotoxy(47, 8);
      cout << "Telefono: 123456789\n";
      gotoxy(40, 9);
      cout << "---------------------------------------------------------------------"<< endl;
      gotoxy(47, 10);
      cout << "Hora programada: " << citas[i].fecha.hora.hora << ":" << citas[i].fecha.hora.minuto << endl;
      gotoxy(47, 11);
      cout << "Nombre: " << citas[i].paciente.nombre << " " << citas[i].paciente.apellido << endl;
      gotoxy(47, 12);
      cout << "Telefono: " << citas[i].paciente.telefono << endl;
      gotoxy(47, 13);
      cout << "Descripcion: " << citas[i].descripcion << endl;
      gotoxy(47, 14);
      cout << "Fecha programada: " << citas[i].fecha.dia << "/" << citas[i].fecha.mes << "/" << citas[i].fecha.anio << endl;
      gotoxy(47, 15);
    }
  }
  system("pause");
}

void buscarCita(){
  system("cls");
  int id;
  cout << "Ingrese el ID de la cita a buscar: ";
  cin >> id;
  mostrarCita(id);
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
      gotoxy(60, 3);
      color(3);
      archivo << "TICKET DE CITA\n";
      color(7);
      gotoxy(40, 4);
      archivo << "---------------------------------------------------------------------"<< endl;
      gotoxy(47, 5);
      archivo << "Centro de salud Colita de Rana\n";
      gotoxy(47, 6);
      archivo<< "RUC: 20131257750\n";
      gotoxy(47, 7);
      archivo << "Av. San Borja Sur 123 Lima, Peru\n";
      gotoxy(47, 8);
      archivo<< "Telefono: 123456789\n";
      gotoxy(40, 9);
      archivo<< "---------------------------------------------------------------------"<< endl;
      gotoxy(47, 10);
      archivo<< "Hora programada: " << citas[i].fecha.hora.hora << ":" << citas[i].fecha.hora.minuto << endl;
      gotoxy(47, 11);
      archivo<< "Nombre: " << citas[i].paciente.nombre << " " << citas[i].paciente.apellido << endl;
      gotoxy(47, 12);
      archivo<< "Telefono: " << citas[i].paciente.telefono << endl;
      gotoxy(47, 13);
      archivo<< "Descripcion: " << citas[i].descripcion << endl;
      gotoxy(47, 14);
      archivo<< "Fecha programada: " << citas[i].fecha.dia << "/" << citas[i].fecha.mes << "/" << citas[i].fecha.anio << endl;
      break;
    }
  }
  archivo.close();
  cout << "Cita impresa" << endl;
  system("pause");
}
