#ifndef GESTIONMOSTRAR_H_INCLUDED
#define GESTIONMOSTRAR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>


//----------------------------------------------------------PROTOTIPADOS----------------------------------------------------------
void mostrarArrayListas(stCelda**ADL, int validos, int idU);
void mostrarArchivoCanciones();
void mostrarArchivoUsuarios ();
void mostrarPlaylist (nodoListaCancion*lista);
void mostrarCancionRecomendada(stCancion cancion);
void mostrarUsuariosRecuperadosEliminados(stUsuario u, int flag, stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario x);
void mostrarCancionesEliminadas ();
void mostrarArregloCanCorto(stCancion**ADL, int validos);
void mostrarArregloCan(stCancion**ADL, int pos);
void mostrarArregloUsuarios(stUsuario a[],int validos);
void mostrarUsuariosAprobados(stUsuario u, stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario x);
void mostrarDatosUsuario(stUsuario u);
void mostrarDatosCancion(stCancion cancion);
void mostrarCancionEliminada(stCancion cancion);
void mostrarDatosCancionSimple(stCancion cancion);
void mostrarListaADL(nodoListaCancion*lista);
void mostrarADL (stCelda**ADL, int validos);
void mostrarMensajeRecibido(char mensaje[], char nombre[]);

#endif // GESTIONMOSTRAR_H_INCLUDED
