#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "gestionCanciones.h"
#include "lista.h"


//inicializo la lista en NULL
nodoListaCancion*inicLista()
{
    return NULL;
}

//creo un nodo de tipo stCancion que almacena una cancion
nodoListaCancion*crearNodo(stCancion cancion)
{
    nodoListaCancion*aux =(nodoListaCancion*)malloc(sizeof(nodoListaCancion));
    aux->c=cancion;
    aux->sig=NULL;

    return aux;
}

//agrega un nodo al final de la lista
nodoListaCancion*agregarAlFinal(nodoListaCancion*lista, nodoListaCancion*nuevoNodo)
{
    nodoListaCancion*ultimo;
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        ultimo=buscarUltimo(lista);
        ultimo->sig=nuevoNodo;
    }
    return lista;
}

//busco el ultimo nodo de la lista
nodoListaCancion*buscarUltimo(nodoListaCancion*lista)
{
    nodoListaCancion*seg=lista;
    while(seg->sig!=NULL)
    {
        seg=seg->sig;
    }
    return seg;
}

//borra una cancion de la lista de canciones
nodoListaCancion*borrarCancion(nodoListaCancion*lista, int id)
{
    nodoListaCancion*aux;
    if(lista!=NULL) //analizo que el dato este en el primer nodo de la lista
    {
        if(lista->c.idCancion==id)
        {
            aux=lista;
            lista=lista->sig;
            free(aux);
        }
        else
        {
            nodoListaCancion*ant=lista;
            nodoListaCancion*seg=lista->sig;
            while((seg!=NULL) && (seg->c.idCancion!=id)) // recorro
            {
                ant=seg;
                seg=seg->sig;
            }

            if(seg!=NULL) //si no es nul es porque encontro el dato antes del final
            {
                ant->sig=seg->sig;
                free(seg);
            }

        }
    }

    return lista;
}


//borra la lista de canciones completa
nodoListaCancion*borrarListaCompleta(nodoListaCancion*lista)
{
    nodoListaCancion*seg=lista;

    if(lista!=NULL)
    {
        while(lista!=NULL)
        {
            lista=lista->sig;   //al final la lista quedara apuntando a NULL
            free(seg);
            seg=lista;
        }
    }

    return lista;
}


//verifica que una cancion este o no agregada a la lista ( a traves del nombre de la cancion)
int encontrarElementoLista (nodoListaCancion*lista, int id)
{
    nodoListaCancion*seg=lista;
    int flag=99;

    if(lista!=NULL)
    {
        while((seg!=NULL) && (flag!=100))
        {
            if(seg->c.idCancion==id)
            {
                flag=100;
            }
            else
            {
                seg=seg->sig;
            }
        }
    }

    return flag;
}

