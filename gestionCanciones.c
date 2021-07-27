#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "gestionCanciones.h"
#include "gestionValidacion.h"


//carga los datos relativos a una cancion para luego poder agregarla a el archivo de canciones.dat
stCancion IngresarDatosCancion()
{
    system("cls");
    stCancion cancion;
    cancion.idCancion= idCancionesAutomaticas(); //localiza el ultimo id del archivo de canciones.dat
    int flag=3;

    printf("********************************\n");
    printf("Ingrese el titulo de la cancion:\n");
    printf("********************************\n");
    fflush(stdin);
    gets(cancion.titulo);
    cantidadMinima(cancion.titulo); //cantidad minima de palabras

    flag=validarCancionRepetida (cancion.titulo); //valida que la cancion ingresada no exista aun en el archivo de canciones.dat

    if(flag==1)//si la cancion ya existia en el archivo
    {
        system("cls");
        printf("*****************************************************************\n");
        printf("ERROR: La cancion ingresada ya se encuentra cargada en el sistema\n");
        printf("Seleccione una tecla para continuar:\n");
        printf("******************************************************************\n");
        getch();
        cancion=IngresarDatosCancion(); //llama a la funcion nuevamente
    }

    else
    {
        cancion.idCancion++; //aumento en 1 el ultimo id (si no habia ninguno, al ser -1 comenzara desde id = 0 )
        cancion.eliminado=0; //la cancion esta activa

        system("cls");
        printf("*********************************************\n");
        printf("Ingrese el artista que interpreta la cancion:\n");
        printf("*********************************************\n");
        fflush(stdin);
        gets(cancion.artista);
        cantidadMinima (cancion.artista); //minima cantidad de letras


        system("cls");
        printf("**********************************\n");
        printf("Ingrese el album al que pertenece:\n");
        printf("**********************************\n");
        fflush(stdin);
        gets(cancion.album);
        cantidadMinima (cancion.album); //minima cantidad de letras

        system("cls");
        printf("**********************************************\n");
        printf("Ingrese el genero al que pertenece la cancion:\n");
        printf("**********************************************\n");
        fflush(stdin);
        gets(cancion.genero);
        cantidadMinima (cancion.genero); //no se limitan los generos disponibles pero si la cantidad de letras

        system("cls");
        printf("*******************************\n");
        printf("Ingrese el anio de lanzamiento:\n");
        printf("*******************************\n");
        fflush(stdin);
        scanf("%d", &cancion.anio);
        cancion=validarAnioCancion (cancion); //que el año sea valido


        system("cls");
        printf("**********************************\n");
        printf("Ingrese la duracion de la cancion:\n");
        printf("**********************************\n");
        fflush(stdin);
        scanf("%d", &cancion.duracion);


        system("cls");
        printf("*********************************************\n");
        printf("Ingrese un comentario referente a la cancion:\n");
        printf("*********************************************\n");
        fflush(stdin);
        gets(cancion.comentario); //no es necesario un minimo de letras en este punto

    }

    return cancion;
}


//solicita se ingrese el titulo de la cancion a modificar
stCancion modificarTitulo (stCancion c)
{
    system("cls");
    printf("**************************************\n");
    printf("Ingrese el nuevo titulo de la cancion:\n");
    printf("**************************************\n");
    fflush(stdin);
    gets(c.titulo);
    cantidadMinima (c.titulo); //verifica la cantidad minima de caracteres sea 3

    return c;
}

//solicita se ingrese el artista de la cancion a modificar
stCancion modificarArtista (stCancion c)
{
    system("cls");
    printf("***************************************\n");
    printf("Ingrese el nuevo artista de la cancion:\n");
    printf("***************************************\n");
    fflush(stdin);
    gets(c.artista);
    ///no se verifica la cantidad minina de letras, ya que hay artistas/grupos con nombres muy cortos (Ej.: U2)

    return c;
}

//solicita que se ingrese el genero de la cancion a modificar
stCancion modificarGenero (stCancion c)
{
    system("cls");
    printf("**************************************\n");
    printf("Ingrese el nuevo genero de la cancion:\n");
    printf("**************************************\n");
    fflush(stdin);
    gets(c.genero);
    cantidadMinima (c.genero); //verifica la cantidad minima de caracteres sea 3

    return c;
}

//solicita que se ingrese el año de la cancion a modificar
stCancion modificarAnio (stCancion c)
{
    system("cls");
    printf("************************************\n");
    printf("Ingrese el nuevo anio de la cancion:\n");
    printf("************************************\n");
    fflush(stdin);
    scanf("%d", &c.anio);
    c=validarAnioCancion (c); //verifica que sea un año valido

    return c;
}
//solicita se ingrese el nuevo nombre del album
stCancion modificarAlbum (stCancion c)
{
    system("cls");
    printf("*************************************\n");
    printf("Ingrese el nuevo album de la cancion:\n");
    printf("*************************************\n");
    fflush(stdin);
    gets(c.album);
    cantidadMinima (c.album); //verifica la cantidad minima de caracteres sea 3

    return c;
}

//solicita se ingrese un nuevo comentario a la cancion
stCancion modificarComentario (stCancion c)
{
    system("cls");
    printf("******************************************\n");
    printf("Ingrese el nuevo comentario de la cancion:\n");
    printf("******************************************\n");
    fflush(stdin);
    gets(c.comentario);
    ///no se verifica cantidad minima, ya que es posible que no haya comentarios en todas las canciones
    return c;
}



