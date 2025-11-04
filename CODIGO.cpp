#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <string.h>
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



//FUNCIONES PRINCIPALES
void menu(Nodo* &lista);
void insertarInicio(Nodo*& lista, const paciente& p);
void insertarFinal(Nodo*& lista, const paciente& p);
void insertarAntesDe(Nodo*& lista, int dniReferencia, const paciente& p);
void insertarDespuesDe(Nodo*& lista, int dniReferencia, const paciente& p);
void buscarPaciente(Nodo* lista);
void mostrarPacientes(Nodo* lista);
//bool eliminarPorDNI(Nodo*& lista, int dni);



//FUNCIONES SECUNDARIAS
Nodo* crearNodo(Nodo*);
void ingresoMedico();
string clavesita();
paciente ingresoPaciente();



//FUNCIONES AUXILIARES
void gotoxy(int x,int y);
void cambio_color(int x);
void mostrarCursor(bool visible);
void bannerInicio();




int main() {
    SetConsoleOutputCP(CP_UTF8);
    Nodo* lista = nullptr; 
    //bannerInicio(); 
    ingresoMedico(); system("cls");
    menu(lista);
    return 0;
}

// ===== MENÚ PRINCIPAL ========
void menu(Nodo* &lista){//variable principal a usar entra al menu y tabajamos con ella
    int opcion;
    system("cls");
    do {
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
        
        switch (opcion) {
            case 1: {
                system("cls");
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

                    switch (subop){
                        case 1:{
                            paciente p=ingresoPaciente();
                            insertarInicio(lista, p);
                            system("cls");
                            break;
                        }

                        case 2:{
                            paciente p=ingresoPaciente();
                            insertarFinal(lista, p);
                            system("cls");
                            break;
                        }

                        case 3: {
                                int dniRef;
                                cout << "DNI de referencia: "; 
                                cin >> dniRef;
                            
                                // verificacion del dni :)
                                Nodo* actual = lista;
                                bool encontrado = false;
                                if (lista != nullptr) {
                                    do {
                                        if (actual->info.dni == dniRef) {
                                            encontrado = true;
                                            break;
                                        }
                                        actual = actual->siguiente;
                                    } while (actual != lista);
                                }
                            
                                if (!encontrado) {
                                    cambio_color(12);
                                    cout << "\nDNI inválido. No se encontró el paciente de referencia.\n";
                                    cambio_color(7);
                                    getch();
                                    system("cls");
                                    break;  
                                }
                            
                                
                                paciente p = ingresoPaciente();
                                insertarAntesDe(lista, dniRef, p);
                                system("cls");
                                break;
                            }


                        case 4: {
                                    int dniRef;
                                    cout << "DNI de referencia: "; 
                                    cin >> dniRef;
                                
                                    // Verificar si el DNI existe
                                    Nodo* actual = lista;
                                    bool encontrado = false;
                                    if (lista != nullptr) {
                                        do {
                                            if (actual->info.dni == dniRef) {
                                                encontrado = true;
                                                break;
                                            }
                                            actual = actual->siguiente;
                                        } while (actual != lista);
                                    }
                                
                                    if (!encontrado) {
                                        cambio_color(12);
                                        cout << "\nDNI inválido. No se encontró el paciente de referencia.\n";
                                        cambio_color(7);
                                        getch();
                                        system("cls");
                                        break;  // regresa al submenú sin pedir datos del paciente
                                    }
                                
                                    // Si se encontró el DNI, pedir datos del paciente
                                    paciente p = ingresoPaciente();
                                    insertarDespuesDe(lista, dniRef, p);
                                    system("cls");
                                    break;
                                }

                        case 5:
                            system("cls");
                        break;

                        default:
                            cambio_color(12);
                            cout<<setw(10) << "\nOpción inválida. Intente nuevamente.\n";
                            cambio_color(7);
                            Sleep(100);
                            system("cls");
                        break;

                    }

                } while (subop != 5);

                break;
            }

            case 2: {
                buscarPaciente(lista);
                cout << "\nPresione una tecla para continuar...";
                getch();
                system("cls");
                break;
            }

            case 3:
                mostrarPacientes(lista);
                cout << "\nPresione una tecla para continuar...";
                getch();
                system("cls");
                break;

            case 4: {
                //int dni;
                /*cout << "Ingrese el DNI del paciente a eliminar: ";
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
                */
                system("cls");
                break;
            }

            case 5:
                system("cls");
                cambio_color(14);
                cout << "\nSaliendo del sistema...\n";
                Sleep(100);
                break;

            default:
                cambio_color(12);
                cout << "Opción inválida. Intente nuevamente.\n";
                cambio_color(7);
                Sleep(100);
            }
    } while (opcion != 5);
}

Nodo* crearNodo(paciente persona){
    Nodo* nuevo= new Nodo();
    nuevo->info=persona;
    nuevo->siguiente=nullptr;
    nuevo->anterior=nullptr;
    return nuevo;
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
        gotoxy(35,5);cout<<"INGRESE CÓDIGO MÉDICO: "; 
        getline(cin, ingreso_codigo);
        
        gotoxy(35,7);cout<<"INGRESE CONTRASEÑA: "; 
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

paciente ingresoPaciente(){
    paciente p;
    cout << "\n--- Datos del nuevo paciente ---" << endl;
    cin.ignore();
    cout << "Nombre: "; getline(cin, p.nombre);
    cout << "DNI: "; cin >> p.dni;
    cout << "Edad: "; cin >> p.edad;
    cin.ignore(); 
    cout << "Diagnóstico: "; getline(cin, p.diagnostico);

   do{
        cout << "\nTipo de cama [1=General, 2=UCI, 3=UCIN]: ";
        cin >> p.tipoCama;
    }while(p.tipoCama< 1 || p.tipoCama>3);

    return p;
}

void insertarInicio(Nodo*& lista, const paciente& p){
    Nodo* nuevo = crearNodo(p);
    
    if (lista == NULL) {
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
        lista = nuevo;
    }else{
        Nodo* ultimo = lista->anterior;  
        nuevo->siguiente = lista;  
        nuevo->anterior = ultimo;    
        lista->anterior = nuevo;   
        ultimo->siguiente = nuevo;   
        lista = nuevo;
    }
    string mensaje = "Paciente insertado al inicio correctamente";
    for (char c : mensaje){
        cout << c << flush; 
        Sleep(60);
    }
}

void insertarFinal(Nodo*& lista, const paciente& p){
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

    string mensaje = "Paciente insertado al final correctamente";
    for (char c : mensaje){
        cout << c << flush; 
        Sleep(60);
    }
}

void insertarAntesDe(Nodo*& lista, int dniReferencia, const paciente& p){
    if (lista == NULL) {
        cout << "La lista está vacía. \nNo se puede insertar antes de un paciente inexistente.\n";
        return;
    }

    Nodo* actual = lista;

    do {
        if (actual->info.dni == dniReferencia) {
            Nodo* nuevo =crearNodo(p);
            // se enlaza al nuevo nodo
            nuevo->siguiente = actual;
            nuevo->anterior = actual->anterior;
        
            actual->anterior->siguiente = nuevo;
            actual->anterior = nuevo;
            if (actual == lista) {
                    lista = nuevo;
            }
            cout << "Paciente insertado correctamente antes del DNI " << dniReferencia << ".\n";
            getch();
            return;
            }
        actual = actual->siguiente;
    } while (actual != lista);

    cout<<"No se encontró un paciente con el DNI de referencia.\n";   
}

void insertarDespuesDe(Nodo*& lista, int dniReferencia, const paciente& p){
    if (lista == nullptr) {
        cout << "La lista está vacía. \nNo se puede insertar después de un paciente inexistente.\n";
        return;}

    Nodo* actual = lista;
    do {
        if (actual->info.dni == dniReferencia) {
            Nodo* nuevo = crearNodo(p);

            // se enlaza al nuevo nodo
            nuevo->siguiente = actual->siguiente;
            nuevo->anterior = actual;

            actual->siguiente->anterior = nuevo;
            actual->siguiente = nuevo;

            cout << "Paciente insertado correctamente después del DNI " << dniReferencia << ".\n";
            getch();
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

void mostrarPacientes(Nodo* lista){
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
         << "DIAGNÓSTICO\n";

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

//bool eliminarPorDNI(Nodo*& lista, int dni){}


void liberar(Nodo*& lista) {
    if (!lista) return;

    Nodo* actual = lista->siguiente;

    while (actual != lista) {
        Nodo* aux = actual;
        actual = actual->siguiente;
        delete aux;
    }
    delete lista;
    lista = nullptr;
}


void cambio_color(int x){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}

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

void bannerInicio() {
    system("cls");
    string titulo = "SISTEMA DE GESTIÓN HOSPITALARIA";
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
