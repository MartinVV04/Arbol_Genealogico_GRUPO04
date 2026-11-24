#include <iostream>
#include <string>
#include <clocale>
#include <cstdlib> 
using namespace std;

struct Nodo
{
    int codigo;     
    string nombre;  
    string padre; 
    string madre;   
    string rama;     
    Nodo *izq;       
    Nodo *der;       
};

Nodo *nuevoNodo(int codigo, string nombre, string padre, string madre, string rama);
Nodo *insertar(Nodo *raiz, Nodo *nuevo);
Nodo *buscar(Nodo *raiz, int codigo);
Nodo *minimo(Nodo *raiz);
Nodo *eliminar(Nodo *raiz, int codigo);
void preorden(Nodo *raiz);
void inorden(Nodo *raiz);
void postorden(Nodo *raiz);
int consultarRama(Nodo *raiz, string rama);
void mostrarMiembro(Nodo *miembro);
void mostrarRuta(Nodo *raiz, int codigo);
string leerTexto(string mensaje);
void cargarDatosPrueba(Nodo *&raiz);
void registrar(Nodo *&raiz);
void menu();

Nodo *nuevoNodo(int codigo, string nombre, string padre, string madre, string rama)
{
    Nodo *nodo = new Nodo;
    nodo->codigo = codigo;
    nodo->nombre = nombre;
    nodo->padre = padre;
    nodo->madre = madre;
    nodo->rama = rama;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

Nodo *insertar(Nodo *raiz, Nodo *nuevo)
{
    if (raiz == NULL)
    {
        return nuevo;                    
    }
    if (nuevo->codigo < raiz->codigo)
    {
        raiz->izq = insertar(raiz->izq, nuevo);   
    }
    else
    {
        if (nuevo->codigo > raiz->codigo)
        {
            raiz->der = insertar(raiz->der, nuevo); 
        }
        else
        {
            cout << "El código ya existe, no se inserta \n";
        }
    }
    return raiz;
}

Nodo *buscar(Nodo *raiz, int codigo)
{
    if (raiz == NULL)
    {
        return NULL;                     
    }
    if (codigo == raiz->codigo)
    {
        return raiz;                 
    }
    if (codigo < raiz->codigo)
    {
        return buscar(raiz->izq, codigo);
    }
    return buscar(raiz->der, codigo);
}

Nodo *minimo(Nodo *raiz)
{
    Nodo *actual = raiz;
    while (actual->izq != NULL)
    {
        actual = actual->izq;
    }
    return actual;
}

Nodo *eliminar(Nodo *raiz, int codigo)
{
    Nodo *aux;
    Nodo *sucesor;

    if (raiz == NULL)
    {
        return NULL;
    }

    if (codigo < raiz->codigo)
    {
        raiz->izq = eliminar(raiz->izq, codigo); 
    }
    else
    {
        if (codigo > raiz->codigo)
        {
            raiz->der = eliminar(raiz->der, codigo); 
        }
        else
        {
            if (raiz->izq == NULL && raiz->der == NULL)
            {
                delete raiz;
                return NULL;
            }
            else
            {
                if (raiz->izq == NULL)
                {
                    aux = raiz->der;
                    delete raiz;
                    return aux;
                }
                else
                {
                    if (raiz->der == NULL)
                    {
                        aux = raiz->izq;
                        delete raiz;
                        return aux;
                    }
                    else
                    {
                        sucesor = minimo(raiz->der);
                        raiz->codigo = sucesor->codigo;
                        raiz->nombre = sucesor->nombre;
                        raiz->padre = sucesor->padre;
                        raiz->madre = sucesor->madre;
                        raiz->rama = sucesor->rama;
                        raiz->der = eliminar(raiz->der, raiz->codigo);
                    }
                }
            }
        }
    }
    return raiz;
}

void mostrarMiembro(Nodo *miembro)
{
    cout << "Código: " << miembro->codigo
         << " | Nombre: " << miembro->nombre
         << " | Padre: " << miembro->padre
         << " | Madre: " << miembro->madre
         << " | Rama: " << miembro->rama << "\n";
}

void preorden(Nodo *raiz)
{
    if (raiz != NULL)
    {
        mostrarMiembro(raiz);
        preorden(raiz->izq);
        preorden(raiz->der);
    }
}

void inorden(Nodo *raiz)
{
    if (raiz != NULL)
    {
        inorden(raiz->izq);
        mostrarMiembro(raiz);
        inorden(raiz->der);
    }
}

void postorden(Nodo *raiz)
{
    if (raiz != NULL)
    {
        postorden(raiz->izq);
        postorden(raiz->der);
        mostrarMiembro(raiz);
    }
}

int consultarRama(Nodo *raiz, string rama)
{
    int total;
    if (raiz == NULL)
    {
        return 0;
    }
    total = consultarRama(raiz->izq, rama);
    if (raiz->rama == rama)
    {
        mostrarMiembro(raiz);
        total = total + 1;
    }
    total = total + consultarRama(raiz->der, rama);
    return total;
}

void mostrarRuta(Nodo *raiz, int codigo)
{
    Nodo *actual = raiz;
    cout << "Ruta en el árbol: ";
    while (actual != NULL)
    {
        cout << actual->codigo;
        if (actual->codigo == codigo)
        {
            actual = NULL;
        }
        else
        {
            cout << " -> ";
            if (codigo < actual->codigo)
            {
                actual = actual->izq;
            }
            else
            {
                actual = actual->der;
            }
        }
    }
    cout << "\n";
}

string leerTexto(string mensaje)
{
    string texto;
    do
    {
        cout << mensaje;
        getline(cin, texto);
        if (texto == "")
        {
            cout << "El dato no puede quedar vacío. Si no se conoce, escriba Desconocido o Desconocida \n";
        }
    }
    while (texto == "");
    return texto;
}

void cargarDatosPrueba(Nodo *&raiz)
{
    int i;
    int codigos[10] = {50, 30, 70, 20, 40, 60, 80, 10, 35, 65};
    string nombres[10] = {"Aru", "Belen", "Ciro", "Dalia", "Eron", "Fara", "Galen", "Huma", "Ilan", "Jana"};
    string padres[10] = {"Desconocido", "Aru", "Aru", "Belen", "Belen", "Ciro", "Ciro", "Dalia", "Eron", "Fara"};
    string madres[10] = {"Desconocida", "Naira", "Naira", "Ima", "Ima", "Luma", "Luma", "Sira", "Mara", "Oren"};
    string ramas[10] = {"Solar", "Solar", "Lunar", "Solar", "Solar", "Lunar", "Lunar", "Solar", "Solar", "Lunar"};

    for (i = 0; i < 10; i++)
    {
        raiz = insertar(raiz, nuevoNodo(codigos[i], nombres[i], padres[i], madres[i], ramas[i]));
    }
}

void registrar(Nodo *&raiz)
{
    int codigo;
    string nombre, padre, madre, rama;
    Nodo *nuevo;

    do
    {
        cout << "Ingrese código (mayor a 0): ";
        cin >> codigo;
        if (codigo <= 0)
        {
            cout << "El código debe ser mayor a 0 \n";
        }
    }
    while (codigo <= 0);

    if (buscar(raiz, codigo) != NULL)
    {
        cout << "El código ya existe, no se registra el miembro \n";
        return;
    }

    cin.ignore();  
    nombre = leerTexto("Ingrese nombre: ");
    padre = leerTexto("Ingrese nombre del padre: ");
    madre = leerTexto("Ingrese nombre de la madre: ");
    rama = leerTexto("Ingrese rama familiar: ");

    nuevo = nuevoNodo(codigo, nombre, padre, madre, rama);
    raiz = insertar(raiz, nuevo);
    cout << "Miembro registrado \n";
    mostrarRuta(raiz, codigo);
}

void menu()
{
    Nodo *raiz = NULL;
    int op, codigo, total;
    string rama;
    Nodo *encontrado;

    cargarDatosPrueba(raiz);
    cout << "Se cargaron 10 miembros de prueba en el árbol \n";
    system("pause");
    system("cls");

    do
    {
        cout << "*** ÁRBOL GENEALÓGICO DE LA CIVILIZACIÓN PERDIDA *** \n";
        cout << "1. Registrar miembro \n";
        cout << "2. Buscar miembro por código \n";
        cout << "3. Eliminar miembro \n";
        cout << "4. Mostrar recorrido inorden \n";
        cout << "5. Mostrar recorrido preorden \n";
        cout << "6. Mostrar recorrido postorden \n";
        cout << "7. Consultar miembros por rama \n";
        cout << "8. Salir \n";

        do
        {
            cout << "Elegir opción (1-8): ";
            cin >> op;
            if (op < 1 || op > 8)
            {
                cout << "Opción inválida, debe elegir del 1 al 8 \n";
            }
        }
        while (op < 1 || op > 8);

        switch (op)
        {
            case 1:
                cout << "\n--- Registrar miembro --- \n";
                registrar(raiz);
                break;

            case 2:
                cout << "\n--- Buscar miembro --- \n";
                if (raiz == NULL)
                {
                    cout << "El árbol está vacío \n";
                }
                else
                {
                    cout << "Ingrese el código a buscar: ";
                    cin >> codigo;
                    encontrado = buscar(raiz, codigo);
                    if (encontrado == NULL)
                    {
                        cout << "No existe un miembro con ese código \n";
                    }
                    else
                    {
                        cout << "Miembro encontrado \n";
                        mostrarMiembro(encontrado);
                        mostrarRuta(raiz, codigo);
                    }
                }
                break;

            case 3:
                cout << "\n--- Eliminar miembro --- \n";
                if (raiz == NULL)
                {
                    cout << "El árbol está vacío \n";
                }
                else
                {
                    cout << "Ingrese el código a eliminar: ";
                    cin >> codigo;
                    encontrado = buscar(raiz, codigo);
                    if (encontrado == NULL)
                    {
                        cout << "No existe un miembro con ese código \n";
                    }
                    else
                    {
                        cout << "Se eliminará el siguiente miembro: \n";
                        mostrarMiembro(encontrado);
                        raiz = eliminar(raiz, codigo);
                        cout << "Miembro eliminado \n";
                    }
                }
                break;

            case 4:
                cout << "\n--- Recorrido Inorden (Izquierda - Raíz - Derecha) --- \n";
                if (raiz == NULL)
                {
                    cout << "El árbol está vacío \n";
                }
                else
                {
                    inorden(raiz);
                }
                break;

            case 5:
                cout << "\n--- Recorrido Preorden (Raíz - Izquierda - Derecha) --- \n";
                if (raiz == NULL)
                {
                    cout << "El árbol está vacío \n";
                }
                else
                {
                    preorden(raiz);
                }
                break;

            case 6:
                cout << "\n--- Recorrido Postorden (Izquierda - Derecha - Raíz) --- \n";
                if (raiz == NULL)
                {
                    cout << "El árbol está vacío \n";
                }
                else
                {
                    postorden(raiz);
                }
                break;

            case 7:
                cout << "\n--- Consultar miembros por rama --- \n";
                if (raiz == NULL)
                {
                    cout << "El árbol está vacío \n";
                }
                else
                {
                    cin.ignore();  
                    rama = leerTexto("Ingrese la rama a consultar: ");
                    total = consultarRama(raiz, rama);
                    if (total == 0)
                    {
                        cout << "No hay miembros en esa rama \n";
                    }
                    else
                    {
                        cout << "Total de miembros en la rama " << rama << ": " << total << "\n";
                    }
                }
                break;

            case 8:
                cout << "Hasta pronto... \n";
                break;
        }

        if (op != 8)
        {
            system("pause");
            system("cls");
        }
    }
    while (op != 8);
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    menu();
    return 0;
}
