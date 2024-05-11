#include <iostream>
#include <string>
#include <vector>
#include <set>
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

/*
struct historialClinico {
  set<string> enfermedades;
  Fecha fecha;
  int id;
};
*/

struct Paciente {
  string nombre;
  string apellido;
  string telefono;
  int dni;
  // TODO: Agregar historial clinico
  int numHistoriaClinica;
  bool SIS; // TODO

};

struct Cita {
  Paciente paciente;
  string descripcion;
  Fecha fecha;
  int id;
};
