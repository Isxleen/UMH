#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <Windows.h>

using namespace std;

typedef struct nodoA
{
    string nombre;
    string nombreG;
    string tipocuerpo;
    int masa;
    int distancia;

    struct nodoA *izq, *der;

}*nodoarbol;

typedef struct Arbol
{
    string NombreArbol;
    struct nodoA *raiz;
}*arbol;

arbol CrearArbol(string nom)
{
    arbol ar;
    ar = new struct Arbol;
    ar->raiz = new struct nodoA;

    ar->NombreArbol = nom;
                                                // Creo primer nodo pero está vacío
    ar-> raiz->izq = ar->raiz->der = NULL;

    return(ar);
}

bool ValidarDatos(string cuerpo, double masa, double distancia)
{
    if(cuerpo == "S"|cuerpo == "M"|cuerpo == "P")
        {if(masa<=20&masa>=0){
            if(distancia<=1000&distancia>=0){
                return true;
            }
        }
    }else
    {
        return false;
    }
}

bool ArbolVacio(arbol ar)
{
    if(ar->raiz->nombre == "")
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

int Orden(string nombre1, string nombre2)
{
    if(nombre1 < nombre2){
        return -1;
    }else if(nombre1 > nombre2){
        return 1;
    }else if(nombre1 == nombre2){
        return 0;
    }
}

nodoA *InsertarCuerpo(arbol ar, string cuerpo, int masa, int distancia, string nombreGaux)
{
    struct nodoA *nodo_padre, *nodo_aux;
    nodo_padre = new struct nodoA;
    nodo_aux = new struct nodoA;

    nodo_padre = NULL;
    nodo_aux = ar->raiz;


    int numnom = 100 + rand() % 999;
    string numeronombre(std::to_string(numnom));
    string nombreaux;

     if(ArbolVacio(ar))
        {
            nodo_aux->tipocuerpo = cuerpo;
            nodo_aux->masa = masa;
            nodo_aux->distancia = distancia;

            nodo_aux->izq = nodo_aux->der = NULL;

            nodo_aux->nombre = nombreGaux+numeronombre+cuerpo;
            cout<<"\nSe ha introducido el cuerpo: "<<nodo_aux->nombre<<" a la galaxia "<< ar->NombreArbol<<endl;

            return nodo_aux;
        }
        else
        {
             nombreaux = nombreGaux+numeronombre+cuerpo;

             while((nodo_aux!=NULL) && Orden(nombreaux, nodo_aux->nombre) != 0)
            {
                nodo_padre = nodo_aux;
                if(Orden(nombreaux, nodo_padre->nombre)==-1) nodo_aux = nodo_aux->izq;
                else nodo_aux = nodo_aux->der;
            }
            if(nodo_aux!=NULL)
            {
                cout <<"\n"<< nodo_aux->nombre << "no se puede insertar puesto que este ya existe"<<endl;
                return NULL;
            }
            if(Orden(nombreaux, nodo_padre->nombre)==-1)
            {
                struct nodoA *nodo;
                nodo = new struct nodoA;

                nodo_padre->izq = nodo;

                nodo->tipocuerpo = cuerpo;
                nodo->masa = masa;
                nodo->distancia = distancia;
                nodo->nombre = nombreaux;

                cout<<"\nSe ha introducido el cuerpo: "<<nodo->nombre<<" a la galaxia "<<ar->NombreArbol<<endl;

                nodo->izq = nodo->der = NULL;
                return nodo;
            }
            else
            {
                struct nodoA *nodo;
                nodo = new struct nodoA;

                nodo_padre->der = nodo;

                nodo->tipocuerpo = cuerpo;
                nodo->masa = masa;
                nodo->distancia = distancia;
                nodo->nombre = nombreaux;

                cout<<"\nSe ha introducido el cuerpo: "<<nodo->nombre<<" a la galaxia "<<ar->NombreArbol<<endl;

                nodo->izq = nodo->der = NULL;
                return nodo;
            }
        }
}

void preOrden(nodoarbol nodo)
{
    if(nodo == NULL)
    {
        return;
    }else{
        cout << nodo->nombre << " - ";
        if(nodo->izq != NULL) preOrden(nodo->izq);
        if(nodo->der != NULL) preOrden(nodo->der);
    }
}

void inOrden(nodoarbol nodo)
{
    if(nodo == NULL)
    {
        return;
    }else{
        if(nodo->izq != NULL) inOrden(nodo->izq);
        cout << nodo->nombre << " - ";
        if(nodo->der != NULL) inOrden(nodo->der);
    }
}

void posOrden(nodoarbol nodo)
{
    if(nodo == NULL)
    {
        return;
    }else{
        if(nodo->izq != NULL) inOrden(nodo->izq);
        if(nodo->der != NULL) inOrden(nodo->der);
        cout << nodo->nombre << " - ";
    }
}

nodoA *CrearCuerpoAleat(arbol ar)
{
    struct nodoA *nodo ;
    nodo = new struct nodoA;
    string sol="S";
    string planeta="P";
    string luna="M";
    string nombreC, nombreG, nombre;

    int cuerpoR,masaR,distR;

    cuerpoR = 1 + rand() % 3;
    masaR = 1 + rand() % 20;
    distR = 1 + rand() % 1000;

    if(cuerpoR == 1)
    {
        nombreC = sol;
    }
    else if(cuerpoR == 2)
    {
        nombreC = planeta;
    }
    else if(cuerpoR == 3)
    {
        nombreC = luna;
    }

    if(ar->NombreArbol == "Andromeda")
    {
        nombreG = "AN";

    }else if(ar->NombreArbol == "Centauro"){
        nombreG = "CE";

    }else if(ar->NombreArbol == "Via Lactea")
    {
    nombreG = "VL";

    }else if(ar->NombreArbol == "Leo")
    {
        nombreG = "LE";
    }

    nodo = InsertarCuerpo(ar, nombreC,masaR,distR, nombreG);
    return nodo;
}


void IntroducirCuerpo(arbol ar,string cuerpo, int masa, int distancia)
{
    string nombreGaux;

    if(ValidarDatos(cuerpo, masa, distancia))
    {
        if(ar->NombreArbol == "Andromeda")
        {
            nombreGaux = "AN";

        }else if(ar->NombreArbol == "Centauro")
        {
            nombreGaux = "CE";

        }else if(ar->NombreArbol == "Via Lactea")
        {
            nombreGaux = "VL";

        }else if(ar->NombreArbol == "Leo")
        {
           nombreGaux = "LE";
        }

        InsertarCuerpo(ar, cuerpo, masa, distancia, nombreGaux);
        cout<<" "<<endl;
        preOrden(ar->raiz);
    }
}

void BuscarCuerpo(arbol ar, string nombreaux)
{
    struct nodoA *nodo_aux;
    nodo_aux = new struct nodoA;

    nodo_aux = ar->raiz;

     while((nodo_aux!=NULL) && Orden(nombreaux, nodo_aux->nombre) != 0)
    {
            if(nombreaux < nodo_aux ->nombre) nodo_aux = nodo_aux->izq;
            else nodo_aux = nodo_aux->der;
    }

    if(Orden(nombreaux, nodo_aux->nombre) == 0)
    {

        cout << "\nNombre: "<< nodo_aux->nombre <<"\nMasa: "<<nodo_aux->masa<<"\nDistancia: "<<nodo_aux->distancia;
        return;
    }
    else
    {
        cout << "El nodo no existe";
    }
}

nodoA *minimo(nodoarbol nodo)
{
    if(nodo == NULL)
    {
        return NULL;
    }
    if(nodo->izq)
    {
        return minimo(nodo->izq);
    }
    else
    {
        return nodo;
    }
}

bool EsHoja(arbol a,nodoarbol r)
{
   return !r->der && !r->izq;
}

void Borrar(arbol a, string nombre)
{
    struct nodoA *padre, *actual, *nodo;
    padre = new struct nodoA;
    actual = new struct nodoA;
    nodo = new struct nodoA;

    string aux;

    padre = NULL;
    actual = a->raiz;

    while(actual != NULL)
    {
        if(nombre == actual->nombre)
        {
            if(EsHoja(a, actual))
            {
                if(padre)
                { if(padre->der == actual) padre->der = NULL;
                    else if(padre->izq == actual) padre->izq = NULL;
                free(actual);
                actual = NULL;
                return;
                }
            }else
            {/*Buscar nodo*/
                padre = actual;
                if(actual->der){
                    nodo = actual->der;
                    while(nodo->izq){
                        padre = nodo;
                        nodo = nodo->izq;
                    }
                }
                else{
                    nodo = actual->izq;
                    while(nodo->der)
                    {
                        padre = nodo;
                        nodo = nodo->der;
                    }
                }
                /*Intercambio*/
                aux = actual->nombre;
                actual->nombre = nodo->nombre;
                nodo->nombre = aux;
                actual = nodo;
            }
        }
        else{
            padre = actual;
            if(nombre > actual->nombre) actual = actual->der;
            else if(nombre < actual->nombre) actual = actual->izq;
        }
    }
}

nodoA *CuerposAleatorios(arbol ar)
{
    struct nodoA *nodo ;
    nodo = new struct nodoA;

    nodo = CrearCuerpoAleat(ar);
    preOrden(ar->raiz);
    cout<<" "<<endl;

    return nodo;
}


nodoA *CuerposAltElim(arbol ar)
{
    struct nodoA *nodo ;
    nodo = new struct nodoA;

    nodo = CrearCuerpoAleat(ar);
    preOrden(ar->raiz);
    cout<<" "<<endl;

    Borrar(ar, nodo->nombre);
    cout<<"Se ha eliminado "<<nodo->nombre<<endl;

    return nodo;



}

VerABBSimulacion(arbol an, arbol ce, arbol vl, arbol le)
{
    cout<<" "<<endl;
    cout<<" "<<an->NombreArbol<<":      ";
    preOrden(an->raiz);

    cout<<" "<<endl;
    cout<<" "<<ce->NombreArbol<<":       ";
    preOrden(ce->raiz);

    cout<<" "<<endl;
    cout<<" "<<vl->NombreArbol<<":     ";
    preOrden(vl->raiz);

    cout<<" "<<endl;
    cout<<" "<<le->NombreArbol<<":             ";
    preOrden(le->raiz);
    cout<<" "<<endl;
}

void EventoLlegada(arbol ar, arbol an, arbol ce, arbol vl, arbol le)
{
    nodoA *nodo_aux;
    nodo_aux = new struct nodoA;

    nodo_aux = CrearCuerpoAleat(ar);
    VerABBSimulacion(an,ce,vl,le);
    cout<<"Llegada "<<nodo_aux->nombre<<" al ABB "<<ar->NombreArbol<<endl;
    cout<<"_________________________________________________________________ "<< endl;

}

void EventoProc(arbol ar, arbol an, arbol ce, arbol vl, arbol le)
{
    nodoA *nodo_aux;
    nodo_aux = new struct nodoA;

    if(ArbolVacio(ar) == false)
    {
        nodo_aux = minimo(ar->raiz);
        Borrar(ar, nodo_aux->nombre);
        VerABBSimulacion(an,ce,vl,le);
        cout<<"Procesamiento OK "<<nodo_aux->nombre<<" del ABB "<<ar->NombreArbol<<endl;
        cout<<"_________________________________________________________________ "<< endl;
    }
    else if(ArbolVacio(ar))
    {
        VerABBSimulacion(an,ce,vl,le);
        cout<<"El arbol "<< ar->NombreArbol << " esta vacio"<<endl;
        cout<<"_________________________________________________________________ "<< endl;
    };

}


int main()
{
    string AN = "Andromeda";
    string CE = "Centauro";
    string VL = "Via Lactea";
    string LE = "Leo";

    string P = "P";
    string S = "S";
    string M = "M";

    int input, ginput, minput, dinput;
    string cinput;

    srand (time(NULL));

   arbol ArbolAN = CrearArbol(AN);
   arbol ArbolCE = CrearArbol(CE);
   arbol ArbolVL = CrearArbol(VL);
   arbol ArbolLE = CrearArbol(LE);

   struct nodoA* root = NULL;


        do
        {
            cout<<" "<<endl;
            cout<<"Disponemos de los siguientes telescopios: Andromeda (AN), Centauro (CE), Via Lactea (VL), Leo (LE).\n Seleccione la funcion que desea realizar\n";
            cout<<"  1.Introducir manualmente un cuerpo en cualquier ABB\n";
            cout<<"  2.Buscar cualquier cuerpo celeste en el ABB que se indique\n";
            cout<<"  3.Imprimir los cuerpos del ABB de cualquier froma\n";
            cout<<"  4.Borrar un cuerpo celeste, introducido por teclado, del ABB que se indique.\n";
            cout<<"  5.Introducir un número y crear dicha cantidad de cuerpos celestes de cualquier galaxia.\n";
            cout<<"  6.Introducir un número y crear dicha cantidad de cuerpos celestes de cualquier galaxia y eliminarlos.\n";
            cout<<"  7.Iniciar simulacion\n";
            cout<<"  8.Cerrar aplicacion\n";

            cin>>input;

            switch (input)
            {
                case 1:
                    //Introducir manualmente un cuerpo en cualquier ABB
                    cout<<"Seleccione galaxia: \n";
                    cout<<"Andromeda (1), Centauro (2), Via Lactea (3), Leo (4).\n";
                    cin>>ginput;

                    cout<<"Introduzca el tipo de cuerpo:\n Estrella(S), Planeta(P) o Luna(M)\n";
                    cin>>cinput;

                    cout<<"Introduzca la masa del cuerpo [0...20]\n";
                    cin>>minput;

                    cout<<"Introduzca la distancia a la que se encuentra el cuerpo [0...1000]\n";
                    cin>>dinput;

                    switch (ginput)
                    {
                    case 1:
                        IntroducirCuerpo(ArbolAN, cinput, minput, dinput);
                        break;

                    case 2:
                        IntroducirCuerpo(ArbolCE, cinput, minput, dinput);
                        break;

                    case 3:
                        IntroducirCuerpo(ArbolLE, cinput, minput, dinput);
                        break;

                    case 4:
                        IntroducirCuerpo(ArbolVL, cinput, minput, dinput);

                        break;
                    }
                    break;

                case 2:
                {//Buscar cualquier cuerpo celeste en el ABB que se indique
                   string nominput;

                    cout<<"Seleccione galaxia:\n";
                    cout<<"Andromeda (1), Centauro (2), Via Lactea (3), Leo (4).\n";
                    cin>>ginput;
                    cout<<"Inserta el nombre del cuerpo que quieres buscar.\n";
                    cin>>nominput;

                    switch (ginput)
                    {
                    case 1:
                        BuscarCuerpo(ArbolAN, nominput);
                        break;

                    case 2:
                        BuscarCuerpo(ArbolCE, nominput);
                        break;

                    case 3:
                        BuscarCuerpo(ArbolVL, nominput);
                        break;

                    case 4:
                        BuscarCuerpo(ArbolLE, nominput);
                        break;
                    }
                    break;
                }
                case 3:
                {  //Imprimir los cuerpos del ABB de cualquier froma
                    cout<<"Seleccione galaxia:\n";
                    cout<<"Andromeda (1), Centauro (2), Via Lactea (3), Leo (4).\n";
                    cin>>ginput;
                    cout<<"Inserta la forma de imprimir el ABB: Preorden(1), Inorden(2), Posorden(3).\n";
                    int finput;
                    cin>>finput;

                    switch (finput)
                    {
                        case 1:
                            switch(ginput)
                            {
                                case 1:
                                    preOrden(ArbolAN->raiz);
                                    break;

                                case 2:
                                    preOrden(ArbolCE->raiz);
                                    break;

                                case 3:
                                    preOrden(ArbolVL->raiz);
                                    break;

                                case 4:
                                    posOrden(ArbolLE->raiz);
                            }
                            break;

                        case 2:
                            switch(ginput)
                            {
                                case 1:
                                    inOrden(ArbolAN->raiz);
                                    break;

                                case 2:
                                    inOrden(ArbolCE->raiz);
                                    break;

                                case 3:
                                    inOrden(ArbolVL->raiz);
                                    break;

                                case 4:
                                    inOrden(ArbolLE->raiz);
                            }
                            break;

                        case 3:
                            switch(ginput)
                            {
                                case 1:
                                    posOrden(ArbolAN->raiz);
                                    break;

                                case 2:
                                    posOrden(ArbolCE->raiz);
                                    break;

                                case 3:
                                    posOrden(ArbolVL->raiz);
                                    break;

                                case 4:
                                    posOrden(ArbolLE->raiz);
                            }
                            break;

                        break;
                        }
                    break;
                }

                case 4:
                {//Borrar un cuerpo celeste, introducido por teclado, del ABB que se indique.
                   string nominput;

                    cout<<"Seleccione galaxia:\n";
                    cout<<"Andromeda (1), Centauro (2), Via Lactea (3), Leo (4).\n";
                    cin>>ginput;
                    cout<<"Inserta el nombre del cuerpo que quieres eliminar.\n";
                    cin>>nominput;

                    switch (ginput)
                    {
                        case 1:
                            Borrar(ArbolAN, nominput);
                            break;

                        case 2:
                            Borrar(ArbolCE, nominput);
                            break;

                        case 3:
                            Borrar(ArbolVL, nominput);
                            break;

                        case 4:
                            Borrar(ArbolLE, nominput);
                            break;
                        }
                        break;
                    }
                case 5:
                {//Introducir un número y crear dicha cantidad de cuerpos celestes de cualquier galaxia.
                    int n, i, galax;
                    cout<<"Inserta cuantos cuerpos quieres insertar.\n";
                    cin>>n;

                    for(i=0; i<n; i++)
                    {
                        galax = 1 + rand() % 4;

                        if(galax == 1)
                        {
                            CuerposAleatorios(ArbolAN);
                        }
                        else if(galax == 2)
                        {
                            CuerposAleatorios(ArbolCE);
                        }
                        else if(galax == 3)
                        {
                            CuerposAleatorios(ArbolVL);
                        }
                        else if(galax == 4)
                        {
                            CuerposAleatorios(ArbolVL);
                        }
                    }
                    break;
                }
                case 6:
                {//Introducir un número y crear dicha cantidad de cuerpos celestes de cualquier galaxia y eliminarlos
                    int n, i, galax;
                    cout<<"Inserta cuantos cuerpos quieres insertar.\n";
                    cin>>n;

                    for(i=0; i<n; i++)
                    {
                        galax = 1 + rand() % 4;

                        if(galax == 1)
                        {
                            CuerposAltElim(ArbolAN);
                        }
                        else if(galax == 2)
                        {
                            CuerposAltElim(ArbolCE);
                        }
                        else if(galax == 3)
                        {
                            CuerposAltElim(ArbolVL);
                        }
                        else if(galax == 4)
                        {
                            CuerposAltElim(ArbolVL);
                        }
                    }
                    break;
                }
                case 7:
                {
                    int j,h, galax;
                    cout<<"\n ++Llegada de los nodos ++ \n";
                    for(j=0;j<=6;j++)
                    {
                        galax = 1 + rand() % 4;
                        //Creo cuerpos aleatorios a lo largo de un minuto 5*12=60
                        if(galax == 1)
                        {
                            EventoLlegada(ArbolAN, ArbolAN, ArbolCE, ArbolVL, ArbolLE);

                        }
                        else if(galax == 2)
                        {
                            EventoLlegada(ArbolCE, ArbolAN, ArbolCE, ArbolVL, ArbolLE);
                        }
                        else if(galax == 3)
                        {
                            EventoLlegada(ArbolVL, ArbolAN, ArbolCE, ArbolVL, ArbolLE);
                        }
                        else if(galax == 4)
                        {
                            EventoLlegada(ArbolLE, ArbolAN, ArbolCE, ArbolVL, ArbolLE);
                        }
                        Sleep(5000);
                    }
                    cout<<"\n ++Procesamiento de los nodos ++ \n";
                    for(h=0;h<=6;h++)
                    {
                        int grand;
                        grand = 1 + rand() % 4;

                        if(grand == 1)
                        {
                            EventoProc(ArbolAN ,ArbolAN, ArbolCE, ArbolVL, ArbolLE);

                        }
                        else if(grand == 2)
                        {
                            EventoProc(ArbolCE, ArbolAN, ArbolCE, ArbolVL, ArbolLE);
                        }
                        else if(grand == 3)
                        {
                            EventoProc(ArbolVL, ArbolAN, ArbolCE, ArbolVL, ArbolLE);
                        }
                        else if(grand == 4)
                        {
                            EventoProc(ArbolLE, ArbolAN, ArbolCE, ArbolVL, ArbolLE);
                        }
                    Sleep(5000);
                    }
                    break;
                    cout << "+++ FIN SIMULACION";
                }
                case 8:
                    return 0;

            }

        }while(input != 8);
}


