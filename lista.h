#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>


//-----------------------------------------------------ESTRUCTURAS-----------------------------------------------------

//Lista de cancanciones
typedef struct
{
    stCancion c;
    struct nodoListaCancion * sig;
} nodoListaCancion;


//-----------------------------------------------------PROTOTIPADOS-----------------------------------------------------
nodoListaCancion*inicLista();
nodoListaCancion*crearNodo(stCancion cancion);
nodoListaCancion*agregarAlFinal(nodoListaCancion*lista, nodoListaCancion*nuevoNodo);
nodoListaCancion*buscarUltimo(nodoListaCancion*lista);
nodoListaCancion*borrarCancion(nodoListaCancion*lista, int id);
nodoListaCancion*borrarListaCompleta(nodoListaCancion*lista);
int encontrarElementoLista (nodoListaCancion*lista, int id);

#endif // LISTA_H_INCLUDED
