#ifndef GESTIONVALIDACION_H_INCLUDED
#define GESTIONVALIDACION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "gestionUsuario.h"
#include "sistema.h"

//-----------------------------------------------------PROTOTIPADOS----------------------------------------------------------
void contraseniaAdministrador (stCelda**ADL, int*validos, nodoArbolCancion*arbol);
void cantidadMinima (char palabra[]);
int nombreDisponible (char nombre[]);
int validarAnioNacimiento(int anio);
stUsuario  generoValido (stUsuario u);
int usuariosTotales ();
int validCorreoE(char mail[]);
int verifTipoUsuario (stUsuario u);
int verifAprobUsuario(stUsuario u);
int validarContrasenia (char contrasenia [],stUsuario u);
int validarCancionRepetida (char nombreCancion[]);
int validarCancionEliminada(int id);
int verificarCancionesEliminadas();
int verificarCancionesGenero(char genero[]);
int verificarExisteId(int id);
stCancion validarAnioCancion (stCancion c);
int validarIdCancion (int id);
void buscarCancionGenero (stCancion**ADL, int validos, char genero[]);
int verificarCancionesTitulo(char titulo[]);
int existeUsuariosEliminados();

#endif // GESTIONVALIDACION_H_INCLUDED
