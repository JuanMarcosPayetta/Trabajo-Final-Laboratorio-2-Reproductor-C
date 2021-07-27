#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "gestionUsuario.h"
#include "gestionMenus.h"
#include "sistema.h"

// Menu de inicio, permite el registo e inicio de sesion mediante la invocacion de una funcion segun la opcion ingresada//
void menuInicio (stCelda**ADL, int*validos, nodoArbolCancion*arbol)
{
    int opcion;
    do
    {
        system("cls");
        printf("********************************************\n");
        printf("*<>*<>*<>*<>*< MENU DE INICIO >*<>*<>*<>*<>*\n");
        printf("********************************************\n");
        printf("Bienvenido Invitado\n");
        printf("ELIJA LA OPCION DESEADA:\n\n");
        printf("INGRESE [ 1 ] PARA RESGISTRARSE\n\n");
        printf("INGRESE [ 2 ] PARA INICIAR SESION\n\n");
        printf("INGRESE [ 3 ] PARA ACERCA DE...\n\n");
        printf("INGRESE [ 4 ] PARA SALIR\n");
        printf("********************************************\n");
        fflush(stdin);
        opcion=getch();

        switch(opcion) //se utiliza codigo ascii para las opciones
        {
        case 49:
            registrarse(ADL, validos, arbol); //permite registrarse
            break;

        case 50:
            iniciarSesion (ADL, validos, arbol); //permite iniciar sesion
            break;

        case 51:
            system("cls");
            printf("\n\n\n\n\n\n\t\t\tDesarrolado por Dolores Bruzzone - Juan Payetta - Pablo Payetta\n");
            printf("\n\t\t\tCopyright © FRUTNMDP 2020, todos los derechos reservados\n");
            getch();
            system("cls");
            menuInicio (ADL, validos,arbol);
            break;

        case 52:
            exit(0);
            break;

        default:
            printf("La opcion elegida no es valida\n");
            printf("Ingrese una opcion nuevamente:\n");
            printf("Presione una tecla para continuar\n");
            getch();
            break;

        }
    }
    while(opcion!=49 && opcion!=50 && opcion!=51);
}

//Menu con las opciones para registrarse como administrador o usuario.
void registrarse(stCelda**ADL, int*validos, nodoArbolCancion*arbol)
{
    int opcion;
    int i=0;
    do
    {
        system("cls");
        printf("***********************************************\n");
        printf("*<>*<>*<>*<>*< MENU DE REGISTRO >*<>*<>*<>*<>*\n");
        printf("***********************************************\n");
        printf("ELIJA LA OPCION DESEADA:\n\n");
        printf("INGRESE [ 1 ] RESGISTRARSE COMO ADMINISTRADOR\n\n");
        printf("INGRESE [ 2 ] RESGISTRARSE COMO USUARIO\n\n");
        printf("INGRESE [ 3 ] REGRESAR AL MENU DE INICIO\n");
        printf("***********************************************\n");
        fflush(stdin);
        opcion=getch();

        switch(opcion) //utilizamos codigo ascii para seleccionar las opciones
        {
        case 49:
            contraseniaAdministrador  (ADL, validos, arbol); //se le solicita que ingrese una contraseña de seguridad para poder ser administrador. Impide que cualquier persona pueda registrarse como administrador.
            break;

        case 50:
            registroUsuario (ADL, validos, arbol, i); //lo envia a la pantalla de registro de usuario.
            break;

        case 51:
            menuInicio (ADL, validos,arbol); //lo envia a la pantalla de inicio.
            break;

        default:
            printf("La opcion elegida no es valida\n ");
            printf("Ingrese una opcion nuevamente:\n");
            printf("Presione una tecla para continuar\n");
            getch();
            break;
        }
    }
    while(opcion!=49 && opcion!=50 && opcion!=51);
}



//permite modificar los datos del usuario
stUsuario subMenModificarRegistroUsuario(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    int opcion;
    do
    {
        printf("***********************************************\n");
        printf("*<>*<>*<>*< SUBMENU MODIFICAR DATOS >*<>*<>*<>*\n");
        printf("***********************************************\n");
        printf("Elija la opcion del campo que desea modificar:\n\n");
        printf("INGRESE [ 1 ]  NOMBRE DE USUARIO\n\n");
        printf("INGRESE [ 2 ]  CONTRASEÑA\n\n");
        printf("INGRESE [ 3 ]  PAIS\n\n");
        printf("INGRESE [ 4 ]  CORREO ELECTRONICO\n\n");
        printf("INGRESE [ 5 ]  AÑO DE NACIMIENTO\n\n");
        printf("INGRESE [ 6 ]  GENERO\n\n");
        printf("INGRESE [ 7 ]  REGRESAR A LA PANTALLA ANTERIOR\n");
        printf("*************************************************\n");
        fflush(stdin);
        opcion=getch();

        switch(opcion) //utilizamos codigo ascii para seleccionar las opciones
        {
        case 49:
            u=cargaNombreU(u);
            break;
        case 50:
            pedirPassDosVeces(u.pass,20);
            break;
        case 51:
            u=cargaPais(u);
            break;
        case 52:
            u=cargaCorreoE(u);
            break;
        case 53:
            u=cargaAnioNac(u);
            break;
        case 54:
            u=cargaGenero(u);
            break;
        case 55:
            menuCliente(ADL, validos, arbol, u);
            break;
        default:
            printf("*********************************\n");
            printf("La opcion elegida no es valida\n ");
            printf("Ingrese una opcion nuevamente:\n");
            printf("Presione una tecla para continuar\n");
            printf("**********************************\n");
            getch();
            break;
        }

    }
    while(opcion!=49 && opcion!=50 && opcion!=51 && opcion!=52 && opcion!=53 && opcion!=54 && opcion!=55);

    return u;
}

//sub menu para que el usuario cliente seleccione alguna opcion relativa a canciones (playlist)
void menuCliente(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    int opcion;
    do
    {
        system("cls");
        printf("***********************************************\n");
        printf("*<>*<>*<>*<>*< MENU DE CLIENTES >*<>*<>*<>*<>*\n");
        printf("***********************************************\n");
        printf("Bienvenido Usuario: %s\n\n", u.nombreUsuario);
        printf("ELIJA LA OPCION DESEADA:\n\n");
        printf("INGRESE [ 1 ] VER SU PERFIL\n\n");
        printf("INGRESE [ 2 ] VER SU PLAYLIST\n\n");
        printf("INGRESE [ 3 ] AGREGAR CANCIONES A SU PLAYLIST\n\n");
        printf("INGRESE [ 4 ] VER CANCIONES RECOMENDADAS\n\n");
        printf("INGRESE [ 5 ] MODIFICAR PERFIL\n\n");
        printf("INGRESE [ 6 ] ELIMINAR CANCION DE SU PLAYLIST\n\n");
        printf("INGRESE [ 7 ] REPRODUCCIONES GLOBALES\n\n");
        printf("INGRESE [ 8 ] ENVIAR MENSAJE AL ADMINISTRADOR\n\n");
        printf("INGRESE [ 9 ] CERRAR SESION\n");
        printf("***********************************************\n");
        fflush(stdin);
        opcion=getch();

        switch(opcion) //utilizamos codigo ascii para seleccionar las opciones
        {
        case 49:
            verPerfil(u, ADL, validos, arbol); //muestra por pantalla los datos actuales del cliente
            break;

        case 50:
            verPlaylist (ADL, validos, arbol, u); //muestra la playlist del usuario cliente

            break;

        case 51:
            escucharCancion(ADL, u.idUsuario, validos, arbol, u); //permite agregar canciones a la playlist
            break;

        case 52:
            recomendarCancion (ADL, validos, arbol, u); //muestra las canciones recomendadas al usuario cliente

            break;

        case 53:
            u=modificarPerfil(u, ADL, validos, arbol); //permite modificar datos del perfil
            break;

        case 54:
            eliminarCancionPlaylist (ADL, validos, arbol, u); //elimina canciones de la playlist
            break;

        case 55:
            reproduccionCancion (ADL, validos, arbol, u); //muestra la cantidad de reproducciones totales de las canciones del sistema
            break;

        case 56:
            enviarMensaje (ADL, validos, arbol, u); //permite enviar un mensaje al administrador
            break;

        case 57:
            borrarMemoria(ADL, validos, u);
            menuInicio (ADL, validos, arbol); //lo envia a la pantalla de inicio.
            break;

        default:
            printf("La opcion elegida no es valida\n ");
            printf("Ingrese una opcion nuevamente:\n");
            printf("Presione una tecla para continuar\n");
            getch();
            break;
        }

    }
    while(opcion!=49 && opcion!=50 && opcion!=51 && opcion!=52 && opcion!=53 && opcion!=54 && opcion!=55 && opcion!=56 && opcion!=57);

}


//sub menu para que el administrador seleccione que tarea desea realizar respecto de usuario o canciones
void menuPpalAdmin(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    int opcion;
    do
    {
        system("cls");
        printf("****************************************************\n");
        printf("*<>*<>*<>*<>*< MENU DEL ADMINISTRADOR >*<>*<>*<>*<>*\n");
        printf("****************************************************\n");
        printf("Bienvenido Administrador/a: %s\n\n", u.nombreUsuario);
        printf("ELIJA LA OPCION DESEADA:\n\n");
        printf("INGRESE [ 1 ] MENU ADMINISTRACION DE USUARIOS\n\n");
        printf("INGRESE [ 2 ] MENU ADMINISTRACION DE CANCIONES\n\n");
        printf("INGRESE [ 3 ] CERRAR SESION\n");
        printf("*****************************************************\n");
        fflush(stdin);
        opcion=getch();

        switch(opcion) //utilizamos codigo ascii para seleccionar las opciones
        {
        case 49:
            subMenuAdmin(ADL, validos, arbol, u); //sub menu administracion de usuarios

            break;

        case 50:
            subMenuAdminCanciones (ADL, validos, arbol, u); //sub menu administracion de canciones

            break;

        case 51:
            borrarMemoriaAdm (ADL, validos); //limpia la memoria cuandos se cierra sesion
            menuInicio (ADL, validos,arbol); //lo envia a la pantalla de inicio.
            break;

        default:
            printf("*********************************\n");
            printf("La opcion elegida no es valida\n ");
            printf("Ingrese una opcion nuevamente:\n");
            printf("Presione una tecla para continuar\n");
            printf("**********************************\n");
            getch();
            break;
        }
    }
    while(opcion!=49 && opcion!=50 && opcion!=51);
}

//sub menu para que el administrador seleccione que tarea quiere realizar respecto de un usuario cliente
void subMenuAdmin(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    int opcion;
    do
    {
        system("cls");
        printf("****************************************************************\n");
        printf("*<>*<>*<>*<>*< MENU DEL ADMINISTRADOR DE USUARIOS >*<>*<>*<>*<>*\n");
        printf("****************************************************************\n");
        printf("ELIJA LA OPCION DESEADA:\n\n");
        printf("INGRESE [ 1 ] ALTA DE USUARIOS\n\n");
        printf("INGRESE [ 2 ] BAJA DE USUARIOS\n\n");
        printf("INGRESE [ 3 ] MODIFICACION DE USUARIOS\n\n");
        printf("INGRESE [ 4 ] CONSULTA DE USUARIOS\n\n");
        printf("INGRESE [ 5 ] LISTADO DE USUARIOS\n\n");
        printf("INGRESE [ 6 ] LEER CORREO\n\n");
        printf("INGRESE [ 7 ] VOLVER A MENU PRINCIPAL DE ADMIN.\n");
        printf("****************************************************************\n");
        fflush(stdin);
        opcion=getch();

        switch(opcion) //utilizamos codigo ascii para seleccionar las opciones
        {
        case 49:
            system("cls");
            altaDeUsuarios(ADL, validos, arbol, u); //aprueba a un usuario o lo recupera si fue eliminado
            break;

        case 50:
            darDeBajaUsuario(ADL, validos, arbol, u); //da de baja a un usuario
            break;

        case 51:
            modifUssAdmin(ADL, validos, arbol, u); //modifica algunos datos de un usuario cliente
            break;

        case 52:
            consultaExistUsuario(ADL, validos, arbol, u); //consulta de usuarios clientes
            break;

        case 53:
            listadoUsuarios(ADL, validos, arbol, u); //muestra el listado de usuarios clientes
            break;

        case 54:
            recibirMensaje (ADL, validos, arbol, u); //permite leer mensajes enviados por un usuario cliente
            break;

         case 55:
            menuPpalAdmin(ADL, validos,arbol,u); //lo envia a la pantalla de inicio.
             break;

        default:
            printf("*********************************\n");
            printf("La opcion elegida no es valida\n ");
            printf("Ingrese una opcion nuevamente:\n");
            printf("Presione una tecla para continuar\n");
            printf("*********************************\n");
            getch();
            break;
        }
    }
    while(opcion!=49 && opcion!=50 && opcion!=51 && opcion!=52 && opcion!=53 && opcion!=54 && opcion!=55);
}

//sub menu para que el administrador seleccione que dato se quiere modificar de un usuario cliente
void subMenModifRegAdmin(stUsuario u, stUsuario c, stCelda**ADL, int*validos, nodoArbolCancion*arbol)
{
    int opcion;
    int flag=0;
    do
    {
        printf("\n**********************************************************\n");
        printf("Elija la opcion del campo que desea modificar:\n");
        printf("************************************************************\n");
        printf("INGRESE [ 1 ]  ANIO DE NACIMIENTO\n\n");
        printf("INGRESE [ 2 ]  GENERO\n\n");
        printf("INGRESE [ 3 ]  PAIS\n\n");
        printf("INGRESE [ 4 ]  CORREO ELECTRONICO\n\n");
        printf("INGRESE [ 5 ]  MODIFICAR OTRO USUARIO CLIENTE\n\n");
        printf("INGRESE [ 6 ]  VOLVER AL MENU DE ADMINISTRACION DE USUARIOS\n");
        printf("************************************************************\n");
        printf("\n\n");
        fflush(stdin);
        opcion=getch();

        switch(opcion) //utilizamos codigo ascii para seleccionar las opciones
        {
        case 49: // flag=1
            modificarClienteArchivo(c, 1, ADL, validos, arbol, u);
            break;
        case 50: // flag=2
            modificarClienteArchivo(c, 2, ADL, validos, arbol, u);
            break;
        case 51: // flag=3
            modificarClienteArchivo(c, 3, ADL, validos, arbol, u);
            break;
        case 52: // flag=4
            modificarClienteArchivo(c, 4, ADL, validos, arbol, u);
            break;
        case 53:
            modifUssAdmin(ADL,validos,arbol,u);
            break;
        case 54:
            subMenuAdmin(ADL,validos,arbol,u);
            break;
        default:
            printf("*********************************\n");
            printf("La opcion elegida no es valida\n ");
            printf("Ingrese una opcion nuevamente:\n");
            printf("Presione una tecla para continuar\n");
            printf("*********************************\n");
            getch();
            break;
        }
    }
    while(opcion!=49 && opcion!=50 && opcion!=51 && opcion!=52 && opcion!=53 && opcion!=54);
}

//sub menu para que el administrador seleccione que dato se quiere modificar de una cancion
stCancion menuModificacionCanciones (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u, stCancion c)
{
    stCancion cancion;
    int opcion;
    do
    {
        printf("*************************************************\n");
        printf("*<>*<>*<>*< MENU MODIFICAR CANCIONES  >*<>*<>*<>*\n");
        printf("*************************************************\n");
        printf("Elija la opcion del campo que desea modificar:\n\n");
        printf("INGRESE [ 1 ]  TITULO\n\n");
        printf("INGRESE [ 2 ]  ARTISTA\n\n");
        printf("INGRESE [ 3 ]  ALBUM\n\n");
        printf("INGRESE [ 4 ]  ANIO\n\n");
        printf("INGRESE [ 5 ]  GENERO\n\n");
        printf("INGRESE [ 6 ]  COMENTARIO\n\n");
        printf("INGRESE [ 7 ]  REGRESAR AL MENU ADMIN CANCIONES\n");
        printf("*************************************************\n");
        fflush(stdin);
        opcion=getch();

        switch(opcion) //utilizamos codigo ascii para seleccionar las opciones
        {
        case 49:
            cancion=modificarTitulo (c);
            break;
        case 50:
            cancion=modificarArtista (c);

            break;
        case 51:
            cancion=modificarAlbum (c);

            break;
        case 52:
            cancion=modificarAnio (c);
            break;
        case 53:
            cancion=modificarGenero (c);
            break;
        case 54:
            cancion=modificarComentario (c);

            break;
        case 55:
            subMenuAdminCanciones(ADL, validos, arbol,u);
            break;
        default:
            printf("*********************************\n");
            printf("La opcion elegida no es valida\n ");
            printf("Ingrese una opcion nuevamente:\n");
            printf("Presione una tecla para continuar\n");
            printf("**********************************\n");
            getch();
            break;
        }

    }
    while(opcion!=49 && opcion!=50 && opcion!=51 && opcion!=52 && opcion!=53 && opcion!=54 && opcion!=55);

    return cancion;
}


//sub menu del administador, relativo a las canciones.
void subMenuAdminCanciones (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    int opcion;
    do
    {
        system("cls");
        printf("**************************************************************\n");
        printf("*<>*<>*<>*<>*< MENU ADMINISTRACION DE CANCIONES >*<>*<>*<>*<>*\n");
        printf("**************************************************************\n");
        printf("ELIJA LA OPCION DESEADA:\n\n");
        printf("INGRESE [ 1 ] ALTA DE CANCION\n\n");
        printf("INGRESE [ 2 ] BAJA DE CANCION \n\n");
        printf("INGRESE [ 3 ] MODIFICACION DE CANCION\n\n");
        printf("INGRESE [ 4 ] CONSULTA DE CANCION\n\n");
        printf("INGRESE [ 5 ] LISTADO DE CANCION\n\n");
        printf("INGRESE [ 6 ] RESTAURAR CANCION DADA DE BAJA\n\n");
        printf("INGRESE [ 7 ] ELIMINAR CANCION DE MANERA PERMANENTE\n\n");
        printf("INGRESE [ 8 ] VOLVER A MENU PRINCIPAL DE ADMIN\n");
        printf("***************************************************************\n");
        fflush(stdin);
        opcion=getch();

        switch(opcion) //utilizamos codigo ascii para seleccionar las opciones
        {
        case 49:
            system("cls");
            cargarCancionArchivo(ADL, validos, &arbol, u); //permite agregar una cancion al archivo de canciones y

            break;

        case 50:
            system("cls");
            darDeBajaCancion(ADL, validos, arbol, u); //permite eliminar logicamente una cancion


            break;

        case 51:
            modificacionDeCanciones (ADL, validos, arbol, u); //permite modificar una cancion

            break;

        case 52:
            consultaCanciones (ADL, validos, arbol, u); //consulta los datos de una cancion

            break;

        case 53:
            listadoCanciones (ADL, validos, arbol, u); //muestra canciones por titulo, genero, o todas las canciones activas
            break;

        case 54:
            restaurarCancion (ADL, validos, arbol, u); //restaura una cancion dada de baja
            break;

        case 55:
            eliminarCancionAdminFisicamente (ADL, validos, arbol, u); //elimina una cancion fisicamente
            break;

        case 56:
             menuPpalAdmin(ADL, validos,arbol,u); //lo envia a la pantalla de inicio.
            break;

        default:
            printf("*********************************\n");
            printf("La opcion elegida no es valida\n ");
            printf("Ingrese una opcion nuevamente:\n");
            printf("Presione una tecla para continuar\n");
            printf("*********************************\n");
            getch();
            break;
        }
    }
    while(opcion!=49 && opcion!=50 && opcion!=51 && opcion!=52 && opcion!=53 && opcion!=54 && opcion!=55 && opcion!=56);
}

//menu que permite al administrador seleccionar si desea recuperar a un usuario eliminado u aprobar usuarios
void altaDeUsuarios(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    char ctr;

    printf("*********************************************************\n");
    printf("*<>*<>*<>*<>*<>*< MENU ALTA DE USUARIOS >*<>*<>*<>*<>*<>*\n");
    printf("**********************************************************\n\n");
    printf("ELIJA LA OPCION DESEADA:\n\n");
    printf("INGRESE [ 1 ] RECUPERAR USUARIO ELIMINADO\n\n");
    printf("INGRESE [ 2 ] APROBAR USUARIO\n\n");
    printf("INGRESE [ 3 ] VOLVER AL MENU DE ADMINISTRACION DE USUARIOS\n");
    printf("***********************************************************\n");
    ctr=getch();

    switch(ctr) //utilizamos codigo ascii para seleccionar las opciones
    {
    case 49:
        recuperarUsuarioCl(ADL, validos, arbol, u); //recuperar un usuario cliente que fue eliminado
        break;

    case 50:
        system("cls");
        aprobarUsuarios (ADL, validos, arbol, u); //aprueba a un usuario cliente

        break;

    case 51:
        subMenuAdmin(ADL, validos, arbol, u); //retorna al menu de adm de usuarios
        break;

    default:
        printf("La opcion elegida no es valida\n ");
        printf("Ingrese una opcion nuevamente:\n");
        printf("Presione una tecla para continuar\n");
        getch();
        break;

    }
    while(ctr!=49 && ctr!=50 && ctr!=51);

}


//menu de mostrar listado de canciones por genero o por titulo
void listadoCanciones (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    char opcion;

    printf("*******************************************************\n");
    printf("*<>*<>*<>*<>*< MENU LISTADO DE CANCIONES >*<>*<>*<>*<>*\n");
    printf("*******************************************************\n");
    printf("ELIJA LA OPCION DESEADA\n\n");
    printf("INGRESE [ 1 ] CANCIONES POR TITULO\n\n");
    printf("INGRESE [ 2 ] CANCIONES POR GENERO \n\n");
    printf("INGRESE [ 3 ] TOTAL CANCIONES ACTIVAS\n\n");
    printf("INGRESE [ 4 ] VOLVER A MENU ADMIN CANCIONES\n");
    printf("********************************************************\n");
    fflush(stdin);
    opcion=getch();

    switch(opcion)
    {
    case 49:
        system("cls");
        cancionesTitulo (ADL, validos, arbol, u); //muestra una cancion ingresando su titulo

        break;

    case 50:
        system("cls");
        cancionesGenero (ADL, validos, arbol, u); //muestra las canciones de un genero determinado

        break;

    case 51:
        listaTotalCancionesActivas(ADL, validos, arbol, u); //muestra las canciones activas
        break;

    case 52:
        subMenuAdminCanciones (ADL, validos, arbol, u); //vuelve al menu de administracion de canciones
        break;

    default:
        printf("********************************\n");
        printf("La opcion elegida no es valida\n ");
        printf("Ingrese una opcion nuevamente:\n");
        printf("Presione una tecla para continuar\n");
        printf("*********************************\n");
        getch();
        break;

    }
    while(opcion!=49 && opcion!=50 && opcion!=51 && opcion!=52);

}
