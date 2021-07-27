#ifndef GESTIONUSUARIO_H_INCLUDED
#define GESTIONUSUARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "arbolCanciones.h"
#include "lista.h"




//-----------------------------------------------------ESTRUCTURAS-----------------------------------------------------------

//Datos Usuario (cliente/administrador)
typedef struct
{
    int idUsuario;
    char nombreUsuario[30];
    char pass[20];
    int anioNacimiento;
    char genero;
    char pais[20];
    char correoElectronico[50];
    int eliminado; /// indica 1 o 0 si el cliente fue eliminado
    int aprobado;/// indique 1 o 0 si el cliente esta aprobado por el admin
    int tipoUsuario;///1 admin , 0 usuario
} stUsuario;


//Arreglo de listas (ADL)
typedef struct
{
    stUsuario usr;
    nodoListaCancion * listaCanciones;
} stCelda;


//utilizada para el envio de mensajes por parte de los clientes a un administrador
typedef struct
{
    char mensaje[300];
    char nombreUsuario[20];
}stMensaje;


//Funciones utilizadas directamente por los usuarios cliente/administrador en sus menus
//-----------------------------------------------------PROTOTIPADOS----------------------------------------------------------
//FUNCIONES USUARIO CLIENTE
void verPerfil(stUsuario u,stCelda**ADL, int*validos, nodoArbolCancion*arbol);
stUsuario modificarPerfil(stUsuario u,stCelda**ADL, int*validos, nodoArbolCancion*arbol);
void verPlaylist (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void recomendarCancion (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void generoRecomendado (nodoArbolCancion*arbol, char gen[]);
void verGeneroMayor (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u, int posicion);
int mayorGenero (int pop, int rock, int balada, int electro, int tango, int clasica);
void eliminarCancionPlaylist (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void escucharCancion (stCelda**ADL, int idUsuario, int validos, nodoArbolCancion*arbol, stUsuario u);
void reproduccionCancion(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void enviarMensaje (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);


//FUNCIONES ADMINISTRADOR
void aprobarUsuarios (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario x);
void recuperarUsuarioCl(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario x);
void modifUssAdmin(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void darDeBajaUsuario(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario x);
void restaurarCancion (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void cancionesGenero (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void cancionesTitulo (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void buscarCancionTitulo (stCancion**ADL, int validos, char titulo[]);
int cancionToArregloConsulta (stCancion**ADL, int validos, stCancion cancion);
int cargarADLConsulta(stCancion**ADL);
void buscarCanIdArreglo (stCancion**ADL, int validos, int id);
void consultaCanciones (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void consultaExistUsuario(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void listadoUsuarios(stCelda **ADL, int *validos, nodoArbolCancion *arbol, stUsuario u);
void darDeBajaCancion(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void eliminarCancionAdminFisicamente (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void listaTotalCancionesActivas(stCelda **ADL, int *validos, nodoArbolCancion *arbol, stUsuario u);
void recibirMensaje (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void modificacionDeCanciones (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);


#endif // GESTIONUSUARIO_H_INCLUDED
