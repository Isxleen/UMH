#include <iostream>
#include <cstdlib>
#include <time.h>
#include<stdio.h>
#include<stdlib.h>
#include <windows.h>

using namespace std;


typedef struct nodoC
{
    string Nombre;
    string cuerpo;
    int numnom;
    double masa;
    double distancia;
    struct nodoC *sig;

}nodoc;

typedef struct Cola
{
    struct nodoC *pr;
    struct nodoC *ult;;
    string NombreCola;

}*cola;


/**
Funciones
**/
cola Crearcola(string nom)
{
    struct nodoC *nodo_aux,*nodo_aux2;
    cola patimicola= new struct Cola;

    patimicola->NombreCola = nom;

    patimicola->pr = new struct nodoC; // Creo un puntero pr y otro ult
    patimicola->ult = new struct nodoC;

    patimicola->ult = NULL; //apunto ult a null
    patimicola->pr->sig = NULL; //el siguiente del primero de la cola apunta a null

    return (patimicola);
}

bool EmptyQueue(cola co)
{
    if(co->ult == NULL) return (true); else return (false);
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

void IntroducirCuerpo(cola co, string cuerpoip, double masaip, double distanciaip)
{
    string Andromeda="Andromeda";
    string Centauro="Centauro";
    string ViaLactea="Via Lactea";
    string Leo="Leo";

    struct nodoC *nodo_aux;
    nodo_aux = new struct nodoC;

    srand (time(NULL));
    int num;
    nodo_aux->numnom = 100 + rand() %((999+100) - 100);


    if(ValidarDatos(cuerpoip,masaip,distanciaip))
    {
        if(EmptyQueue(co))
        {
            co->pr->sig = nodo_aux; // Pongo el nodo seguido del primero
            nodo_aux->sig = NULL; // El puntero sig del nodo apunta a null
            co->ult = nodo_aux; //El puntero ult apunta al nodo
        }
        else if(EmptyQueue(co) == false)
        {
        co->ult->sig = nodo_aux; // pongo sig del ultimo nodo en el nodo nuevo
        co->ult = nodo_aux;      // pongo ult en el nodo
        co->ult->sig = NULL;    // Pongo el sig del ultimo nodo en NULL
        }

        if(co->NombreCola == "Andromeda")
        {
            nodo_aux->Nombre = "AN";

        }else if(co->NombreCola == "Centauro"){
            nodo_aux->Nombre = "CE";

        }else if(co->NombreCola == "Via Lactea"){
            nodo_aux->Nombre = "VL";

        }else if(co->NombreCola == "Leo")
        {
            nodo_aux->Nombre = "LE";
        }

    nodo_aux->cuerpo = cuerpoip;
    nodo_aux->masa = masaip;
    nodo_aux->distancia = distanciaip;
    }else{
    cout<<"Los valores introducidos son invalidos."<<endl;
    }
}

void VerCola(cola co)
{
    struct nodoC *nodo_aux;

    cout<<"____________________________________\n"<< endl;
    nodo_aux = new struct nodoC;

    nodo_aux = co->pr->sig;
    int cont=1;

     cout<<"Galaxia: "<<co->NombreCola << endl;
     cout<<" "<< endl;

    while (nodo_aux!=NULL)
    {
        cout<<cont<<"."<<nodo_aux->Nombre << nodo_aux->numnom << nodo_aux->cuerpo << endl;
        cout<<"Tipo:"<<nodo_aux->cuerpo << endl;
        cout<<"Masa:"<<nodo_aux->masa << endl;
        cout<<"Distancia:"<<nodo_aux->distancia << endl;
        cout<<" "<< endl;
        nodo_aux = nodo_aux->sig;
        cont++;
    }
}
struct nodoC* FirstQueue(cola co){
    if(EmptyQueue(co)){
        return NULL;
    }
    return co->pr->sig;
}

struct nodoC* LastQueue(cola co){
    if(EmptyQueue(co)){
        return NULL;
    }
    return co->ult;
}

void CoutFirstQueue (cola co) {

    struct nodoC* pr = FirstQueue(co);


    if(EmptyQueue(co) == false)
    {
        cout<<"Primer nodo:"<<pr->Nombre << pr->numnom << pr->cuerpo<< endl;
        cout<<"Tipo:"<<pr->cuerpo << endl;
        cout<<"Masa:"<<pr->masa << endl;
        cout<<"Distancia:"<<pr->distancia << endl;
        cout<<" \n"<< endl;


    struct nodoC* ultimo = LastQueue(co);
        cout<<"Primer nodo:"<<ultimo->Nombre << ultimo->numnom << ultimo->cuerpo<< endl;
        cout<<"Tipo:"<<ultimo->cuerpo << endl;
        cout<<"Masa:"<<ultimo->masa << endl;
        cout<<"Distancia:"<<ultimo->distancia << endl;
        cout<<" "<< endl;
    return;
    }else
    {
        cout<<"La cola esta vacia " << endl;
    }
}

void ExtraerCuerpo(cola co)
{
    if(EmptyQueue(co)){
        cout<<"La cola esta vacia \n";
    }
    else
    {
    struct nodoC *nodo_aux;

    nodo_aux = new struct nodoC;

    nodo_aux = co->pr->sig;

    co->pr->sig = co->pr->sig->sig;

    delete nodo_aux;

     if(co->pr->sig == NULL)
    {
        co->ult = NULL;
     }
    }
}

void CuerpoAleatorio(cola co)
{
    rand();
    string sol="S";
    string planeta="P";
    string luna="M";

    int cuerpoR,masaR,distR;

    struct nodoC *nodo_aux;
    nodo_aux = new struct nodoC;

    cuerpoR = 1 + rand() % 3;
    masaR = 1 + rand() % 20;
    distR = 1 + rand() % 1000;

    nodo_aux->masa = masaR;
    nodo_aux ->distancia = distR;

    nodo_aux->numnom = 100 + rand() %((999+100) - 100);

    if(cuerpoR == 1)
    {
        nodo_aux->cuerpo = sol;
    }
    else if(cuerpoR == 2)
    {
        nodo_aux->cuerpo = planeta;
    }
    else if(cuerpoR == 3)
    {
        nodo_aux->cuerpo = luna;
    }

    if(co->NombreCola == "Andromeda")
    {
        nodo_aux->Nombre = "AN";

    }else if(co->NombreCola == "Centauro"){
        nodo_aux->Nombre = "CE";

    }else if(co->NombreCola == "Via Lactea"){
        nodo_aux->Nombre = "VL";

    }else if(co->NombreCola == "Leo")
    {
        nodo_aux->Nombre = "LE";
    }

    if(EmptyQueue(co))
    {
        co->pr->sig = nodo_aux;
        nodo_aux->sig = NULL;
        co->ult = nodo_aux;
    }
        else if(EmptyQueue(co) == false)
        {
        co->ult->sig = nodo_aux;
        co->ult = nodo_aux;
        co->ult->sig = NULL;
        }
}

void VerColasSimulacion(cola coAn, cola coCE, cola coVL, cola coLE)
{
    struct nodoC *nodo_AN;
    struct nodoC *nodo_CE;
    struct nodoC *nodo_VL;
    struct nodoC *nodo_LE;

    nodo_AN = new struct nodoC;
    nodo_CE = new struct nodoC;
    nodo_VL = new struct nodoC;
    nodo_LE = new struct nodoC;


    //Imprimo los nombres de los cuerpos de la cola ANDROMEDA
    nodo_AN = coAn->pr->sig;
    cout<<" "<<endl;
    cout<<" "<<coAn->NombreCola<<":      ";
    while (nodo_AN!=NULL)
    {                                                                                           //
        cout<<nodo_AN->Nombre << nodo_AN->numnom << nodo_AN->cuerpo <<"  ";//Imprimo los nombres de los cuerpos que pertencen a
        nodo_AN = nodo_AN->sig;                                                               //la cola introducida
    }

    //""" CENTAURO
    nodo_CE = coCE->pr->sig;
    cout<<" "<<endl;
    cout<<" "<<coCE->NombreCola<<":       ";
        while (nodo_CE!=NULL)
    {                                                                                           //
        cout<<nodo_CE->Nombre << nodo_CE->numnom << nodo_CE->cuerpo <<"  ";//Imprimo los nombres de los cuerpos que pertencen a
        nodo_CE = nodo_CE->sig;                                                               //la cola introducida
    }

    //""" VIA LACTEA
    nodo_VL = coVL->pr->sig;
    cout<<" "<<endl;
    cout<<" "<<coVL->NombreCola<<":     ";
        while (nodo_VL!=NULL)
    {                                                                                           //
        cout<<nodo_VL->Nombre << nodo_VL->numnom << nodo_VL->cuerpo <<"  ";//Imprimo los nombres de los cuerpos que pertencen a
        nodo_VL = nodo_VL->sig;                                                               //la cola introducida
    }

    //""" LEO
    nodo_LE = coLE->pr->sig;
    cout<<" "<<endl;
    cout<<" "<<coLE->NombreCola<<":            ";
        while (nodo_LE!=NULL)
    {                                                                                           //
        cout<<nodo_LE->Nombre << nodo_LE->numnom << nodo_LE->cuerpo <<"  ";//Imprimo los nombres de los cuerpos que pertencen a
        nodo_LE = nodo_LE->sig;                                                               //la cola introducida
    }
    cout<<" "<<endl;
}

void EventosSimulacion(cola co, int num)
{
    nodoC *nodo_aux;
    nodo_aux = new struct nodoC;

    cout<<" "<<endl;
    cout<<" EVENTO:         ";

    if(num == 1)
    {
        nodo_aux = co->ult;
        cout<<"Llegada "<< nodo_aux->Nombre<<nodo_aux->numnom<<nodo_aux->cuerpo<<" a la cola "<<co->NombreCola<<endl;
        cout<<"_________________________________________________________________ "<< endl;
    }
    else if(num == 2)
    {
        int prob;
        prob = 0 + rand() % 10000;
        if(EmptyQueue(co) == false)
        {
            nodo_aux = co->pr->sig;
            if(prob<=7000)
            {
            cout<<"Procesamiento OK "<< nodo_aux->Nombre<<nodo_aux->numnom<<nodo_aux->cuerpo<<" a la cola "<<co->NombreCola<<endl;
            cout<<"_________________________________________________________________ "<< endl;
            ExtraerCuerpo(co);
            }
            else
            {
            cout<<"Procesamiento KO "<< nodo_aux->Nombre<<nodo_aux->numnom<<nodo_aux->cuerpo<<" a la cola "<<co->NombreCola<<endl;
            cout<<"_________________________________________________________________ "<< endl;

            co->ult->sig = nodo_aux;
            co->ult = nodo_aux;
            co->ult->sig = NULL;
            }
        }
        else
        {
            cout<<co->NombreCola<<" esta vacia \n"<< endl;
            cout<<"_________________________________________________________________ "<< endl;
        }
    }
}

int main()
{
    string Andromeda="Andromeda";
    string Centauro="Centauro";
    string ViaLactea="Via Lactea";
    string Leo="Leo";

    string sol="S";
    string planeta="P";
    string luna="M";

    cola ColaAN = Crearcola(Andromeda);

    cola ColaCE = Crearcola(Centauro);

    cola ColaVL = Crearcola(ViaLactea);

    cola ColaLE = Crearcola(Leo);

    int input;

    int ginput;
    string cinput;
    int minput;
    int dinput;

    srand(time(NULL));

        do
        {
            cout<<"Disponemos de los siguientes telescopios: Andromeda (AN), Centauro (CE), Via Lactea (VL), Leo (LE).\n Seleccione la funcion que desea realizar\n";
            cout<<"  1.Introducir manualmente un cuerpo en cualquier cola\n";
            cout<<"  2.Extraer el primer cuerpo de la cola que se indique\n";
            cout<<"  3.Imprimir los cuerpos de la cola que se indique\n";
            cout<<"  4.Consultar que cuerpos estan en la cabecera y al final de la cola que se indique\n";
            cout<<"  5.Introducir los datos de 100 cuerpos que se generaran al azar\n";
            cout<<"  6.Iniciar simulacion\n";
            cout<<"  7.Cerrar aplicacion\n";

            cin>>input;

            switch (input)
            {
                case 1:
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
                        IntroducirCuerpo(ColaAN, cinput, minput, dinput);
                        VerCola(ColaAN);
                        break;

                    case 2:
                        IntroducirCuerpo(ColaCE, cinput, minput, dinput);
                        VerCola(ColaCE);
                        break;

                    case 3:
                        IntroducirCuerpo(ColaVL, cinput, minput, dinput);
                        VerCola(ColaVL);
                        break;

                    case 4:
                        IntroducirCuerpo(ColaLE, cinput, minput, dinput);
                        VerCola(ColaLE);
                        break;

                    }
                    break;

                case 2:
                    cout<<"Seleccione galaxia:\n";
                    cout<<"Andromeda (1), Centauro (2), Via Lactea (3), Leo (4).\n";
                    cin>>ginput;

                    switch (ginput)
                    {
                    case 1:
                        ExtraerCuerpo(ColaAN);;
                        break;

                    case 2:
                        ExtraerCuerpo(ColaCE);
                        break;

                    case 3:
                        ExtraerCuerpo(ColaVL);
                        break;

                    case 4:
                        ExtraerCuerpo(ColaLE);
                        break;
                    }
                break;

                case 3:
                    cout<<"Seleccione galaxia:\n";
                    cout<<"Andromeda (1), Centauro (2), Via Lactea (3), Leo (4).\n";
                    cin>>ginput;

                    switch (ginput)
                    {
                    case 1:
                        VerCola(ColaAN);
                        break;

                    case 2:
                        VerCola(ColaCE);
                        break;

                    case 3:
                        VerCola(ColaVL);
                        break;

                    case 4:
                        VerCola(ColaLE);
                        break;
                    }
                    break;

                case 4:
                    cout<<"Seleccione galaxia:\n";
                    cout<<"Andromeda (1), Centauro (2), Via Lactea (3), Leo (4).\n";
                    cin>>ginput;

                    switch (ginput)
                    {
                    case 1:
                        CoutFirstQueue(ColaAN);
                        break;

                    case 2:
                        CoutFirstQueue(ColaCE);
                        break;

                    case 3:
                        CoutFirstQueue(ColaVL);
                        break;

                    case 4:
                        CoutFirstQueue(ColaLE);
                        break;
                    }
                    break;

                case 5:
                    int i, galax;

                    for(i=0; i<10; i++)
                    {
                        galax = 1 + rand() % 4;

                        if(galax == 1)
                        {
                            CuerpoAleatorio(ColaAN);
                        }
                        else if(galax == 2)
                        {
                            CuerpoAleatorio(ColaCE);
                        }
                        else if(galax == 3)
                        {
                            CuerpoAleatorio(ColaVL);
                        }
                        else if(galax == 4)
                        {
                            CuerpoAleatorio(ColaLE);
                        }
                    }
                    break;

                case 6:
                    int j,h;
                    for(j=0;j<=12;j++)
                    {
                        galax = 1 + rand() % 4;
                        //Creo cuerpos aleatorios a lo largo de un minuto 5*12=60
                        if(galax == 1)
                        {
                            CuerpoAleatorio(ColaAN);
                            VerColasSimulacion(ColaAN, ColaCE, ColaVL, ColaLE);
                            EventosSimulacion(ColaAN, 1);

                        }
                        else if(galax == 2)
                        {
                            CuerpoAleatorio(ColaCE);
                            VerColasSimulacion(ColaAN, ColaCE, ColaVL, ColaLE);
                            EventosSimulacion(ColaCE, 1);


                        }
                        else if(galax == 3)
                        {
                            CuerpoAleatorio(ColaVL);
                            VerColasSimulacion(ColaAN, ColaCE, ColaVL, ColaLE);
                            EventosSimulacion(ColaVL, 1);

                        }
                        else if(galax == 4)
                        {
                            CuerpoAleatorio(ColaLE);
                            VerColasSimulacion(ColaAN, ColaCE, ColaVL, ColaLE);
                            EventosSimulacion(ColaLE, 1);
                        }
                    Sleep(5000);

                    }
                     for(h=0;h<=12;h++)
                    {
                        int grand;
                        grand = 1 + rand() % 4;

                        if(grand == 1)
                        {
                            VerColasSimulacion(ColaAN, ColaCE, ColaVL, ColaLE);
                            EventosSimulacion(ColaAN, 2);

                        }
                        else if(grand == 2)
                        {
                            VerColasSimulacion(ColaAN, ColaCE, ColaVL, ColaLE);
                            EventosSimulacion(ColaCE, 2);

                        }
                        else if(grand == 3)
                        {
                            VerColasSimulacion(ColaAN, ColaCE, ColaVL, ColaLE);
                            EventosSimulacion(ColaVL, 2);
                        }
                        else if(grand == 4)
                        {
                            VerColasSimulacion(ColaAN, ColaCE, ColaVL, ColaLE);
                            EventosSimulacion(ColaLE, 2);
                        }
                    Sleep(5000);
                    }
                default:
                    cout<<"Valor introducido no valido";
                }
            }while(input != 7);
        }




