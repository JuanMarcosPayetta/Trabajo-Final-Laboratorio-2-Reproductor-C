#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "gestionUsuario.h"
#include "gestionMostrar.h"



//muestra un arreglo de listas
void mostrarArrayListas(stCelda**ADL, int validos, int idU)
{
    int pos=posicionUsuarioAdl(ADL, validos, idU);

    if(pos!=-1)
    {
        //printf("USUARIO:............... %d\n",(*ADL)[pos].usr);
        mostrarListaADL((*ADL)[pos].listaCanciones);
    }
}

//muestra las canciones dentro del archivo canciones.dat
void mostrarArchivoCanciones ()
{
    stCancion aux;
    FILE*archi=fopen("canciones.dat", "rb");
    if(archi!=NULL)
    {
        while(fread(&aux, sizeof(stCancion), 1, archi)>0)
        {
            mostrarDatosCancion(aux);
        }
        fclose(archi);
    }
}

//muestra los datos cargados en el archivo de usuarios
void mostrarArchivoUsuarios ()
{
    stUsuario u;
    FILE*archi=fopen("usuarios.dat", "rb");

    printf("*************************************************\n");
    printf("*<>*<>*<>*<>*< ARCHIVO DE USUARIOS >*<>*<>*<>*<>*\n");
    printf("*************************************************\n\n");

    if(archi!=NULL)
    {
        while(fread(&u, sizeof(stUsuario), 1, archi)>0)
        {
            mostrarDatosUsuario(u);
        }
        fclose(archi);
    }
    else
    {
        printf("ERROR: El archivo no pudo escribirse\n");
    }
}

//muestra la playlist del usuario
void mostrarPlaylist (nodoListaCancion*lista)
{
    int i=0;
    nodoListaCancion*seg=lista;
    printf("*****************************************\n");
    printf("*<>*<>*<>*<>*< MI PLAYLIST >*<>*<>*<>*<>*\n");
    printf("*****************************************\n");
    if(seg!=NULL)
    {
        while(seg!=NULL)
        {
            printf("\n*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*\n");
            printf("TITULO: ..............:%s\n",seg->c.titulo);
            printf("ARTISTA:..............:%s\n",seg->c.artista);
            printf("ALBUM:................:%s\n",seg->c.album);
            printf("GENERO:...............:%s\n",seg->c.genero);
            printf("ANIO:.................:%d\n",seg->c.anio);
            printf("DURACION:.............:%d\n",seg->c.duracion);
            printf("COMENTARIO:...........:%s\n",seg->c.comentario);
            printf("ID:...................:%d\n",seg->c.idCancion);
            printf("*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*\n");
            seg=seg->sig;
        }
    }
    else
    {
        printf("Su playlist de canciones se encuentra vacia\n");
        printf("Para agregar canciones dirijase al menu <Agregar Canciones a su Playlist>\n");
    }
}

//muestra la cancion recomendada al usuario cliente
void mostrarCancionRecomendada(stCancion cancion)
{
    printf("\n*****************************************\n");
    printf("TITULO................: %s\n", cancion.titulo);
    printf("ARTISTA...............: %s\n", cancion.artista);
    printf("ALBUM.................: %s\n", cancion.album);
    printf("GENERO.................:%s\n", cancion.genero);
    printf("ID....................: %d\n", cancion.idCancion);
}


//funcion que muestra diferentes casos relativos a usuarios eliminados/recuperados
void mostrarUsuariosRecuperadosEliminados(stUsuario u, int flag, stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario x)
{
    system("cls");
    char opcion;

    if(flag!=0)
    {
        if(flag==1) //el usuario ingresado fue recuperado
        {
            printf("*********************USUARIO RECUPERADO*************************\n");
            printf("\nEl usuario ingresado ahora se encuentra activo en el sistema\n\n");

            printf("NOMBRE DE USUARIO:.......................: %s\n",u.nombreUsuario);

            printf("RECUPERADO:................................: %d\n",u.eliminado);

            printf("****************************************************************\n");

        }
        if(flag==2) //el usuario ingresado NO estaba eliminado
        {
            printf("*************************ERROR***************************\n");

            printf("El usuario ingresado ya se encuentra activo en el sistema\n");

            printf("*********************************************************\n");
        }
        if(flag==4) //el usuario ingresado fue eliminado
        {
            printf("*********************USUARIO ELIMINADO***********************\n");
            printf("\nEl usuario ingresado fue eliminado del sistema\n\n");

            printf("NOMBRE DE USUARIO:.......................: %s\n",u.nombreUsuario);

            printf("ELIMINADO:................................: %d\n",u.eliminado);

            printf("**************************************************************\n");
        }
        if(flag==5) //el usuario ingresado ya se encontraba eliminado
        {
            printf("****************************ERROR****************************\n");

            printf("El usuario ingresado ya se encontraba eliminado en el sistema\n");

            printf("*************************************************************\n");
        }
        if(flag==6) //el usuario ingresado es administrador no puede eliminarse
        {
            printf("**************************ERROR************************\n");

            printf("ERROR: El usuario que intenta eliminar es administrador\n");

            printf("*******************************************************\n");
        }
        if(flag==7) //el usuario ingresado es administrador no puede estar eliminado
        {
            printf("**************************ERROR*************************\n");

            printf("ERROR: El usuario que intenta recuperar es administrador\n");

            printf("********************************************************\n");
        }

        printf("Presione cualquier tecla para regresar al menu:\n");
        getch();
        subMenuAdmin(ADL, validos, arbol, x);
    }
    else
    {
        printf("**********************ERROR***********************\n");

        printf("El usuario ingresado no se encuentra en el sistema\n");

        printf("**************************************************\n");
    }

    printf("Presione cualquier tecla para regresar al menu:\n");
    getch();
    subMenuAdmin(ADL, validos, arbol, x);
}


//busca y muestra las canciones dentro del archivo canciones.dat
void mostrarCancionesEliminadas()
{
    stCancion aux;
    FILE*archi=fopen("canciones.dat", "rb");
    if(archi!=NULL)
    {
        while(fread(&aux, sizeof(stCancion), 1, archi)>0)
        {
            if(aux.eliminado==1)
            {
                mostrarCancionEliminada(aux);
            }
        }

        fclose(archi);
    }
}

//muestra los datos mas importantes de una cancion eliminada
void mostrarCancionEliminada(stCancion cancion)
{
    if(cancion.eliminado==1)
    {
        printf("\n*****************************************\n");
        printf("TITULO................: %s\n", cancion.titulo);
        printf("ARTISTA...............: %s\n", cancion.artista);
        printf("ALBUM.................: %s\n", cancion.album);
        printf("ID....................: %d\n", cancion.idCancion);
    }
}

//muestra la cancion completa en el arreglo
void mostrarArregloCan(stCancion**ADL, int pos)
{
    printf("*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*\n");
    printf("TITULO................: %s\n", (*ADL)[pos].titulo);
    printf("ARTISTA...............: %s\n", (*ADL)[pos].artista);
    printf("ALBUM.................: %s\n", (*ADL)[pos].album);
    printf("GENERO................: %s\n", (*ADL)[pos].genero);
    printf("DURACION..............: %d\n", (*ADL)[pos].duracion);
    printf("ANIO..................: %d\n", (*ADL)[pos].anio);
    printf("ELIMINADA.............: %d\n", (*ADL)[pos].eliminado);
    printf("ID....................: %d\n", (*ADL)[pos].idCancion);
    printf("COMENTARIO............: %s\n", (*ADL)[pos].comentario);
    printf("*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*\n\n");
}

//muestra unicamente dos parametro de una cancion en el arreglo (version reducida)
void mostrarArregloCanCorto(stCancion**ADL, int validos)
{
    int i=0;
    while(i<validos)
    {
        printf("*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*\n");
        printf("TITULO................: %s\n", (*ADL)[i].titulo);
        printf("ID....................: %d\n", (*ADL)[i].idCancion);
        printf("*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*\n\n");
        i++;
    }

}

/*
Muestra todos los datos del usuario que se encuentra en el arreglo de usuarios.
*/
void mostrarArregloUsuarios(stUsuario a[],int validos)
{
    int i=0;
    while(i<validos)
    {
        printf("*******************************************************\n\n");

        printf("ID....................: %d\n",a[i].idUsuario);

        printf("NOMBRE................: %s\n",a[i].nombreUsuario);

        printf("CORREO ELECTRONICO....: %s\n",a[i].correoElectronico);

        printf("ANIO DE NACIMIENTO....: %d\n",a[i].anioNacimiento);

        printf("GENERO................: %c\n",a[i].genero);

        printf("PAIS..................: %s\n",a[i].pais);

        printf("TIPO DE USUARIO.......: %d\n",a[i].tipoUsuario);

        printf("ESTADO................: %d\n",a[i].eliminado);

        printf("*******************************************************\n\n");

        i++;
    }
}

//muestra los usuarios aprobados por el administrador
void mostrarUsuariosAprobados(stUsuario u, stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario x)
{
    printf("****************************************************************\n");

    printf("NOMBRE DE USUARIO:.......................: %s\n",u.nombreUsuario);

    printf("APROBADO:................................: %d\n",u.aprobado);

    printf("****************************************************************\n\n");

}

//muestra por pantalla todos los datos ingresados al momento de registrarse
void mostrarDatosUsuario(stUsuario u)
{
    printf("******************************************************\n");
    printf("*<>*<>*<>*<>*< DATOS DE SU CUENTA >*<>*<>*<>*<>*\n");
    printf("******************************************************\n");

    printf("NOMBRE DE USUARIO:.......................: %s\n",u.nombreUsuario);

    printf("CONTRASENIA:.............................: %s\n",u.pass);

    printf("PAIS DE RESIDENCIA:......................: %s\n",u.pais);

    printf("CORREO ELECTRONICO:......................: %s\n",u.correoElectronico);

    printf("FECHA DE NACIMIENTO:.....................: %i\n",u.anioNacimiento);

    printf("GENERO:..................................: %c\n",u.genero);

    printf("TIPO DE USUARIO:.........................: %d\n",u.tipoUsuario);

    printf("APROBADO:................................: %d\n",u.aprobado);

    printf("ELIMINADO:...............................: %d\n",u.eliminado);

    printf("ID:......................................: %d\n",u.idUsuario);

    printf("******************************************************\n\n");
}


//muestra por pantalla todos los datos de una cancion
void mostrarDatosCancion(stCancion cancion)
{
    printf("**********************************************************************\n");
    printf("*<>*<>*<>*<>*<>*<>*<>*<>*<>*< CANCION >*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*\n");
    printf("**********************************************************************\n");


    printf("TITULO:..........................................................: %s\n",cancion.titulo);

    printf("ARTISTA:.........................................................: %s\n",cancion.artista);

    printf("ALBUM:...........................................................: %s\n",cancion.album);

    printf("GENERO:..........................................................: %s\n",cancion.genero);

    printf("DURACION:........................................................: %d\n",cancion.duracion);

    printf("ANIO:............................................................: %d\n",cancion.anio);

    printf("COMENTARIO:......................................................: %s\n", cancion.comentario);

    printf("ELIMINADO:.......................................................: %d\n",cancion.eliminado);

    printf("ID:..............................................................: %d\n",cancion.idCancion);

    printf("**********************************************************************\n\n");
}


//muestra los datos de una cancion que no se encuentra eliminada
void mostrarDatosCancionSimple(stCancion cancion)
{
    if(cancion.eliminado==0) //no eliminada
    {
        printf("\n*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*\n");
        printf("TITULO................: %s\n", cancion.titulo);
        printf("ARTISTA...............: %s\n", cancion.artista);
        printf("ALBUM.................: %s\n", cancion.album);
        printf("GENERO................: %s\n", cancion.genero);
        printf("ANIO...................: %d\n", cancion.anio);
        printf("DURACION..............: %d\n", cancion.duracion);
        printf("COMENTARIO............: %s\n", cancion.comentario);
        printf("ID....................: %d", cancion.idCancion);
        printf("\n*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*\n\n");
    }
}

//muestra la lista del arreglo
void mostrarListaADL (nodoListaCancion*lista)
{
    int i=0;
    nodoListaCancion*seg=lista;
    printf("************************************************\n");
    printf("*<>*<>*<>*<>*< LISTA DE CANCIONES >*<>*<>*<>*<>*\n");
    printf("************************************************\n\n");
    while(seg!=NULL)
    {
        printf("\n\n*<>*<>*<>*<>*< CANCION N-%d >*<>*<>*<>*<>*\n", i);
        printf("TITULO: ...............%s\n",seg->c.titulo);
        printf("ARTISTA:.............. %s\n",seg->c.artista);
        printf("ALBUM:................ %s\n",seg->c.album);
        printf("ID:................... %d\n\n",seg->c.idCancion);
        printf("*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*\n");
        i++;
        seg=seg->sig;
    }
}

//muestra los usuarios cargados en el arreglo de usuarios
void mostrarADL (stCelda**ADL, int validos)
{
    int i=0;
    printf("\n\n********************************************************************\n");
    printf("-------------------------- ARREGLO DE USUARIOS -------------------------\n");
    printf("************************************************************************\n");
    while(i<validos)
    {
        printf("%s\n", (*ADL)[i].usr.nombreUsuario);
        i++;
    }

}

//muestra el mensaje recibido por el administrador
void mostrarMensajeRecibido(char mensaje[], char nombre[])
{
    printf("USUARIO...............: %s\n\n", nombre);
    printf("MENSAJE...............: %s\n", mensaje);

}
