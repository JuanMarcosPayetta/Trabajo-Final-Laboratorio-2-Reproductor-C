#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "gestionPlaylist.h"



///TODAS LAS PLAYLIST A ADL --> INICIA SESION ADMINISTRADOR
//Agrega las canciones del archivo playlist a las listas de los usuarios (unicamente cuando inicia sesion un administrador)
void pasarDeArchivoPlaylistToADL(stCelda**ADL, int validos, nodoArbolCancion*arbol, stUsuario u)
{
    stPlaylist cancion;
    FILE*archi=fopen("playlist.dat","rb"); //abro en modo lectura

    if(archi!=NULL)
    {
        while(!feof(archi)) //que pase todas las playlist hasta que llegue al final
        {
            fread(&cancion,sizeof(stPlaylist),1,archi);

            if(!feof(archi))
            {
                cancionToADLInicioSesion(ADL,cancion.idCancion, cancion.idUsuario, validos, arbol, u); //paso los datos para poder encontrar en el arbol la cancion elegida y al usuario en el ADL
            }
        }
        fclose(archi);
    }
}


///PLAYLIST DE USUARIO A ADL --> INICIA SESION USUARIO
//Pasa la playlist de un usuario cuando inicia sesion
void pasarArchivoAListaUsuario(stCelda**ADL, int validos, int id, nodoArbolCancion*arbol, stUsuario u) //debo pasarle el id del usuario que inicia sesion para comparar con los registros del archivo playlist
{
    stPlaylist cancion;
    FILE*archi=fopen("playlist.dat","rb"); //abro en modo lectura

    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&cancion,sizeof(stPlaylist),1,archi);
            if(!feof(archi))
            {
                if(cancion.idUsuario==id) //pasa al arreglo unicamente las canciones pertenecientes al registro de un usuario determinado
                {
                    cancionToADLInicioSesion(ADL,cancion.idCancion, cancion.idUsuario, validos, arbol, u); //paso los datos para poder encontrar en el arbol la cancion elegida y al usuario en el ADL
                }
            }
        }
        fclose(archi);
    }
}

//agrega una cancion a la playlist de los usuarios sin necesidad de verificar si la cancion esta repetida
void cancionToADLInicioSesion(stCelda**ADL, int idCancion, int idUsuario, int validos, nodoArbolCancion*arbol, stUsuario u)  // Busca un registro en playlist.dat y la carga en el arreglo.
{
    stCancion cancion;
    nodoListaCancion*nodoCancion;
    nodoArbolCancion*cancionBuscada;

    int pos=posicionUsuarioAdl(ADL, validos, idUsuario); //necesito la posicion en que se encuentra el usuario, comparando los idUsuario del ADL y el idUsuario del registro playlist
    if(pos!=-1) //cuando encontre la posicion
    {
        cancionBuscada=buscarCancionId(arbol, idCancion); //busca en el arbol de canciones la cancion elegida a traves de su ID y retorna la cancion

        if(cancionBuscada!=NULL) //si la cancion no fue eliminada
        {
            cancion=cancionBuscada->c;
            nodoCancion=crearNodo(cancion); //creo un nodo con la cancion
            (*ADL)[pos].listaCanciones=agregarAlFinal((*ADL)[pos].listaCanciones, nodoCancion); //agrego el nodo (cancion) al final de la lista (playlist), asi quedaran en orden de llegada
        }
    }
}


///agrega una cancion a la lista de canciones del ADL!!
void cancionToADL(stCelda**ADL, int idCancion, int idUsuario, int validos, nodoArbolCancion*arbol, stUsuario u)  // Busca un registro en playlist.dat y la carga en el arreglo.
{
    stCancion cancion;
    nodoListaCancion*nodoCancion;
    nodoArbolCancion*cancionBuscada;
    char opcion;
    int flag=99;

    int pos=posicionUsuarioAdl(ADL, validos, idUsuario); //necesito la posicion en que se encuentra el usuario, comparando los idUsuario del ADL y el idUsuario del registro playlist

    if(pos!=-1) //cuando encontre la posicion
    {
        flag=encontrarElementoLista ((*ADL)[pos].listaCanciones, idCancion); //busca si la cancion que se quiere agregar ya esta en la playlist
        if(flag==100) //si la cancion ya estaba agregada previamente
        {
            system("cls");
            printf("******************************************************************************************\n");
            printf("ERROR: la cancion fue agregada previamente a la lista\n");
            printf("Si desea seleccionar otra cancion presione cualquier tecla, caso contrario seleccione ESC:\n");
            printf("******************************************************************************************\n");

            flag=99;//renuevo flag para que al iniciar nuevamente no quede en 1
            opcion=getch();
            if(opcion!=27) //si quiere intentar agregar una cancion nuevamente
            {
                escucharCancion(ADL, idUsuario, validos, arbol, u); //te envia a la pantalla de seleccionar cancion
            }
            else //si no quiere volver a intenrar, va al menu cliente
            {
                menuCliente(ADL, validos, arbol, u); //volves al menu
            }
        }
        else
        {
            cancionBuscada=buscarCancionId(arbol, idCancion); //busca en el arbol de canciones la cancion elegida a traves de su ID y retorna la cancion

            if(cancionBuscada!=NULL) //si la cancion no fue eliminada
            {
                cancion=cancionBuscada->c; //guardo los datos de la cancion en una variable stCancion
                nodoCancion=crearNodo(cancion); //creo un nodo con la cancion
                (*ADL)[pos].listaCanciones=agregarAlFinal((*ADL)[pos].listaCanciones, nodoCancion); //agrego el nodo (cancion) al final de la lista (playlist), asi quedaran en orden de llegada
            }
        }

    }
    //NO PREGUNTO SI POS==-1 PORQUE SI EL USUARIO NO SE ENCUENTRA EN EL ARREGLO, ES PORQUE NUNCA SE REGISTRO Y POR ESO EL ARCHIVO DE USUARIOS.DAT NUNCA LO PASO AL ARRELO
}


//busca la posicion de un usuario en el ADL para asi poder agregar su cancion a la lista de canciones
int posicionUsuarioAdl(stCelda**ADL, int validos, int idU)
{
    int pos=-1;
    int i=0;
    while((i<validos) && (pos==-1))
    {
        if((*ADL)[i].usr.idUsuario!=idU) //si los ID no son iguales sigo recorriendo
        {
            i++;
        }
        else
        {
            if((*ADL)[i].usr.idUsuario==idU) //si los ID son iguales retorno la posicion (i) en que se encuentra
            {
                pos=i;
            }
        }
    }



    return pos; //retorno la posicion -> si la encontre sera (i) sino -1
}


//borra la lista del usuario al desloguear
void borrarMemoria(stCelda**ADL, int validos, stUsuario u)
{
    int pos=posicionUsuarioAdl(ADL, validos, u.idUsuario);
    getch();

    if(pos!=-1)
    {
        (*ADL)[pos].listaCanciones = borrarListaCompleta((*ADL)[pos].listaCanciones);
    }
}

//borra todas las listas de usuarios al desloguear el admin
void borrarMemoriaAdm (stCelda**ADL, int*validos)
{
    int i=0;

    while(i<(*validos))
    {
        (*ADL)[i].listaCanciones =borrarListaCompleta((*ADL)[i].listaCanciones);
        i++;
    }
}


//carga un arreglo de canciones con canciones de archivo playlist.dat
int cargarADLTop(stPlaylist**ADL)
{
    int dimension=cantidadCancionesID(); //cuenta la cantidad de canciones en playlist.dat para determinar la dimension justa para el arreglo
    int validos=0;
    stPlaylist cancion;

    (*ADL)=(stPlaylist*)malloc(dimension*sizeof(stPlaylist)); // le doy dimension justa con la cantidad de canciones en el archivo

    FILE*archi=fopen("playlist.dat","rb");
    if(archi!=NULL)
    {
        while(fread(&cancion,sizeof(stPlaylist),1,archi)>0)
        {
            validos=cancionToADLTop(ADL,validos,cancion); // cargo la cancion en el arreglo
        }
        fclose(archi);
    }
    return validos; //retorno la cantidad de usuarios que cargue en el arreglo
}


//almacena los datos de la cancion en el arreglo dinamico
int cancionToADLTop (stPlaylist**ADL, int validos, stPlaylist cancion)
{
    (*ADL)[validos].idCancion=cancion.idCancion; //agrego la cancion al arreglo en la posicion "validos" mi poosicion sin datos
    (*ADL)[validos].idPlaylist=cancion.idPlaylist;
    (*ADL)[validos].idUsuario=cancion.idUsuario;

    validos++; //sumo validos por cada cancion agregada
    return validos;
}


