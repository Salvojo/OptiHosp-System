#include <iostream>
#include <string>
#include<windows.h>
using namespace std;

struct paciente {
    string nombre;
    int dni;
    int edad;
    string diagnostico;
    int numeroCama;        
    string tipoCama;        };

struct Nodo {
    paciente info;
    Nodo* siguiente;
    Nodo* anterior;         };

Nodo* lista = NULL; //esto para mejor compresión de nosotros (para explicar a la profe)al utilizar punteros se pone en main

void cambio_color(int x){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);}

void gotoxy(int x,int y) {
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);
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

//funciones de tu marido (para no estar repitiendo la misma wbda)
Nodo* crearNodo(Nodo*&lista);




void gotoxy(int x,int y);
void cambio_color(int x);
void mostrarCursor(bool visible);
string clavesita();



int main() {

   bannerInicio();
   ingresoMedico();
   menu();
   return 0;
}

void menu() {
    int opcion;
    do {
         cout<<"\n===== GESTIÓN DE CAMAS HOSPITALARIAS ====="<<endl;
        cout<<"1. Insertar paciente"<<endl;
         cout<<"2. Buscar paciente"<<endl;
         cout<<"3. Mostrar lista "<<endl;
        cout<<"4. Eliminar paciente por DNI"<<endl;
         cout<<"5. Salir"<<endl;
        cout<<"Seleccione una opción: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1: {
                int subop;
                do {
                    cout<<"\n===== SUBMENÚ DE INSERCIÓN ====="<<endl;
                     cout<<"1. Insertar al inicio un paciente"<<endl;
                     cout<<"2. Insertar al final un paciente"<<endl;
                     cout<<"3. Insertar antes de un paciente"<<endl;
                    cout<<"4. Insertar después de un paciente"<<endl;
                    cout<<"5. Volver al menú principal"<<endl;
                    cout<<"Seleccione una opción: ";
                    cin>>subop;

                    if (subop >= 1 && subop <= 4) {
                        paciente p;
                        cout << "\n--- Datos del nuevo paciente ---" << endl;
                        cin.ignore(); 
                        cout << "Nombre: ";
                        getline(cin, p.nombre);
                        cout << "DNI: ";
                        cin >> p.dni;
                        cout << "Edad: ";
                        cin >> p.edad;
                        cin.ignore(); 
                        cout << "Diagnóstico: ";
                        getline(cin, p.diagnostico);
                        cout << "Número de cama: ";
                        cin >> p.numeroCama;
                        cin.ignore();
                        cout << "Tipo de cama (General/UCI/Pediátrica): ";
                        getline(cin, p.tipoCama);
                        
                    }

                    switch (subop) {
                        case 1:
                            // insertarInicio(lista, p);
                            break;
                        case 2:
                            // insertarFinal(lista, p);
                            break;
                        case 3: {
                            int dniRef;
                            cout<<"DNI de referencia:"; cin>>dniRef;
                            // insertarAntesDe(lista, dniRef, p);
                            break;
                        }
                        case 4: {
                            int dniRef;
                            cout<<"DNI de referencia: "; cin>>dniRef;
                            // insertarDespuesDe(lista, dniRef, p);
                            break;
                        }
                    }
                } while (subop != 5);
                break;
            }

            case 2: {
                int dni;
                cout << "\n--- Buscar paciente ---" << endl;
                cout << "Ingrese DNI: "; cin >> dni;
                Nodo* encontrado = buscarPaciente(lista, dni);
                if (encontrado)
                    cout << "Paciente encontrado: " << encontrado->info.nombre 
                         << ", Edad: " << encontrado->info.edad << endl;
                else
                    cout << "No se encontró ningún paciente con ese DNI." << endl;
                break;
            }

            case 3:
                mostrarLista(lista);
                break;

            case 4: {
                int dni;
                cout << "\n--- Eliminar paciente ---" << endl;
                cout << "Ingrese DNI: "; cin >> dni;
                if (eliminarPorDNI(lista, dni))
                    cout << "Paciente eliminado correctamente.\n";
                else
                    cout << "No se encontró el paciente.\n";
                break;
            }

            case 5:
                cout << "Saliendo del sistema..." << endl;
                break;

            default:
                cout << "Opción inválida. Intente nuevamente.\n";
        }

    } while (opcion != 5);
}

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

string clavesita(){
    string contra;
    char caractersito;
    while(true){
        caractersito = getch();
        if(caractersito == 13){
            break;
        } else if(caractersito == 8){
            if(!contra.empty()){
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

void ingresoMedico(){
    int contador=0;
    string codigo="1", contra="2";
    string ingreso_codigo, ingreso_contra;

    do{
        gotoxy(35,5);cout<<"INGRESE CODIGO MEDICO: "; 
        getline(cin, ingreso_codigo);
        
        gotoxy(35,7);cout<<"INGRESE CONTRASENA: "; 
        ingreso_contra = clavesita();
        
        if(ingreso_codigo==codigo && ingreso_contra==contra){
            return; 
        } else {
            contador++;
            gotoxy(35,9); cout<<"CREDENCIALES INCORRECTAS. Intentos: "<<contador<<"/3";
            getch();
            system("cls");
        } 
    }while(contador<3);

    gotoxy(35,11); cout << "ACCESO DENEGADO. Cerrando programa...";
    Sleep(1000);
    system("cls");
    exit(1);
}

void insertarInicio(Nodo*& lista, const paciente& p){}

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

void insertarAntesDe(Nodo*& lista, int dniReferencia, const paciente& p){}

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
