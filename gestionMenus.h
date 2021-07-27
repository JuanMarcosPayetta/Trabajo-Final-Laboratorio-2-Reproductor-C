#ifndef GESTIONMENUS_H_INCLUDED
#define GESTIONMENUS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------PROTOTIPADOS----------------------------------------------------------
void menuInicio (stCelda**ADL, int*validos, nodoArbolCancion*arbol);
void registrarse(stCelda**ADL, int*validos, nodoArbolCancion*arbol);
stUsuario subMenModificarRegistroUsuario(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void menuCliente(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void menuPpalAdmin(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void subMenuAdmin(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void subMenuAdminCanciones (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void subMenModifRegAdmin(stUsuario u, stUsuario c, stCelda**ADL, int*validos, nodoArbolCancion*arbol);
stCancion menuModificacionCanciones (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u, stCancion c);
void altaDeUsuarios(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);
void listadoCanciones (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u);

#endif // GESTIONMENUS_H_INCLUDED

