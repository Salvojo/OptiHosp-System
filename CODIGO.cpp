#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <chrono>
#include <iomanip>
using namespace std;

struct paciente {
    string nombre;
    int dni;
    int edad;
    string diagnostico;
    int tipoCama;
};

struct Nodo {
    paciente info;
    Nodo* siguiente;
    Nodo* anterior;
};


void cambio_color(int x) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void gotoxy(int x, int y) {
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void mostrarCursor(bool visible) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hCon, &cci);
    cci.bVisible = visible;
    SetConsoleCursorInfo(hCon, &cci);
}

void bannerInicio();
void ingresoMedico();
void insertarInicio(Nodo*& lista, const paciente& p);
void insertarFinal(Nodo*& lista, const paciente& p);
void insertarAntesDe(Nodo*& lista, int dniReferencia, const paciente& p);
void insertarDespuesDe(Nodo*& lista, int dniReferencia, const paciente& p);
void buscarPaciente(Nodo* lista);
void mostrarLista(Nodo* lista);
bool eliminarPorDNI(Nodo*& lista, int dni);
void liberar(Nodo*& );
void menu();

// funciones auxiliares
Nodo* crearNodo(Nodo*& lista);
void gotoxy(int x, int y);
void cambio_color(int x);
void mostrarCursor(bool visible);
string clavesita();

int main() {
    Nodo* lista = nullptr;
    bannerInicio();
    ingresoMedico();
    menu();
    return 0;
}

// ================= MENÚ PRINCIPAL =================
void menu() {
    int opcion;
    do {
        system("cls");
        cambio_color(11);
        cout << "\n\t=======================================" << endl;
        cout << "\t   GESTIÓN DE CAMAS HOSPITALARIAS" << endl;
        cout << "\t=======================================\n" << endl;
        cambio_color(15);
        cout << "\t1. Insertar paciente" << endl;
        cout << "\t2. Buscar paciente" << endl;
        cout << "\t3. Mostrar lista de pacientes" << endl;
        cout << "\t4. Eliminar paciente por DNI" << endl;
        cout << "\t5. Salir" << endl;
        cout << "\n\tSeleccione una opción: ";
        cin >> opcion;

        system("cls");

        switch (opcion) {
            case 1: {
    int subop;

    do {
        cambio_color(14);
        cout << "\n===== SUBMENÚ DE INSERCIÓN =====" << endl;
        cambio_color(15);
        cout << "1. Insertar al inicio un paciente" << endl;
        cout << "2. Insertar al final un paciente" << endl;
        cout << "3. Insertar antes de un paciente" << endl;
        cout << "4. Insertar después de un paciente" << endl;
        cout << "5. Volver al menú principal" << endl;
        cout << "\nSeleccione una opción: ";
        cin >> subop;
        cin.ignore();

        switch (subop) {
            case 1: {
                paciente p;
                cout << "\n--- Datos del nuevo paciente ---" << endl;
                cout << "Nombre: "; getline(cin, p.nombre);
                cout << "DNI: "; cin >> p.dni;
                cout << "Edad: "; cin >> p.edad;
                cin.ignore();
                cout << "Diagnóstico: "; getline(cin, p.diagnostico);

                do {
                    cout << "\nTipo de cama [1=General, 2=UCI, 3=UCIN]: ";
                    cin >> p.tipoCama;
                } while (p.tipoCama < 1 || p.tipoCama > 3);

                insertarInicio(lista, p);
                cambio_color(10);
                cout << "\nPaciente insertado al inicio correctamente.\n";
                break;
            }

            case 2: {
                paciente p;
                cout << "\n--- Datos del nuevo paciente ---" << endl;
                cout << "Nombre: "; getline(cin, p.nombre);
                cout << "DNI: "; cin >> p.dni;
                cout << "Edad: "; cin >> p.edad;
                cin.ignore();
                cout << "Diagnóstico: "; getline(cin, p.diagnostico);

                do {
                    cout << "\nTipo de cama [1=General, 2=UCI, 3=UCIN]: ";
                    cin >> p.tipoCama;
                } while (p.tipoCama < 1 || p.tipoCama > 3);

                insertarFinal(lista, p);
                cambio_color(10);
                cout << "\nPaciente insertado al final correctamente.\n";
                break;
            }

            case 3: {
                paciente p;
                int dniRef;
                cout << "\n--- Datos del nuevo paciente ---" << endl;
                cout << "Nombre: "; getline(cin, p.nombre);
                cout << "DNI: "; cin >> p.dni;
                cout << "Edad: "; cin >> p.edad;
                cin.ignore();
                cout << "Diagnóstico: "; getline(cin, p.diagnostico);

                do {
                    cout << "\nTipo de cama [1=General, 2=UCI, 3=UCIN]: ";
                    cin >> p.tipoCama;
                } while (p.tipoCama < 1 || p.tipoCama > 3);

                cout << "\nDNI de referencia: "; cin >> dniRef;
                insertarAntesDe(lista, dniRef, p);
                cambio_color(10);
                cout << "\nPaciente insertado antes del DNI de referencia.\n";
                break;
            }

            case 4: {
                paciente p;
                int dniRef;
                cout << "\n--- Datos del nuevo paciente ---" << endl;
                cout << "Nombre: "; getline(cin, p.nombre);
                cout << "DNI: "; cin >> p.dni;
                cout << "Edad: "; cin >> p.edad;
                cin.ignore();
                cout << "Diagnóstico: "; getline(cin, p.diagnostico);

                do {
                    cout << "\nTipo de cama [1=General, 2=UCI, 3=UCIN]: ";
                    cin >> p.tipoCama;
                } while (p.tipoCama < 1 || p.tipoCama > 3);

                cout << "\nDNI de referencia: "; cin >> dniRef;
                insertarDespuesDe(lista, dniRef, p);
                cambio_color(10);
                cout << "\nPaciente insertado después del DNI de referencia.\n";
                break;
            }

            case 5:
                system("cls");
                break;

            default:
                cambio_color(12);
                cout << "\nOpción inválida. Intente nuevamente.\n";
                cambio_color(7);
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }

        if (subop != 5) {
            cambio_color(7);
            cout << "\nPresione una tecla para continuar...";
            getch();
            system("cls");
        }

    } while (subop != 5);
    break;
}

            case 2: {
                buscarPaciente(lista);
                cout << "\nPresione una tecla para continuar...";
                getch();
                break;
            }

            case 3:
                mostrarLista(lista);
                cout << "\nPresione una tecla para continuar...";
                getch();
                break;

            case 4: {
                int dni;
                cout << "Ingrese el DNI del paciente a eliminar: ";
                cin >> dni;
                if (eliminarPorDNI(lista, dni)) {
                    cambio_color(10);
                    cout << "\nPaciente eliminado correctamente.\n";
                } else {
                    cambio_color(12);
                    cout << "\nNo se encontró el paciente.\n";
                }
                cambio_color(7);
                cout << "\nPresione una tecla para continuar...";
                getch();
                break;
            }

            case 5:
                system("cls");
                cambio_color(14);
                cout << "\nSaliendo del sistema...\n";
                this_thread::sleep_for(chrono::milliseconds(800));
                break;

            default:
                cambio_color(12);
                cout << "\nOpción inválida. Intente nuevamente.\n";
                cambio_color(7);
                this_thread::sleep_for(chrono::milliseconds(1000));
        }

    } while (opcion != 5);
}

//funciones
void insertarInicio(Nodo*& lista, const paciente& p) {
    Nodo* nuevo = new Nodo();
    nuevo->info = p;
    
    if (lista == NULL) {
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
        lista = nuevo;
    } else {

        Nodo* ultimo = lista->anterior;  
        nuevo->siguiente = lista;  
        nuevo->anterior = ultimo;    
        lista->anterior = nuevo;   
        ultimo->siguiente = nuevo;   
        lista = nuevo;
    }
    string mensaje="Paciente insertado al inicio correctamente.\n"
     for(char c : mensaje) {
        cout << c << flush;
        sleep_for(chrono::milliseconds(40));
    }
    
}

void insertarFinal(Nodo*& lista, const paciente& p){//preferia mejor ponerlo persona en lugar de 'p', pero asi esta...
    Nodo* nuevo=crearNodo(p);
    if(!lista){
        lista=nuevo;
        nuevo->siguiente=nuevo;
        nuevo->anterior=nuevo;
        //lo mismo que nuevo->siguiente=nuevo->anterior=nuevo;
    }else{
        Nodo* ultimo = lista->anterior;
        nuevo->siguiente=lista;
        nuevo->anterior=ultimo;
        ultimo->siguiente=nuevo;
        lista->anterior=nuevo;
    }

    cout<<"Paciente guardado al final de la lista";

}
Nodo* crearNodo(Nodo*&lista, paciente persona){
    Nodo* nuevo= new Nodo();
    nuevo->info=persona;
    nuevo->siguiente=nullptr;
    nuevo->anterior=nullptr;
    return nuevo;
}

void insertarAntesDe(Nodo*& lista, int dniReferencia, const paciente& p){
        if (lista == NULL) {
                cout << "La lista está vacía. No se puede insertar antes de un paciente inexistente.\n";
                return;
        }
        Nodo* actual = lista;
        do {
                if (actual->info.dni == dniReferencia) {
                Nodo* nuevo = new Nodo;
                nuevo->info = p;
                // se enlaza al nuevo nodo
                nuevo->siguiente = actual;
                nuevo->anterior = actual->anterior;
        
                actual->anterior->siguiente = nuevo;
                actual->anterior = nuevo;
                if (actual == lista) {
                        lista = nuevo;
                }
                cout << "Paciente insertado correctamente antes del DNI " << dniReferencia << ".\n";
                return;
                }
                actual = actual->siguiente;
        } while (actual != lista);
        cout << "No se encontró un paciente con el DNI de referencia.\n";
}

void insertarDespuesDe(Nodo*& lista, int dniReferencia, const paciente& p) {
    if (lista == NULL) {
        cout << "La lista está vacía. No se puede insertar después de un paciente inexistente.\n";
        return;}

    Nodo* actual = lista;
    do {
        if (actual->info.dni == dniReferencia) {
            Nodo* nuevo = new Nodo;
            nuevo->info = p;

            // se enlaza al nuevo nodo
            nuevo->siguiente = actual->siguiente;
            nuevo->anterior = actual;

            actual->siguiente->anterior = nuevo;
            actual->siguiente = nuevo;

            cout << "Paciente insertado correctamente después del DNI " << dniReferencia << ".\n";
            return;
        }
        actual = actual->siguiente;
    } while (actual != lista);

    cout << "No se encontró un paciente con el DNI de referencia.\n";
}

void buscarPaciente(Nodo* lista) {
    system("cls");

    if (lista == NULL) {
        cambio_color(12);
        cout << "\nNo hay pacientes registrados.\n";
        cambio_color(7);
        return;
    }

    int dniBuscado;
    cout << "Ingrese el DNI del paciente a buscar: ";
    cin >> dniBuscado;

    Nodo* actual = lista;
    bool encontrado = false;

    do {
        if (actual->info.dni == dniBuscado) {
            encontrado = true;
            cambio_color(10);
            cout << "\nPaciente encontrado:\n";
            cambio_color(7);

            cout << "Nombre      : " << actual->info.nombre << endl;
            cout << "DNI         : " << actual->info.dni << endl;
            cout << "Edad        : " << actual->info.edad << endl;
            cout << "Diagnóstico : " << actual->info.diagnostico << endl;

            cout << "Tipo de cama: ";
            if (actual->info.tipoCama == 1) cout << "General\n";
            else if (actual->info.tipoCama == 2) cout << "UCI\n";
            else cout << "UCIN\n";

            cambio_color(7);
            return;
        }
        actual = actual->siguiente;
    } while (actual != lista);

    if (!encontrado) {
        cambio_color(12);
        cout << "\nNo se encontró ningún paciente con ese DNI.\n";
        cambio_color(7);
    }
}
void mostrarLista(Nodo* lista) {
    system("cls");
    if (lista ==NULL) {
        cambio_color(12);
        cout << "\nNo hay pacientes registrados.\n";
        cambio_color(7);
        return;
    }

    cambio_color(11);
    cout << "================ LISTA DE PACIENTES ================\n\n";
    cambio_color(7);

    cout << left;
    cout << setw(15) << "NOMBRE"
         << setw(12) << "DNI"
         << setw(6)  << "EDAD"
         << setw(15) << "CAMA"
         << "DIAGNOSTICO\n";

    cout << "-------------------------------------------------------------\n";

    Nodo* actual = lista;
    do {
        cout << setw(15) << actual->info.nombre
             << setw(12) << actual->info.dni
             << setw(6)  << actual->info.edad;

        if (actual->info.tipoCama == 1)      cout << setw(15) << "General";
        else if (actual->info.tipoCama == 2) cout << setw(15) << "UCI";
        else                                 cout << setw(15) << "UCIN";

        cout << actual->info.diagnostico << "\n";

        actual = actual->siguiente;
    } while (actual != lista);

    cout << "\n-------------------------------------------------------------\n";
}

bool eliminarPorDNI(Nodo*& lista, int dni){}




void bannerInicio() {
    system("cls");
    string titulo = "SISTEMA DE GESTION HOSPITALARIA";
    string subtitulo = "    Hospital Nacional";
    
    cambio_color(11);
    gotoxy(25, 5);
    cout << char(201);
    for (int i = 0; i < 40; i++) cout << char(205);
    cout << char(187);

    for (int i = 6; i <= 11; i++) {
        gotoxy(25, i); cout << char(186);
        gotoxy(66, i); cout << char(186);
    }

    gotoxy(25, 12);
    cout << char(200);
    for (int i = 0; i < 40; i++) cout << char(205);
    cout << char(188);

    cambio_color(14);
    gotoxy(30, 7);
    for (char c : titulo) {
        cout << c;
        Sleep(80);
    }

    gotoxy(33, 9);
    for (char c : subtitulo) {
        cout << c;
        Sleep(50);
    }

    cambio_color(7);
    gotoxy(35, 11);
    cout << "Cargando sistema";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(700);
    }
    Sleep(600);

    system("cls");
    cambio_color(15);
}


string clavesita() {
    string contra;
    char caractersito;
    while (true) {
        caractersito = getch();
        if (caractersito == 13) break;
        else if (caractersito == 8) {
            if (!contra.empty()) {
                contra.pop_back();
                cout << "\b \b";
            }
        } else {
            contra.push_back(caractersito);
            cout << "*";
        }
    }
    return contra;
}

void ingresoMedico() {
    int contador = 0;
    string codigo = "1", contra = "2";
    string ingreso_codigo, ingreso_contra;

    do {
        gotoxy(35, 5); cout << "INGRESE CODIGO MEDICO: ";
        getline(cin, ingreso_codigo);

        gotoxy(35, 7); cout << "INGRESE CONTRASENA: ";
        ingreso_contra = clavesita();

        if (ingreso_codigo == codigo && ingreso_contra == contra) {
            return;
        } else {
            contador++;
            gotoxy(35, 9); cout << "CREDENCIALES INCORRECTAS. Intentos: " << contador << "/3";
            getch();
            system("cls");
        }
    } while (contador < 3);

    gotoxy(35, 11); cout << "ACCESO DENEGADO. Cerrando programa...";
    Sleep(1000);
    system("cls");
    exit(1);
}


void liberar(Nodo*& lista) {
    if (!lista) return;

    Nodo* inicio = lista;

    do {
        Nodo* aux = lista;         
        lista = lista->siguiente;  
        delete aux;                
    } while (lista != inicio);  

    lista = nullptr;
}
