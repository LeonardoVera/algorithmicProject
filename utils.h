#include "structs.h"
#include "gotoxy.h"

vector<Cita> citas;
User currentUser;

// Caracteres especiales
const char wall = (char)179; // │
const char f = (char)196; // ─
const char topLeftCorner = (char)218; // ┌
const char topRightCorner = (char)191; // ┐
const char bottomLeftCorner = (char)192; // └
const char bottomRightCorner = (char)217; // ┘
const char arrow = (char)175; // »

//Vectores usados
vector<string> mainMenuOptions = { "Crear cita", "Buscar Cita", "Modificar cita", "Eliminar cita","Imprimir cita","Informacion del paciente", "Salir" };
vector<string> medicos = {"Jesus Andres Lujan Carrion", "Luis Bartolo Teran", "David Aldana Chavez", "Kevin Rhamses Bohorques","Marco Renato Castilla Huanca", "Salir"};
vector<string> horarios = {"06:30", "7:30","8:30", "9:30", "10:30", "Salir"};
vector<string> fecha = {"07/06/2024", "14/06/2024","21/06/2024", "28/06/2024", "05/07/2024", "Salir" };

// Validacion de datos
bool validateUser(User currentUser);

void inicioSesion();
void crearCuenta();
void login();
void crearCita(Paciente paciente);
void buscarCita();
void mostrarCita(int id);
void modificarCita();

void modificarMedicos (vector<string> medicos, int id);
void modificarFecha (vector<string> fecha, int id);
void modificarHorarios (vector<string> horarios, int id);

void eliminarCita();
void eliminar(int id);

void informacionPaciente(Paciente paciente);

void imprimirCita();
string getFechaActual();
void mainMenu(vector<string> menuOptions,Paciente paciente, User currentUser);
void eleccionMedicos(vector<string> medicos);
void eleccionFecha(vector<string> fecha);
void eleccionHorarios(vector<string> horarios);

Cita cita;

int generarID(int min, int max) {
    // Semilla basada en el tiempo actual
    int seed = chrono::system_clock::now().time_since_epoch().count();

    // Motor de generación de números aleatorios
    default_random_engine generator(seed);

    // Distribución uniforme de números enteros entre min y max
    uniform_int_distribution<unsigned int> distribution(min, max);

    // Generar y devolver el ID
    return distribution(generator);
}


// Definición de funciones
void modificarCita() {
  int id;
  system("cls");
  cout << "Ingrese el ID de la cita a modificar: ";
  cin >> id;

  for (int i = 0; i < citas.size(); ++i) {
    if (citas[i].id == id) {
      cout << "Cita encontrada" << endl;
      cout << "Datos actuales de la cita:" << endl;
      mostrarCita(id);
      
      bool repeat = true;

      while(repeat) {
        system("cls");
        cout << "Seleccione el dato a modificar:" << endl;
        cout << "0. Mostrar cita a modificar" << endl;
        cout << "1. Nombre del paciente" << endl;
        cout << "2. Apellido del paciente" << endl;
        cout << "3. Edad del paciente" << endl;
        cout << "4. DNI del paciente" << endl;
        cout << "5. Telefono del paciente" << endl;
        cout << "6. SIS del paciente" << endl;
        cout << "7. Motivo de consulta" << endl;
        cout << "8. Horario" << endl;
        cout << "9. Salir" << endl;
        cout << "=> ";
        int input;
        cin >> input;

        switch(input) {
          case 0:
            mostrarCita(id);
            break;
          case 1:
            cout << "Ingrese el nuevo nombre del paciente: ";
            cin.ignore();
            getline(cin, citas[i].paciente.nombre);
            break;
          case 2:
            cout << "Ingrese el nuevo apellido del paciente: ";
            getline(cin, citas[i].paciente.apellido);
            break;
          case 3:
            cout << "Ingrese la nueva edad del paciente: ";
            cin >> citas[i].paciente.edad;
            break;
          case 4:
            cout << "Ingrese el nuevo DNI del paciente: ";
            cin >> citas[i].paciente.dni;
            break;
          case 5:
            cout << "Ingrese el nuevo telefono del paciente: ";
            cin.ignore();
            getline(cin, citas[i].paciente.telefono);
            break;
          case 6:
            cout << "El paciente cuenta con SIS activo? (1/0) ";
            cin >> citas[i].paciente.SIS;
            break;
          case 7:
            cout << "Ingrese el nuevo motivo de consulta: ";
            cin.ignore();
            getline(cin, citas[i].descripcion);
            break;
          case 8:
            cout << "Elija sus horarios";
            system("pause");
            modificarMedicos(medicos, id);
            break;
          case 9:
            repeat = false;
            break;
          default:
            cout << "Opción no válida. Inténtalo de nuevo." << endl;
        }
      }
      return;
    }
  }
  cout << "Cita con ID " << id << " no encontrada." << endl;
}

bool validateUser(User currentUser) {
  ifstream file("./data/users.txt");
  string line;

  if(!file.is_open()) {
    cout << "No se pudo abrir el archivo." << endl;
    return false;
  }

  while(getline(file, line)) {
    size_t pos = line.find(":");
    if(pos != string::npos) {
      string user = line.substr(0, pos);
      string pass = line.substr(pos + 1);

      if(user == currentUser.username && pass == currentUser.password) {
        file.close();
        return true;
      }
    }
  }
  return false;
}
void inicioSesion(){
    int opcion;
    do {
        system("cls");
        gotoxy(50,2);
        cout << topLeftCorner << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f <<f << f << f << f << f << f << f << f << f <<f << f << f << f << f << f << f << f << f <<f << f << f << f << f << f << f << f << f <<f << f << f << f << f << f << topRightCorner << endl;
        gotoxy(50,3);
        cout << wall << "                                                   " << wall << endl; 
        gotoxy(50,4);
        cout << wall << "     GESTION DE CITAS - CLINICA COLITA DE RANA     " << wall << endl;
        gotoxy(50,5);
        cout << wall << "                                                   " << wall << endl; 
        gotoxy(50,6);
        cout << wall << "  1. INICIO DE SESION                              " << wall << endl; 
        gotoxy(50,7);
        cout << wall << "  2. CREACION DE CUENTA                            " << wall << endl; 
        gotoxy(50,8);
        cout << wall << "  3. SALIR                                         " << wall << endl;
        gotoxy(50,10);
        cout << bottomLeftCorner<< f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f <<f << f << f << f << f << f << f << f << f <<f << f << f << f << f << f << f << f << f <<f << f << f << f << f << f << f << f << f <<f << f << f << f << f << f << bottomRightCorner << endl;
        gotoxy(79,9);
        cout<<"                       " << wall << endl; 
        gotoxy(50,9); 
        cout << wall << "  Seleccione una opcion:   ";cin >> opcion;
        
        switch(opcion) {
            case 1:
                login();
                break;
            case 2:
                crearCuenta();
                break;
            case 3:
                system("cls");
                gotoxy(50, 10);
                color(3);
                cout << "Saliendo...";
                break;
            default:
                cout << "Opción no válida. Inténtalo de nuevo." << endl;
        }
        cout << endl;
    } while(opcion != 3);
}

void crearCuenta() {
    string nombreUsuario;
    string contrasena;
    string nombreArchivo = "./data/users.txt";

    system("cls");
    gotoxy(40, 5);
    cout << "Ingrese un nombre de usuario: ";
    cin.ignore();
    getline(cin, nombreUsuario);
    gotoxy(40, 7);
    cout << "Ingrese una contrasena: ";
    getline(cin, contrasena);
    
    ofstream archivo(nombreArchivo, ios::app);
    if (archivo.is_open()) {
        archivo << endl << nombreUsuario << ":" << contrasena << endl;
        archivo.close();
        cout << "Datos guardados correctamente" << endl;
    } else {
        cerr << "No se pudo guardar" << endl;
    }
    system("pause");
}

void guardarPaciente(const string& filename, const Paciente& paciente) {
    ofstream outfile;
    outfile.open(filename, ios_base::app); // Abrir el archivo en modo de añadir
    if (outfile.is_open()) {
        outfile << endl << paciente.id << "," << paciente.nombre << "," << paciente.apellido << "," << paciente.edad << "," << paciente.telefono << "," << paciente.dni;
        outfile.close();
    }
    else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
    }
}

std::vector<Paciente> cargarPaciente(const std::string filename) {
    std::vector<Paciente> pacientes;
    std::ifstream infile(filename);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            Paciente paciente;
            std::stringstream ss(line);
            std::string token;

            std::getline(ss, token, ',');
            paciente.id = stoul(token);

            std::getline(ss, token, ',');
            paciente.nombre = token;

            std::getline(ss, token, ',');
            paciente.apellido = token;

            std::getline(ss, token, ',');
            paciente.edad = token;

            std::getline(ss, token, ',');
            paciente.telefono = token;

            std::getline(ss, token, ',');
            paciente.dni = token;

            pacientes.push_back(paciente);
        }
        infile.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo para leer." << std::endl;
    }
    return pacientes;
}

Paciente buscarPorID(const std::vector<Paciente>& pacientes, unsigned int id) {
    for (const Paciente paciente : pacientes) {
        if (paciente.id == id) {
            return paciente;
        }
    }
    return { 0, "", "", 0 }; // Devuelve una persona vacía si no se encuentra
}


void crearPaciente() {
    Paciente paciente;
    paciente.id = generarID(1000, 9999);

    system("cls");

    gotoxy(50, 2);
    cout << "Ingrese el nombre: ";
    cin >> paciente.nombre;

    gotoxy(50, 3);
    cout << "Ingrese el apellido: ";
    cin >> paciente.apellido;

    gotoxy(50, 4);
    cout << "Ingrese la edad: ";
    cin >> paciente.edad;

    gotoxy(50, 5);
    cout << "Ingrese el telefono: ";
    cin >> paciente.telefono;

    gotoxy(50, 6);
    cout << "Ingrese el dni: ";
    cin >> paciente.dni;

    guardarPaciente("./data/pacientes.txt", paciente);

    gotoxy(50, 8);
    color(2);
    cout << "Paciente creado con ID: " << paciente.id << endl;
    color(7);
}

void listarPaciente(const vector<Paciente>& pacientes) {
    if (pacientes.empty()) {
        cout << "No hay personas registradas." << std::endl;
    }
    else {
        for (const Paciente& paciente : pacientes) {
            cout << "ID: " << paciente.id << endl;
            cout << "Nombre: " << paciente.nombre << endl;
            cout << "Apellidos: " << paciente.apellido << endl;
            cout << "Edad: " << paciente.edad << endl;
            cout << "Telefono: " << paciente.telefono << endl;
            cout << "DNI: " << paciente.dni << endl;
            cout << endl;
        }
    }
}

void buscarPaciente() {
    system("cls");
    string filename = "./data/pacientes.txt";
    unsigned int id;
    std::cout << "Ingrese el ID del paciente: ";
    std::cin >> id;

    std::vector<Paciente> pacientes = cargarPaciente(filename);
    Paciente pacienteEncontrado = buscarPorID(pacientes, id);

    if (pacienteEncontrado.id != 0) {
        mainMenu(mainMenuOptions, pacienteEncontrado, currentUser);
    }
    else {
        std::cout << "Persona no encontrada." << std::endl;
    }
}

void listaPacientes() {
    system("cls");
    string filename = "./data/pacientes.txt";
    std::vector<Paciente> pacientes = cargarPaciente(filename);
    listarPaciente(pacientes);
}

void opcionPaciente() {
    int opcion;
    do {
        system("cls");
        gotoxy(50, 2);
        cout << topLeftCorner << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << topRightCorner << endl;
        gotoxy(50, 3);
        cout << wall << "                                                   " << wall << endl;
        gotoxy(50, 4);
        cout << wall << "     GESTION DE CITAS - CLINICA COLITA DE RANA     " << wall << endl;
        gotoxy(50, 5);
        cout << wall << "                                                   " << wall << endl;
        gotoxy(50, 6);
        cout << wall << "  1. BUSCAR PACIENTE                               " << wall << endl;
        gotoxy(50, 7);
        cout << wall << "  2. CREAR PACIENTE                                " << wall << endl;
        gotoxy(50, 8);
        cout << wall << "  3. LISTAR PACIENTES                              " << wall << endl;
        gotoxy(50, 9);
        cout << wall << "  4. SALIR                                         " << wall << endl;
        gotoxy(50, 11);
        cout << bottomLeftCorner << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << f << bottomRightCorner << endl;
        gotoxy(79, 10);
        cout << "                       " << wall << endl;
        gotoxy(50, 10);
        cout << wall << "  Seleccione una opcion:   ";cin >> opcion;

        switch (opcion) {
        case 1:
            buscarPaciente();
            system("pause");
            break;

        case 2:
            crearPaciente();
            system("pause");
            break;
        case 3:
            listaPacientes();
            system("pause");
            break;

        case 4:
            system("cls");
            gotoxy(50, 10);
            color(3);
            cout << "Saliendo...";
            break;
        default:
            cout << "Opcion no valida. Intentalo de nuevo." << endl;
        }
        cout << endl;
    } while (opcion != 4);
}

void login() {
control:
  cin.ignore();
  system("cls");
  gotoxy(40, 5);
  cout << "Username: ";
  getline(cin, currentUser.username);
  gotoxy(40, 6);
  cout << "Password: ";
  getline(cin, currentUser.password);

  if(validateUser(currentUser)) {
    opcionPaciente();
  }else {
    gotoxy(40, 7);
    color(4);
    cout << "Usuario o contrasenha incorrectos." << endl;
    cin.ignore();
    color(7);
    system("pause");
    goto control;
  }
}

void mainMenu(const vector<string> menuOptions, const Paciente paciente, User currentUser) {
    bool repeat = true;
    int opt = 1; // Opción seleccionada
    const int numOptions = menuOptions.size();
    
    do {
        system("cls");
        gotoxy(92, 1);
        color(3);
        cout << "User: " << currentUser.username << endl;
        color(7);
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
                cout << arrow;
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
                cin.ignore(); // Limpia el búfer después de usar cin
                switch(opt) {
                    case 1:
                        crearCita(paciente);
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
                        system("cls");
                        informacionPaciente(paciente);
                        system("pause");
                        break;

                    case 7:
                        cout << "Salir" << endl;
                        repeat = false;
                        break;
                }
                break;
        }
    } while (repeat);
}

void informacionPaciente(Paciente paciente) {
    system("cls");
    cout << "ID: " << paciente.id << endl;
    cout << "Nombre: " << paciente.nombre << endl;
    cout << "Apellido: " << paciente.apellido << endl;
    cout << "Edad: " << paciente.edad << endl;
    cout << "Telefono: " << paciente.telefono << endl;
    cout << "DNI: " << paciente.dni << endl;
    system("pause");
}
void crearCita(Paciente paciente) {
    system("cls");
    gotoxy(50, 2);
    cout << "*****************************************************" << endl;
    cita.paciente.nombre = paciente.nombre;
    cita.paciente.apellido = paciente.apellido;
    cita.paciente.edad = paciente.edad;
    cita.paciente.dni = paciente.dni;
    cita.paciente.telefono = paciente.telefono;

    gotoxy(50, 3);
    cout << "El paciente cuenta con SIS activo? (1/0) ";
    cin >> cita.paciente.SIS;
    cin.ignore();

    gotoxy(50, 4);
    cout << "Motivo de consulta: ";
    getline(cin, cita.descripcion);

    gotoxy(50, 5);
    cout << "Asigne un ID a la cita: ";
    cin >> cita.id;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el búfer después de usar cin

    gotoxy(50,7);
    cout << "Mostrando seleccion de medicos y horarios..." << endl;
    system("pause");

    system("cls");
    eleccionMedicos(medicos);
}

void mostrarCita(int id){
  system("cls");
  bool encontrarID = false;
  for (int i = 0; i < citas.size(); ++i) {
    if (citas[i].id == id) {
      encontrarID = true;
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
      cout << "Hora programada: " << citas[i].horariosMedicos.horarios << endl;
      gotoxy(47, 11);
      cout << "Nombre del paciente: " << citas[i].paciente.nombre << " " << citas[i].paciente.apellido << endl;
      gotoxy(47, 12);
      cout << "Edad del paciente: " << citas[i].paciente.edad << endl;
      gotoxy(47, 13);
      cout << "El medico asignado es: " << citas[i].horariosMedicos.medico<< endl;
      gotoxy(47, 14);
      cout << "Telefono del paciente: " << citas[i].paciente.telefono << endl;
      gotoxy(47, 15);
      cout << "Descripcion de la cita: " << citas[i].descripcion << endl;
      gotoxy(47, 16);
      cout << "Fecha programada: " << citas[i].horariosMedicos.fecha<< endl;
      gotoxy(47, 17);

      gotoxy(85, 18);
      cout << "SIS Activo:";
      if (citas[i].paciente.SIS) {
        color(2);
        cout << "Si\n";
        color(7);
      } else {
        color(4);
        cout << "No\n";
        color(7);
      }
    }
  }
  if (!encontrarID) {
        gotoxy(45, 15);
        cout << "Cita con ID " << id << " no encontrada.\n";
    }
  system("pause");
}

void buscarCita(){
  system("cls");
  int id;
  gotoxy(45, 15);
  cout << "Ingrese el ID de la cita a buscar";
  gotoxy(whereX(), whereY());
  color(3);
  cout << "=>";
  color(7);
  cin >> id;
  mostrarCita(id);
  system("pause");
}

void eliminarCita() {
    system("cls");
    int id;
    gotoxy(45, 15);
    cout << "Ingrese el ID de la cita a eliminar: ";
    gotoxy(whereX(), whereY());
    cout << "=> ";
    cin >> id;
    eliminar(id);
    system("pause");
}

void eliminar(int id) {
    for (auto it = citas.begin(); it != citas.end(); ++it) {
        if (it->id == id) {
            citas.erase(it);  
            cout << "Cita con ID " << id << " eliminada.\n";
            return; 
        }
    }
    cout << "Cita con ID " << id << " no encontrada.\n";
    system("pause");
}

void verCitas() {
    system("cls");
    for (int i = 0; i < citas.size(); ++i) {
        cout << "Cita " << i + 1 << endl;
        cout << "Nombre: " << citas[i].paciente.nombre << " " << citas[i].paciente.apellido << endl;
        cout << "Telefono: " << citas[i].paciente.telefono << endl;
        cout << "Descripcion: " << citas[i].descripcion << endl;
        cout << "Fecha Programada: " << citas[i].horariosMedicos.fecha << endl;
        cout << "Hora Programada: " << citas[i].horariosMedicos.horarios << endl;
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
  ofstream archivo("./data/citas.txt", ios::app);
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
      archivo<< "Hora programada: " << citas[i].horariosMedicos.horarios<< endl;
      gotoxy(47, 11);
      archivo<< "Nombre: " << citas[i].paciente.nombre << " " << citas[i].paciente.apellido << endl;
      gotoxy(47, 12);
      archivo<< "Telefono: " << citas[i].paciente.telefono << endl;
      gotoxy(47, 13);
      archivo<< "Medico programado: " << citas[i].horariosMedicos.medico << endl;
      gotoxy(47, 14);
      archivo<< "Fecha programada: " << citas[i].horariosMedicos.fecha << endl;
      gotoxy(47, 15);
      archivo<< "Descripcion: " << citas[i].descripcion << endl;
      break;
    }
  }
  archivo.close();
  cout << "Cita impresa" << endl;
  system("pause");
}


void eleccionMedicos (vector<string> medicos) {
    bool repeat = true;
    int opt = 1; // Opción seleccionada
    const int numOptions = medicos.size();
    HorariosMedicos horariosMedicos;
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
        cout << "*              Seleccione el doctor                 *" << endl; 
        gotoxy(50, 7);
        cout << "*                                                   *" << endl; 
        gotoxy(50, 8);
        cout << "*****************************************************" << endl;

        for (int i = 0; i < numOptions; ++i) {
            if (i == opt - 1) {
                color(2);
                gotoxy(55, 10 + i);
                cout << arrow;
                color(2);
                gotoxy(57, 10 + i);
                cout << medicos[i] << endl;
                color(7);
            } else {
                gotoxy(57, 10 + i);
                cout << "   " << medicos[i] << endl;
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
                cita.horariosMedicos.medico = medicos[opt - 1];
                eleccionFecha(fecha);
                repeat = false;
                break;
        }
    } while (repeat);
}

void eleccionFecha (vector<string> fecha) {
    bool repeat = true;
    int opt = 1; // Opción seleccionada
    const int numOptions = fecha.size();
    
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
        cout << "*               Seleccione la fecha                 *" << endl; 
        gotoxy(50, 7);
        cout << "*                                                   *" << endl; 
        gotoxy(50, 8);
        cout << "*****************************************************" << endl;

        for (int i = 0; i < numOptions; ++i) {
            if (i == opt - 1) {
                color(2);
                gotoxy(55, 10 + i);
                cout << arrow;
                color(2);
                gotoxy(57, 10 + i);
                cout << fecha[i] << endl;
                color(7);
            } else {
                gotoxy(57, 10 + i);
                cout << "   " << fecha[i] << endl;
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
                cita.horariosMedicos.fecha = fecha[opt - 1];
                eleccionHorarios(horarios);
                repeat = false;
                break;
        }
    } while (repeat);
}

void eleccionHorarios (vector<string> horarios) {
    bool repeat = true;
    int opt = 1; // Opción seleccionada
    const int numOptions = horarios.size();
    
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
        cout << "*               Seleccione su horario               *" << endl; 
        gotoxy(50, 7);
        cout << "*                                                   *" << endl; 
        gotoxy(50, 8);
        cout << "*****************************************************" << endl;

        for (int i = 0; i < numOptions; ++i) {
            if (i == opt - 1) {
                color(2);
                gotoxy(55, 10 + i);
                cout << arrow;
                color(2);
                gotoxy(57, 10 + i);
                cout << horarios[i] << endl;
                color(7);
            } else {
                gotoxy(57, 10 + i);
                cout << "   " << horarios[i] << endl;
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
                cita.horariosMedicos.horarios = horarios[opt - 1];
                repeat = false;
                break;
        }
    } while (repeat);
  
  system("cls");
  citas.push_back(cita);
    gotoxy(50, 10);
    cout << "Cita creada exitosamente." << endl;
    system("pause");
}

//-----------------------------------------------------------------------------------------------------------

void modificarMedicos (vector<string> medicos, int id) {
    bool repeat = true;
    int opt = 1; // Opción seleccionada
    const int numOptions = medicos.size();
    HorariosMedicos horariosMedicos;
    for (int i = 0; i < citas.size(); ++i) {
      if (citas[i].id == id) {
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
          cout << "*              Seleccione el doctor                 *" << endl; 
          gotoxy(50, 7);
          cout << "*                                                   *" << endl; 
          gotoxy(50, 8);
          cout << "*****************************************************" << endl;

          for (int i = 0; i < numOptions; ++i) {
            if (i == opt - 1) {
                color(2);
                gotoxy(55, 10 + i);
                cout << arrow;
                color(2);
                gotoxy(57, 10 + i);
                cout << medicos[i] << endl;
                color(7);
            } else {
                gotoxy(57, 10 + i);
                cout << "   " << medicos[i] << endl;
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
                        citas[i].horariosMedicos.medico = medicos[0];
                        modificarFecha (fecha, id);
                        repeat = false;
                        break;
                    case 2:
                        citas[i].horariosMedicos.medico = medicos[1];
                        modificarFecha (fecha, id);
                        repeat = false;
                        break;
                    case 3:
                        citas[i].horariosMedicos.medico = medicos[2];
                        modificarFecha (fecha, id);
                        repeat = false;
                        break;
                    case 4:
                        citas[i].horariosMedicos.medico = medicos[3];
                        modificarFecha (fecha, id);
                        repeat = false;
                        break;
                    case 5:
                        citas[i].horariosMedicos.medico = medicos[4];
                        modificarFecha (fecha, id);
                        repeat = false;
                        break;
                    case 6:
                        cout << "Salir" << endl;
                        repeat = false;
                        break;
            } break;
          }
        } while (repeat);
      }
    }
}



void modificarFecha (vector<string> fecha, int id) {
    bool repeat = true;
    int opt = 1; // Opción seleccionada
    const int numOptions = fecha.size();
    HorariosMedicos horariosMedicos;
    for (int i = 0; i < citas.size(); ++i) {
      if (citas[i].id == id) {
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
          cout << "*              Seleccione la fecha                  *" << endl; 
          gotoxy(50, 7);
          cout << "*                                                   *" << endl; 
          gotoxy(50, 8);
          cout << "*****************************************************" << endl;

          for (int i = 0; i < numOptions; ++i) {
            if (i == opt - 1) {
                color(2);
                gotoxy(55, 10 + i);
                cout << arrow;
                color(2);
                gotoxy(57, 10 + i);
                cout << fecha[i] << endl;
                color(7);
            } else {
                gotoxy(57, 10 + i);
                cout << "   " << fecha[i] << endl;
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
                        citas[i].horariosMedicos.fecha = fecha[0];
                        modificarHorarios (horarios, id);
                        repeat = false;
                        break;
                    case 2:
                        citas[i].horariosMedicos.fecha = fecha[1];
                        modificarHorarios (horarios, id);
                        repeat = false;
                        break;
                    case 3:
                        citas[i].horariosMedicos.fecha = fecha[2];
                        modificarHorarios (horarios, id);
                        repeat = false;
                        break;
                    case 4:
                        citas[i].horariosMedicos.fecha = fecha[3];
                        modificarHorarios (horarios, id);
                        repeat = false;
                        break;
                    case 5:
                        citas[i].horariosMedicos.fecha = fecha[4];
                        modificarHorarios (horarios, id);
                        repeat = false;
                        break;
                    case 6:
                        cout << "Salir" << endl;
                        repeat = false;
                        break;
            } break;
          }
        } while (repeat);
      }
    }
}

void modificarHorarios (vector<string> horarios, int id) {
    bool repeat = true;
    int opt = 1; // Opción seleccionada
    const int numOptions = horarios.size();
    HorariosMedicos horariosMedicos;
    for (int i = 0; i < citas.size(); ++i) {
      if (citas[i].id == id) {
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
          cout << "*              Seleccione el horario                *" << endl; 
          gotoxy(50, 7);
          cout << "*                                                   *" << endl; 
          gotoxy(50, 8);
          cout << "*****************************************************" << endl;

          for (int i = 0; i < numOptions; ++i) {
            if (i == opt - 1) {
                color(2);
                gotoxy(55, 10 + i);
                cout << arrow;
                color(2);
                gotoxy(57, 10 + i);
                cout << horarios[i] << endl;
                color(7);
            } else {
                gotoxy(57, 10 + i);
                cout << "   " << horarios[i] << endl;
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
                        citas[i].horariosMedicos.horarios = horarios[0];
                        repeat = false;
                        break;
                    case 2:
                        citas[i].horariosMedicos.horarios = horarios[1];
                        repeat = false;
                        break;
                    case 3:
                        citas[i].horariosMedicos.horarios = horarios[2];
                        repeat = false;
                        break;
                    case 4:
                        citas[i].horariosMedicos.horarios = horarios[3];
                        repeat = false;
                        break;
                    case 5:
                        citas[i].horariosMedicos.horarios = horarios[4];
                        repeat = false;
                        break;
                    case 6:
                        cout << "Salir" << endl;
                        repeat = false;
                        break;
            } 
          }
        } while (repeat);
      }
    }
    system("cls");
    gotoxy(50, 10);
    cout << "Cita modificada exitosamente." << endl;
    system("pause");
}
