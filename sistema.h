#ifndef SISTEMA_H_INCLUDED
#define SISTEMA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define contraseniaAdmin "enter2020" //contraseña para poder registrarse como administrador

//-----------------------------------------------------PROTOTIPADOS----------------------------------------------------------
//FUNCIONES SISTEMA
void iniciarSesion (stCelda**ADL, int*validos, nodoArbolCancion*arbol);
void continuaInicioSesion (stUsuario usuario, stCelda**ADL, int*validos, nodoArbolCancion*arbol);
void contraseniaInicioSesion(char contrasenia[],int dimension);
void ocultarContraseniaInicioSesion(char contrasenia[],int dimension);
void pedirPassDosVeces(char contrasenia[], int dimension);
void registroUsuario (stCelda**ADL, int*validos, nodoArbolCancion*arbol, int usuarioTipo);
void ingresoContraCorrecta (stUsuario usuario, stCelda**ADL, int*validos, nodoArbolCancion*arbol);
void ordenarPorNombreUsr(stUsuario a[],int validos);
char ocultarContrAdmin(char contrasenia[],int dimension);
int cargarADL(stCelda**ADL);
int agregarUsuariosActivosToADL(stCelda ** ADL, int validos, stUsuario usuario);
stUsuario cargaNombreU (stUsuario u);
stUsuario cargaAnioNac (stUsuario u);
stUsuario cargaGenero (stUsuario u);
stUsuario cargaPais(stUsuario u);
stUsuario cargaCorreoE(stUsuario u);


#endif // SISTEMA_H_INCLUDED
