#include <iostream>
#include <sstream>
#include <limits>
using namespace std;

template <class N>
class NodoLista{
    public:
    N dato;                 
    NodoLista<N>* next;     
    
    NodoLista(){
        next = nullptr;
    } 
    //Constructor
    NodoLista(N valor) {
        dato = valor;
        next = nullptr;
    }
};

template <class N>
class Lista{
private:
    NodoLista<N>* first;
public:
    //Constructor
    Lista(){
        first = nullptr;
    }

    ~Lista() {
        NodoLista<N>* actual = first;
        while (actual != nullptr) {
            NodoLista<N>* temp = actual; 
            actual = actual->next;        
            delete temp;                
        }
    }

    template <typename T>
    T leerEntradaValida(string mensaje) {
        T valor;
        while (true) {
            cout << mensaje;
            string input;
            cin >> input;

            try {
                istringstream iss(input);
                if (!(iss >> valor)) {
                    throw invalid_argument("No es un número válido.");
                }
                break;
            } catch (invalid_argument& e) {
                cout << "Error: " << e.what() << " Intentar de nuevo." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        return valor;
    }

    void insertarInicio(){
        N valor = leerEntradaValida<N>("Ingresar dato: ");
        NodoLista<N> *nuevoNodo = new NodoLista<N>(valor);
        nuevoNodo->next = first;
        first = nuevoNodo;
    }
    
    void insertarFinal(){
        N valor = leerEntradaValida<N>("Ingresar dato: ");;

        NodoLista<N> *nuevoNodo = new NodoLista<N>(valor);
        NodoLista<N>* actual = first;

        if(first == nullptr){
            first = nuevoNodo;
        } else{
            while(actual->next != nullptr)
                actual = actual->next;
            actual->next = nuevoNodo;
        }
    }

    void insertarDespues(int k) {
        N valor = leerEntradaValida<N>("Ingresar dato a insertar: ");

        NodoLista<N>* nuevoNodo = new NodoLista<N>(valor);

        if (k == 0) {
            nuevoNodo->next = first;
            first = nuevoNodo;
            return;
        }

        NodoLista<N>* actual = first;

        for (int i = 0; actual != nullptr && i < k - 1; i++) {
            actual = actual->next;  
        }

        if (actual != nullptr) {
            nuevoNodo->next = actual->next; 
            actual->next = nuevoNodo;
        } else {
            cout << "La posición " << k << " está fuera de los límites de la lista." << endl;
            delete nuevoNodo;  
        }     
    }        

    int read(N valor) {
        while (true) { 
            NodoLista<N>* actual = first; // Reinicia el nodo actual al inicio de la lista
            int posicion = 0;
            
            // Solicita al usuario que ingrese un valor
            cout << "Ingresar elemento a buscar: ";
            string input;
            cin >> input;

            // Intentar convertir la entrada del usuario a tipo N
            try {
                istringstream iss(input);
                if (!(iss >> valor)) {
                    throw invalid_argument("No es un numero valido. ");
                }

                // Recorrer la lista en busca del valor
                while (actual != nullptr) {
                    if (valor == actual->dato) {
                        cout << "Elemento encontrado en la posicion: " << posicion << endl; // Mensaje de éxito
                        return posicion; // Retornar la posicion del elemento
                    }
                    actual = actual->next; // Moverse al siguiente nodo
                    posicion++; // Incrementar la posición
                }
                // Si el elemento no se encuentra en la lista
                cout << "Elemento no encontrado. Intenta de nuevo. " << endl;

            } catch (invalid_argument& e) {
                cout << "Error: " << e.what() << " Intentar de nuevo. " << endl;
            }
        }
    }
    
    //Operación update
    void update(N oldDato) {
        N newDato = leerEntradaValida<N>("Ingresar el nuevo elemento: ");

        NodoLista<N>* actual = first;
        bool encontrado = false;

        while (actual != nullptr) {
            if (actual->dato == oldDato) {
                actual->dato = newDato; 
                encontrado = true;
                cout << "El elemento " << oldDato << " fue actualizado a " << newDato << "." << endl;
                break;
            }
            actual = actual->next;
        }

        if (!encontrado) {
            cout << "El elemento " << oldDato << " no fue encontrado en la lista." << endl;
        }
    }


    void deleteNodo(N datobasura){
        if (first == nullptr) {
            throw invalid_argument("La lista está vacía. No se puede eliminar el elemento.");
        }

        NodoLista<N>* actual = first;
        NodoLista<N>* prev = nullptr;
        bool encontrado = false;
        
        if (actual != nullptr && actual->dato == datobasura) {
            first = actual->next; 
            delete actual;        
            encontrado = true;
            cout << "Elemento " << datobasura << " eliminado." << endl;
            return;               
        }
        
        while (actual != nullptr){
            if (actual->dato == datobasura){
                prev->next = actual->next;
                delete actual;
                encontrado = true;
                cout << "Elemento " << datobasura << " eliminado." << endl;
                return;
            }
            
            prev = actual;
            actual = actual->next;
            
        }
        if (!encontrado) {
            throw invalid_argument("Elemento " + to_string(datobasura) + " no encontrado en la lista.");
        }
    }

    //Imprimir lista
    void imprimir(){
        NodoLista<N> *actual = first;
            while (actual != nullptr) {
            cout << "Dato: " << actual->dato << endl;
            actual = actual->next;
        }
    }

    int tamano() { 
        NodoLista<N>* actual = first;
        int size = 0;
        while (actual != nullptr) {
            size++;
            actual = actual->next;
        }
        return size;
    }
};


/////////////////////////////////////////////////////////////
int main() {
    Lista<int> lista;
    int size = lista.leerEntradaValida<int>("Escribe el número de elementos de la lista: ");

    for (int i = 0; i < size; i++) {
        lista.insertarFinal();
    }

    cout << "Lista actual:\n";
    lista.imprimir();

    int buscar;
    // Llamar a read en un bucle hasta que encuentre un elemento válido
    int encontrado = -1; // Inicializar la variable
    while (encontrado == -1) {
        encontrado = lista.read(buscar); // Llamar a read con el valor ingresado
    }

    int antiguo = lista.leerEntradaValida<int>("Ingresa el elemento a actualizar: ");
    lista.update(antiguo);
    lista.imprimir();

    try {
        int eliminar = lista.leerEntradaValida<int>("Ingresa el elemento a eliminar: ");
        lista.deleteNodo(eliminar);
    } catch (invalid_argument& e){
        cout << "Error: " << e.what() << endl;
    }
    
    lista.imprimir();

    int posicion = lista.leerEntradaValida<int>("Ingresa la posición en donde insertar: ");
    lista.insertarDespues(posicion);
    lista.imprimir();

    return 0;
};