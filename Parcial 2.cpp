#include <iostream>
#include <stack>
#include <queue>
#include <list>

using namespace std;
struct Nodo {
    int dato;
    Nodo* izquierda;
    Nodo* derecha;
};
class Menu {
public:void menuPrincipal();
    void menuOperaciones(stack<int>& pila, queue<int>& cola, list<int>& listaCircular, Nodo*& arbol);
    void insertarNodo(Nodo*& raiz, int dato);
    void mostrarListaCircular(const list<int>& listaCircular);
    void mostrarArbol(Nodo* arbol);
    void mostrarArbolInorden(Nodo* nodo);
    bool editarDato(stack<int>& pila, queue<int>& cola, list<int>& listaCircular, int datoViejo, int datoNuevo);
    bool eliminarDato(stack<int>& pila, queue<int>& cola, list<int>& listaCircular, int dato);
};
void Menu::menuPrincipal() {
    cout << "MENU PRINCIPAL" << endl;
    cout << "1. Crear Pila" << endl;
    cout << "2. Crear Cola" << endl;
    cout << "3. Salir" << endl;
}
void Menu::menuOperaciones(stack<int>& pila, queue<int>& cola, list<int>& listaCircular, Nodo*& arbol) {
    int opcion;
    do {
        cout << "\nMENU DE OPERACIONES" << endl;
        cout << "1. Agregar dato" << endl;
        cout << "2. Editar dato" << endl;
        cout << "3. Eliminar dato" << endl;
        cout << "4. Mostrar lista circular" << endl;
        cout << "5. Mostrar arbol " << endl;
        cout << "6. Regresar al menu principal" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int dato;
                cout << "Ingrese el dato: ";
                cin >> dato;
                pila.push(dato);
                cola.push(dato);
                listaCircular.push_back(dato);
                insertarNodo(arbol, dato);
                break;
            }
            case 2: {
                int datoViejo, datoNuevo;
                cout << "Ingrese el dato que desea editar: ";
                cin >> datoViejo;
                cout << "Ingrese el nuevo valor: ";
                cin >> datoNuevo;
                if (editarDato(pila, cola, listaCircular, datoViejo, datoNuevo)) {
                    cout << "Dato editado correctamente." << endl;
                } else {
                    cout << "El dato no se encontró." << endl;
                }
                break;
            }
            case 3: {
                int dato;
                cout << "Ingrese el dato que desea eliminar: ";
                cin >> dato;
                if (eliminarDato(pila, cola, listaCircular, dato)) {
                    cout << "Dato eliminado correctamente." << endl;
                } else {
                    cout << "El dato no se encontró." << endl;
                }
                break;
            }
            case 4: {
                mostrarListaCircular(listaCircular);
                break;
            }
            case 5: {
                mostrarArbol(arbol);
                break;
            }
            case 6: {
                break;
            }
            default: {
                cout << "Opcion no valida. Intente de nuevo." << endl;
            }
        }
    } while (opcion != 6);
}

void Menu::insertarNodo(Nodo*& raiz, int dato) {
    if (raiz == nullptr) {
        raiz = new Nodo;
        raiz->dato = dato;
        raiz->izquierda = nullptr;
        raiz->derecha = nullptr;
    } else {
        if (dato < raiz->dato) {
            insertarNodo(raiz->izquierda, dato);
        } else if (dato > raiz->dato) {
            insertarNodo(raiz->derecha, dato);
        }
    }
}

void Menu::mostrarListaCircular(const list<int>& listaCircular) {
    cout << "Lista Circular: ";
    if (!listaCircular.empty()) {
        for (int elemento : listaCircular) {
            cout << elemento << " ";
        }
        cout << endl;
    } else {
        cout << "La lista circular esta vacia." << endl;
    }
}

void Menu::mostrarArbol(Nodo* arbol) {
    if (arbol == nullptr) {
        cout << "El arbol esta vacio." << endl;
        return;
    }

    cout << "Arbol: ";
    mostrarArbolInorden(arbol);
    cout << endl;
}

void Menu::mostrarArbolInorden(Nodo* nodo) {
    if (nodo != nullptr) {
        mostrarArbolInorden(nodo->izquierda);
        cout << nodo->dato << " ";
        mostrarArbolInorden(nodo->derecha);
    }
}

bool Menu::editarDato(stack<int>& pila, queue<int>& cola, list<int>& listaCircular, int datoViejo, int datoNuevo) {
    bool encontrado = false;
    
    stack<int> tempPila;
    while (!pila.empty()) {
        if (pila.top() == datoViejo) {
            tempPila.push(datoNuevo);
            encontrado = true;
        } else {
            tempPila.push(pila.top());
        }
        pila.pop();
    }
    while (!tempPila.empty()) {
        pila.push(tempPila.top());
        tempPila.pop();
    }
    queue<int> tempCola;
    while (!cola.empty()) {
        if (cola.front() == datoViejo) {
            tempCola.push(datoNuevo);
            encontrado = true;
        } else {
            tempCola.push(cola.front());
        }
        cola.pop();
    }
    while (!tempCola.empty()) {
        cola.push(tempCola.front());
        tempCola.pop();
    }
    list<int>::iterator it;
    for (it = listaCircular.begin(); it != listaCircular.end(); ++it) {
        if (*it == datoViejo) {
            *it = datoNuevo;
            encontrado = true;
        }
    }

    return encontrado;
}

bool Menu::eliminarDato(stack<int>& pila, queue<int>& cola, list<int>& listaCircular, int dato) {
    bool encontrado = false;
    stack<int> tempPila;
    while (!pila.empty()) {
        if (pila.top() == dato) {
            pila.pop();
            encontrado = true;
        } else {
            tempPila.push(pila.top());
            pila.pop();
        }
    }
   while (!tempPila.empty()) {
        pila.push(tempPila.top());
        tempPila.pop();
    }
    queue<int> tempCola;
    while (!cola.empty()) {
        if (cola.front() == dato) {
            cola.pop();
            encontrado = true;
        } else {
            tempCola.push(cola.front());
            cola.pop();
        }
    }
    while (!tempCola.empty()) {
        cola.push(tempCola.front());
        tempCola.pop();
    }
    listaCircular.remove(dato);

    return encontrado;
}

int main() {
    Menu menu;
    stack<int> pila;
    queue<int> cola;
    list<int> listaCircular;
    Nodo* arbol = nullptr;

    int opcion;
    do {
        menu.menuPrincipal();
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "Pila creada." << endl;
                break;
            }
            case 2: {
                cout << "Cola creada." << endl;
                break;
            }
            case 3: {
                cout << "Saliendo del programa." << endl;
                exit(0);
            }
            default: {
                cout << "Opcion no valida. Intente de nuevo." << endl;
            }
        }
        if (opcion == 1 || opcion == 2) {
            menu.menuOperaciones(pila, cola, listaCircular, arbol);
        }

    } while (opcion != 3);

    return 0;
}

    
