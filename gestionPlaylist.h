#ifndef GESTIONPLAYLIST_H_INCLUDED
#define GESTIONPLAYLIST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "gestionUsuario.h"

//-----------------------------------------------------ESTRUCTURA-----------------------------------------------------------
//Playlist (archivo)
typedef struct
{
    int idPlaylist;
    int idUsuario;
    int idCancion;
} stPlaylist;


//-----------------------------------------------------PROTOTIPADOS----------------------------------------------------------
void pasarDeArchivoPlaylistToADL(stCelda**ADL, int validos, nodoArbolCancion*arbol, stUsuario u);
void cancionToADL(stCelda**ADL, int idCancion, int idUsuario, int validos, nodoArbolCancion*arbol, stUsuario u);
void cancionToADLInicioSesion(stCelda**ADL, int idCancion, int idUsuario, int validos, nodoArbolCancion*arbol, stUsuario u);
void pasarArchivoAListaUsuario(stCelda**ADL, int validos, int id, nodoArbolCancion*arbol, stUsuario u);
int posicionUsuarioAdl(stCelda**ADL, int validos, int idU);
void borrarMemoria(stCelda**ADL, int validos, stUsuario u);
void borrarMemoriaAdm (stCelda**ADL, int*validos);
int cargarADLTop(stPlaylist**ADL);
int cancionToADLTop (stPlaylist**ADL, int validos, stPlaylist cancion);


#endif // GESTIONPLAYLIST_H_INCLUDED
