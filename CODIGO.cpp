#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <chrono>
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

Nodo* lista = NULL; // esto para mejor comprensión (para explicar a la profe) al utilizar punteros se pone en main

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
Nodo* buscarPaciente(Nodo* lista, int dni);
void mostrarLista(Nodo* lista);
bool eliminarPorDNI(Nodo*& lista, int dni);
void menu();

// funciones auxiliares
Nodo* crearNodo(Nodo*& lista);
void gotoxy(int x, int y);
void cambio_color(int x);
void mostrarCursor(bool visible);
string clavesita();

int main() {
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

                    if (subop >= 1 && subop <= 4) {
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

                        if (subop == 1) insertarInicio(lista, p);
                        else if (subop == 2) insertarFinal(lista, p);
                        else if (subop == 3) {
                            int dniRef;
                            cout << "\nDNI de referencia: "; cin >> dniRef;
                            insertarAntesDe(lista, dniRef, p);
                        } else if (subop == 4) {
                            int dniRef;
                            cout << "\nDNI de referencia: "; cin >> dniRef;
                            insertarDespuesDe(lista, dniRef, p);
                        }
                    }

                    if (subop != 5) {
                        cout << "\nPresione una tecla para continuar...";
                        getch();
                        system("cls");
                    }
                } while (subop != 5);
                break;
            }

            case 2: {
                int dni;
                cout << "Ingrese el DNI del paciente: ";
                cin >> dni;
                Nodo* encontrado = buscarPaciente(lista, dni);
                if (encontrado) {
                    cambio_color(10);
                    cout << "\nPaciente encontrado:\n";
                    cout << "Nombre: " << encontrado->info.nombre << endl;
                    cout << "Edad: " << encontrado->info.edad << endl;
                    cout << "Diagnóstico: " << encontrado->info.diagnostico << endl;
                } else {
                    cambio_color(12);
                    cout << "\nNo se encontró ningún paciente con ese DNI.\n";
                }
                cambio_color(7);
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

Nodo* buscarPaciente(Nodo* lista, int dni){}

void mostrarLista(Nodo* lista){}

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
