#ifndef ARBOLCANCIONES_H_INCLUDED
#define ARBOLCANCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "gestionCanciones.h"


//-----------------------------------------------------ESTRUCTURA---------------------------------------------------------------

//Arbol de Canciones
typedef struct
{
    stCancion c;
    struct nodoArbolCancion * izq;
    struct nodoArbolCancion * der;
} nodoArbolCancion;


//-----------------------------------------------------PROTOTIPADOS--------------------------------------------------------------
nodoArbolCancion*inicArbol();
nodoArbolCancion*crearNodoArbol (stCancion cancion);
nodoArbolCancion*InsertarCancionArbol (nodoArbolCancion*arbol, nodoArbolCancion*cancion);
nodoArbolCancion*balanceo(nodoArbolCancion*arbol, stCancion arreglo[], int validos); //balancear arbol
nodoArbolCancion*arrayToArbolBalanceado(nodoArbolCancion*arbol, stCancion arreglo[], int base, int tope); //balancear arbol
void mostrarArbol(nodoArbolCancion*arbol);
void mostrarArbol2 (stCancion cancion);
void inOrder(nodoArbolCancion*arbol);
void mostrarArregloCanciones (stCancion arreglo[], int validos);
nodoArbolCancion*buscarCancionId(nodoArbolCancion*arbol, int id);
nodoArbolCancion*borrarCancionArbol(nodoArbolCancion*arbol, int id);
nodoArbolCancion*masGrandeDer(nodoArbolCancion*arbol);
nodoArbolCancion*masGrandeIzq(nodoArbolCancion*arbol);
nodoArbolCancion*buscarCancionGen(nodoArbolCancion*arbol, char gen[]);





#endif // ARBOLCANCIONES_H_INCLUDED
