#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "arbolCanciones.h"


//inicializa el arbol en NULL
nodoArbolCancion*inicArbol()
{
    return NULL;
}

//creo un nodo para cargarle una cancion e insertarlo al arreglo
nodoArbolCancion*crearNodoArbol (stCancion cancion)
{
    nodoArbolCancion*aux=(nodoArbolCancion*)malloc(sizeof(nodoArbolCancion)); //le doy dimension al nodo
    aux->c=cancion; //guardo la cancion en el nodo
    aux->der=NULL; //inicializo cada lado del arbol en null
    aux->izq=NULL;

    return aux;
}

//inserta un nodo en el arbol ordenado por ID
nodoArbolCancion*InsertarCancionArbol (nodoArbolCancion*arbol, nodoArbolCancion*cancion)
{
    if(arbol==NULL)
    {
        arbol=cancion;

    }
    else
    {
        if(cancion->c.idCancion>arbol->c.idCancion) //si el ID es mayor al que esta en nodo arbol, inserto en la derecha
        {
            arbol->der=InsertarCancionArbol(arbol->der, cancion);
        }
        else
        {
            arbol->izq=InsertarCancionArbol(arbol->izq, cancion); //si el ID es menor al que esta en nodo arbol, inserto en la izquierda
        }
    }

    return arbol;
}



//borra una cancion del arbol (nodo)
nodoArbolCancion*borrarCancionArbol(nodoArbolCancion*arbol, int id)
{
    if(arbol!=NULL)
    {
        if(arbol->c.idCancion==id)  // el dato buscado esta en el nodo Arbol
        {
            if(arbol->izq)  //analizar el lado izquierdo
            {
                nodoArbolCancion*mayorDer=masGrandeDer(arbol->izq);
                arbol->c=mayorDer->c;
                arbol->izq=borrarCancionArbol(arbol->izq,mayorDer->c.idCancion);
            }
            else if(arbol->der) //analizo el lado derecho
            {
                nodoArbolCancion*mayorIzq=masGrandeIzq(arbol->der);
                arbol->c=mayorIzq->c;
                arbol->der=borrarCancionArbol(arbol->der,mayorIzq->c.idCancion);
            }
            else //el arbol no tiene hijos, osea que es una hoja.
            {
                free(arbol);
                arbol=NULL;
            }
        }
        else if (arbol->c.idCancion<id) //si el id del arbol es menor a la id pasada por parametro
        {
            arbol->der=borrarCancionArbol(arbol->der,id);
        }
        else
        {
            arbol->izq=borrarCancionArbol(arbol->izq,id);
        }
    }
    return arbol;
}


//borrar nodo
nodoArbolCancion*masGrandeDer(nodoArbolCancion*arbol)
{
    nodoArbolCancion*x=arbol;
    if(arbol!=NULL)
    {
        if(arbol->der)
        {
            x=masGrandeDer(arbol->der);
        }
    }
    return x;
}

//borrar nodo
nodoArbolCancion*masGrandeIzq(nodoArbolCancion*arbol)
{
    nodoArbolCancion*x=arbol;
    if(arbol!=NULL)
    {
        if(arbol->izq)
        {
            x=masGrandeIzq(arbol->izq);
        }
    }
    return x;
}


//muestra el arreglo de canciones
void mostrarArregloCanciones (stCancion arreglo[], int validos)
{
    int i=0;
    while(i<validos)
    {
        mostrarDatosCancion(arreglo[i]);
        i++;
    }
}


//le envia los parametros a la funcion que carga el arbol con los datos del arreglo de canciones
nodoArbolCancion*balanceo(nodoArbolCancion*arbol, stCancion arreglo[], int validos)
{
    int base=0;//primer posicion del arreglo
    int tope=validos-1; //ultima posicion con datos del arreglo

    arbol=arrayToArbolBalanceado(arbol,arreglo,base,tope);

    return arbol;
}

//Invoca la funcion que carga el arbol de forma balanceada para que no quede como una lista (utiliza un arreglo ordenado por id)
nodoArbolCancion*arrayToArbolBalanceado(nodoArbolCancion*arbol, stCancion arreglo[], int base, int tope)
{
    int medio;

    if(!(base>tope))
    {
        medio=(base+tope)/2;
        arbol=InsertarCancionArbol(arbol, crearNodoArbol(arreglo[medio])); //inserto por ID

        arbol->izq=arrayToArbolBalanceado(arbol->izq, arreglo, base, medio-1);
        arbol->der=arrayToArbolBalanceado(arbol->der, arreglo, medio+1, tope);
    }

    return arbol;
}



void mostrarArbol(nodoArbolCancion*arbol)
{
    mostrarArbol2(arbol->c);
}

void mostrarArbol2 (stCancion cancion)
{
    mostrarDatosCancionSimple(cancion);
}

//muestra el arbol
void inOrder(nodoArbolCancion*arbol)
{
    if(arbol!=NULL)
    {
        inOrder(arbol->izq);
        mostrarArbol(arbol);
        inOrder(arbol->der);
    }
}


//busca una cancion en el arbol de canciones a traves del id (le paso el id de la cancion elegida y lo busca en el arbol). Retorna la cancion elegida para agregarla a la playlist.
nodoArbolCancion*buscarCancionId(nodoArbolCancion*arbol, int id)
{
    nodoArbolCancion*buscado=NULL;//NULL por si no encuentra el nodo
    if(arbol!=NULL)
    {
        if(arbol->c.idCancion==id) //compara legajo con el nodo donde esta parado
        {
            buscado=arbol;
        }
        else
        {
            if(id>arbol->c.idCancion) //si no lo encuentra, se corre hacia derecha o izquierda, llama a la funcion, y compara nuevamente arriba (if) con el nodo donde se paro ahora
            {
                buscado=buscarCancionId(arbol->der, id);
            }
            else
            {
                buscado=buscarCancionId(arbol->izq, id);
            }
        }
    }
    return buscado; //retorna la cancion para almacenarla en la playlist
}

//busca una cancion por genero en el arbol
nodoArbolCancion*buscarCancionGen(nodoArbolCancion*arbol, char gen[])
{
    nodoArbolCancion*buscado=NULL;//NULL por si no encuentra el nodo
    if(arbol!=NULL)
    {
        if(strcmpi(arbol->c.genero,gen)==0) //compara legajo con el nodo donde esta parado
        {
            buscado=arbol;
        }
        else
        {
            if(strcmpi(arbol->c.genero,gen)>0) //si no lo encuentra, se corre hacia derecha o izquierda, llama a la funcion, y compara nuevamente arriba (if) con el nodo donde se paro ahora
            {
                buscado=buscarCancionGen(arbol->der, gen);
            }
            else
            {
                buscado=buscarCancionGen(arbol->izq, gen);
            }
        }
    }
    return buscado; //retorna la cancion para almacenarla en la playlist
}



