#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

struct User {
  string username;
  string password;
};

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


struct HorariosMedicos{
  string medico;
  string fecha;
  string horarios;

};


struct Paciente {
  int id;
  string nombre;
  string apellido;
  string edad;
  string telefono;
  string dni;
  int numHistoriaClinica;
  bool SIS;

};

struct Cita {
  Paciente paciente;
  string descripcion;
  HorariosMedicos horariosMedicos;
  int id;
};
