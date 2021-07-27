#ifndef GESTIONARCHIVOS_H_INCLUDED
#define GESTIONARCHIVOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "gestionUsuario.h"

//-----------------------------------------------------PROTOTIPADOS-----------------------------------------------------
stUsuario buscarNombreInicioSesion(char nombre[], int*flag);
void agregarUsuarioToArchivo (stUsuario u);
stUsuario buscarId (int id, int*flag);
int buscarPosicionUsuarioArchivo(stUsuario usuario);
void modificarClienteArchivo(stUsuario c, int flag, stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void archivoToArreglo(stUsuario a[]);
int usuariosActivos();
void todosLosUsuarios();
void todosLosUsuariosEliminados();
void modificacionUsuario (stUsuario u);
void eliminarCancionArchivoPlaylist (int idC, int idU);
int cuentaRegistroArchivo();
int idCancionesAutomaticas();
void cargarCancionArchivo(stCelda**ADL, int*validos, nodoArbolCancion**arbol, stUsuario u);
void eliminarCancionArchivo (int id);
stCancion retornaCancionEliminada (int id);
int cancionesActivas();
void modificarCancionArchivo (int id, stCancion cModificada);
int registrosCanciones ();
int archivoCancionesToArreglo(stCancion arreglo[]);
stCancion buscarCancionRetornarla (int id);
void guardarCancionEnArchPlayl(int idCancion, int idUsuario);
int cuentaRegistros(char archivo[], int dim);
void restaurarCancionArchivo (int id);
stCancion buscarCancionPorId (int id);
void mensajeAdministrador (char mensaje[], char usuario[]);

#endif // GESTIONARCHIVOS_H_INCLUDED
