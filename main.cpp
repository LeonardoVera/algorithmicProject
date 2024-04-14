#include <iostream>
#include <string>
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

struct Cita {
  string nombre;
  string descripcion;
  Fecha fecha;
};

// Declaración de funciones

// Funciones para imprimir las opciones del menu principal y manejar las opciones
void printOptions();
void manageOpts(int &opt);
void printMenu(int &opt);

// Funciones para la creacion, visualizacion, modificacion y eliminacion de citas
void crearCita(){}
void verCitas(){}
void modificarCita(){}
void eliminarCita(){}


int main(int argc, char *argv[]) {
  int opt;
  do {
    printMenu(opt);
  } while(opt!=5);
  return 0;
}

// Funcion para imprimer el menu principal en pantalla
void printMenu(int &opt) {
  system("cls");
  printOptions();
  cin >> opt;
  manageOpts(opt);
}

// Funcion para imprimir las opciones del menu
void printOptions() {
  cout << "1. Crear cita" << endl;
  cout << "2. Ver citas" << endl;
  cout << "3. Modificar cita" << endl;
  cout << "4. Eliminar cita" << endl;
  cout << "5. Salir" << endl;
  cout << "Seleccione una opcion: ";
}

// Funcion para manejar las opciones del menu
void manageOpts(int &opt) {
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
      break;
    default:
      cout << "Opcion no valida" << endl;
      break;
  }
}
