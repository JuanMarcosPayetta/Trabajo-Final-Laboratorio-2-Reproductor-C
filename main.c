
/**********************************************************************************
*
*         Desarrolado por Dolores Bruzzone - Juan Payetta - Pablo Payetta
*                              Comision N°3
*          para la Universidad Tecnologica Nacional Regional Mar Del Plata
*
*                       Materia: LABORATORIO DE COMPUTACION II
*
*
*************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "arbolCanciones.h"
#include "gestionCanciones.h"
#include "gestionPlaylist.h"
#include "gestionUsuario.h"
#include "sistema.h"
#include "gestionMenus.h"
#include "gestionMostrar.h"
#include "gestionArchivos.h"
#include "gestionValidacion.h"
#include "lista.h"


int main()
{
//COLOR PANTALLA//
system("color 0B"); //coloca de un color la pantalla y tipografia

//MEMORIA//
stCelda*ADL; //arreglo dinamico de tipo stCelda para cargar todos los usuarios activos
int validos=0;
nodoArbolCancion*arbol=inicArbol(); //arbol inicializado en NULL

validos=cargarADL(&ADL); //cargo en el arreglo de listas los usuarios activos cargados en el archivo de usuarios.dat (antes de que inicie el menu)

int cantidadCanciones=registrosCanciones (); //cuento la cantidad de canciones en canciones.dat (no eliminadas)
//printf("Canciones sin eliminar: %d\n", cantidadCanciones);

stCancion*arreglo=(stCancion*)malloc(cantidadCanciones*sizeof(stCancion)); //creo un arreglo dinamico de dimension justa con la cantidad de registros de canciones.dat
int validosCanciones=archivoCancionesToArreglo(arreglo); //cargo el arreglo dinamico con las canciones de canciones.dat (no eliminadas)
arbol=balanceo(arbol, arreglo, validosCanciones); //le pasa todas las canciones del arreglo al arbol de canciones


//***MENU***//

printf("\n\n\n\n");
printf("\t\t\t\t********************************************************\n");
printf("\t\t\t\t*<>*<>*<>*<>*< REPRODUCTOR DE MUSICA D-JP >*<>*<>*<>*<>*\n");
printf("\t\t\t\t\t\t\tBienvenido\n");
printf("\t\t\t\t********************************************************\n\n");
printf("\t\t\t\t\tPresione cualquier tecla para continuar\n");
getch();
menuInicio (&ADL, &validos, arbol); //inicio

    return 0;
}

