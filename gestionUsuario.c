#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "gestionUsuario.h"
#include "gestionMenus.h"
#include "gestionArchivos.h"
#include "gestionPlaylist.h"





//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
///FUNCIONES DE USUARIO CLIENTE

//muestra los datos del usuario
void verPerfil(stUsuario u,stCelda**ADL, int*validos, nodoArbolCancion*arbol)
{
    system("cls");
    char opcion;
    printf("*******************************************************************************\n");
    printf("Si desea ver sus datos de usuario presione cualquier tecla, caso contrario ESC:\n");
    printf("*******************************************************************************\n");
    opcion=getch();
    if(opcion!=27)
    {
        system("cls");
        mostrarDatosUsuario(u);
        printf("Para volver al menu presione cualquier tecla:\n");
        getch();
        menuCliente(ADL, validos, arbol, u);
    }
    else
    {
        menuCliente(ADL, validos, arbol, u);
    }
}


stUsuario modificarPerfil(stUsuario u,stCelda**ADL, int*validos, nodoArbolCancion*arbol)
{
    system("cls");
    char opcion;
    mostrarDatosUsuario(u);
    printf("************************************************************************************************\n");
    printf("Si desea modificar sus datos personales presione cualquier tecla, caso contrario seleccione ESC:\n");
    printf("************************************************************************************************\n");
    opcion=getch();

    if(opcion!=27)
    {
        system("cls");
        mostrarDatosUsuario(u);
        u=subMenModificarRegistroUsuario(ADL, validos, arbol, u);
        system("cls");
        modificacionUsuario(u);
        mostrarDatosUsuario(u);
        printf("Para regresar al menu seleccione cualquier tecla:\n");
        getch();
    }

    menuCliente(ADL, validos, arbol, u);
}

//pregunta al usuario si desea ver su playlist
void verPlaylist (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    char opcion;
    system("cls");
    printf("**********************************************************************\n");
    printf("Si desea ver su playlist presione cualquier tecla, caso contrario ESC:\n");
    printf("**********************************************************************\n");
    opcion=getch();
    if(opcion!=27)
    {
        int pos;

        pos=posicionUsuarioAdl(ADL, validos, u.idUsuario); //busco la posicion del usuario en el arreglo

        if(pos!=-1)
        {

            system("cls");
            mostrarPlaylist((*ADL)[pos].listaCanciones); //le paso la lista del usuario para mostrarla
        }

        printf("\nSi desea volver al menu presione cualquier tecla:\n");
        getch();
        menuCliente(ADL, validos, arbol, u);
    }
    else
    {
        menuCliente(ADL, validos, arbol, u);
    }
}


//consulta si el usuario desea eliminar una cancion de su playlist de canciones
void eliminarCancionPlaylist (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    char opcion;
    printf("******************************************************************************************\n");
    printf("Si desea borrar una cancion de su playlist seleccione cualquier tecla, caso contrario ESC:\n");
    printf("******************************************************************************************\n");
    opcion=getch();
    int id;
    if(opcion!=27)
    {
        system("cls");
        int pos=posicionUsuarioAdl(ADL, validos, u.idUsuario); //busco la posicion del usuario en el arreglo

        if((*ADL)[pos].listaCanciones!=NULL) //si la playlist tiene almenos 1 cancion
        {
            if(pos!=-1)
            {
                mostrarPlaylist((*ADL)[pos].listaCanciones); //le paso la lista del usuario para mostrarla y elija ID
            }

            printf("\n\nIngrese el ID de la cancion que desea eliminar:\n");
            fflush(stdin);
            scanf("%d", &id);

            int flag=encontrarElementoLista ((*ADL)[pos].listaCanciones, id);

            if(flag==100) //encontro una cancion con esa id en la lista de canciones
            {
                system("cls");
                (*ADL)[pos].listaCanciones=borrarCancion((*ADL)[pos].listaCanciones, id); //borro la cancion de la lista
                eliminarCancionArchivoPlaylist (id, u.idUsuario); //elimina la cancion del archivo playlist fisicamente

                mostrarPlaylist((*ADL)[pos].listaCanciones);

                printf("\n\nSu cancion a sido eliminada con exito\n");
                printf("Si desea intentar repetir la accion presione cualquier tecla, caso contrario ESC:\n");

                opcion=getch();
                if(opcion!=27)
                {
                    eliminarCancionPlaylist (ADL, validos, arbol, u);
                }
                else
                {
                    menuCliente(ADL, validos, arbol, u);
                }

            }
            else //el id ingresado no es valido
            {
                system("cls");
                printf("El ID ingresado no corresponde a ninguna cancion en su playlist\n");
                printf("Si desea volver a intentar presione cualquier tecla, caso contrario seleccione ESC:\n");
                opcion=getch();

                if(opcion!=27)
                {
                    eliminarCancionPlaylist (ADL, validos, arbol, u);
                }
                else
                {
                    menuCliente(ADL, validos, arbol, u);
                }
            }
        }
        else
        {
            system("cls");
            printf("*****************************************************************************\n");
            printf("Su playlist se encuentra vacia, presione cualquier tecla para volver al menu:\n");
            printf("*****************************************************************************\n");
            getch();
            menuCliente(ADL, validos, arbol, u);
        }

    }
    else
    {
        menuCliente(ADL, validos, arbol, u);
    }

}


//algoritmo que cuenta la cantidad de canciones con determinado genero, compara los valores y muestra una cancion del genero con mayor cantidad
void recomendarCancion (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{

    system("cls");
    int pos;
    char pop[20]="pop"; //nombre de cada genero
    char rock[20]="rock";
    char balada[20]="balada";
    char electro[20]="electro";
    char clasica[20]="clasica";
    char tango[20]="tango";
    int contPop=0; //inicializo un contador por genero
    int contRock=0;
    int contBalada=0;
    int contElectro=0;
    int contClasica=0;
    int contTango=0;
    int flag=0;
    char opcion;

    printf("Si desea ver las canciones recomendadas presiones cualquier tecla, caso contrario ESC:\n");
    opcion=getch();
    if(opcion!=27)
    {
        system("cls");
        pos=posicionUsuarioAdl(ADL, validos, u.idUsuario); //busco la posicion del usuario en el arreglo
        if(pos!=1)
        {
            nodoListaCancion*seg=(*ADL)[pos].listaCanciones;
            if(seg!=NULL)
            {
                while(seg!=NULL) //cuento cuantas canciones por cada genero tiene la playlist del usuario (su lista)
                {
                    if(strcmpi(seg->c.genero, pop)==0)
                    {
                        contPop++;
                        seg=seg->sig;
                        flag=1;
                    }
                    else if(strcmpi(seg->c.genero, rock)==0)
                    {
                        contRock++;
                        seg=seg->sig;
                        flag=1;
                    }
                    else if(strcmpi(seg->c.genero, balada)==0)
                    {
                        contBalada++;
                        seg=seg->sig;
                        flag=1;
                    }
                    else if(strcmpi(seg->c.genero, electro)==0)
                    {
                        contElectro++;
                        seg=seg->sig;
                        flag=1;
                    }
                    else if(strcmpi(seg->c.genero, clasica)==0)
                    {
                        contClasica++;
                        seg=seg->sig;
                        flag=1;
                    }
                    else if(strcmpi(seg->c.genero, tango)==0)
                    {
                        contTango++;
                        seg=seg->sig;
                        flag=1;
                    }
                    else
                    {
                        seg=seg->sig;
                    }
                }
            }
            else if(flag==0) //si no tiene ningun genero de los establecidos en la lista
            {
                printf("********************************************************************************************\n");
                printf("Por el momento no hay canciones para recomendar, intente luego de cargar su playlis porfavor\n");
                printf("Presione cualquier tecla para volver al menu:\n");
                printf("********************************************************************************************\n");
                getch();
                menuCliente(ADL, validos, arbol, u);
            }
        }


        printf("****************************************************\n");
        printf("*<>*<>*<>*<>*< CANCIONES RECOMENDADAS >*<>*<>*<>*<>*\n");
        printf("****************************************************\n");

        int posicion=mayorGenero (contPop, contRock, contBalada, contElectro, contTango, contClasica); //analiza cual fue el genero con mayor cantidad de canciones
        verGeneroMayor (ADL, validos, arbol, u, posicion); //muestra canciones del genero mas elegido en el arbol de canciones
    }
    else
    {
        menuCliente(ADL, validos, arbol, u);
    }
}


//muestra canciones del genero mas elegido segun la posicion retornada por la funcion mayorGenero
void verGeneroMayor (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u, int posicion)
{
    char pop[20]="pop";
    char rock[20]="rock";
    char balada[20]="balada";
    char electro[20]="electro";
    char clasica[20]="clasica";
    char tango[20]="tango";

    if(posicion==0)
    {
        generoRecomendado (arbol, pop);
    }
    else if(posicion==1)
    {
        generoRecomendado (arbol, rock);
    }
    else if(posicion==2)
    {
        generoRecomendado (arbol, balada);
    }
    else if(posicion==3)
    {
        generoRecomendado (arbol, electro);
    }
    else if(posicion==4)
    {
        generoRecomendado (arbol, clasica);
    }
    else if(posicion==5)
    {
        generoRecomendado (arbol, tango);
    }
    else
    {
        printf("Por el momento no hay canciones para recomendar, intente mas tarde:\n");
    }


    printf("\nSi desea volver al menu presione cualquier tecla:\n");
    getch();
    menuCliente(ADL, validos, arbol, u);
}

//busca el genero con mayor cantidad de canciones y devuelve la posicion del arreglo
int mayorGenero (int pop, int rock, int balada, int electro, int tango, int clasica)
{
    int posicion=0;
    int arreglo[30];
    int valid=0;
    arreglo[0]=pop; //cargo en cada posicion del arreglo un genero musical (que ya tiene la cantidad de canciones de ese genero en la play del usuario)
    arreglo[1]=rock;
    arreglo[2]=balada;
    arreglo[3]=electro;
    arreglo[4]=clasica;
    arreglo[5]=tango;
    int mayor=arreglo[0]; //tomo un genero de referencia
    valid=6;

    int i=1;
    while(i<valid)
    {
        if(mayor<arreglo[i])
        {
            mayor=arreglo[i];
            posicion=i;
            i++;
        }
        else
        {
            i++;
        }
    }

    return posicion; //genero con mas cantidad en la playlist del usuario
}

//muestra las canciones del arbol de un genero buscado
void generoRecomendado (nodoArbolCancion*arbol, char gen[])
{
    if(arbol!=NULL)
    {
        generoRecomendado(arbol->izq, gen); //recorro el arbol hacia la izquierda

        if(strcmpi(arbol->c.genero, gen)==0) //si el genero es el buscado lo muestro
        {
            mostrarCancionRecomendada(arbol->c);
        }

        generoRecomendado(arbol->der, gen); //recorro el arbol hacia la derecha
    }
}


//permite seleccionar una cancion del arbol de canciones y agregarla a la playlist
void escucharCancion(stCelda**ADL, int idUsuario, int validos, nodoArbolCancion*arbol, stUsuario u)
{
    int id=-5;
    int validacion=-7;
    char opcion;


    do
    {
        system("cls");
        printf("******************************************************************\n");
        printf("*<>*<>*<>*<>*< MENU AGREGAR CANCIONES A LA PALYLIST >*<>*<>*<>*<>*\n");
        printf("******************************************************************\n");
        printf("LISTA DE CANCIONES DISPONIBLES:\n\n");

        inOrder(arbol); //muestra toda la lista de canciones disponibles en el arbol de canciones


        printf("\n*****************************************************************\n");
        printf("Ingrese el ID de la cancion que desea escuchar y agregar a su playlist\n:");
        fflush(stdin);
        scanf("%d", &id);

        validacion=validarIdCancion(id); //verifica que el ID sea un ID valido
        if(validacion!=1) //si el ID no es valido
        {
            printf("\nERROR: El ID seleccionado no es valido\n");
            printf("Si desea volver a intentar presione cualquier tecla, caso contrario seleccione ESC:\n");
            opcion=getch();

            if(opcion!=27)
            {
                escucharCancion (ADL, idUsuario, validos, arbol, u); //si ingreso un id errone y desea continuar, llamada recursiva a la misma funcion
            }
            else
            {
                menuCliente(ADL, validos, arbol, u); //si no quiere ingresar canciones regresa al menu de cliente
            }
        }
        else //si el ID seleccionado es valido lo agrego a la lista
        {
            cancionToADL(ADL, id, idUsuario, validos, arbol, u); //cargo la cancion seleccionada mediante su id, al ADL
            guardarCancionEnArchPlayl(id, idUsuario); //guarda la cancion seleccionada en el archivo playslit
            system("cls");
            mostrarArrayListas(ADL, validos, idUsuario);
            printf("\n\n******************************************************************************************\n");
            printf("La cancion fue agregada con exito a su playlist\n");
            printf("\nSi deses agregar mas canciones a su playlist seleccione cualquier tecla, caso contrario ESC:\n");
            printf("**********************************************************************************************\n");

            opcion=getch();
        }

    }
    while(opcion!=27);
    menuCliente(ADL, validos, arbol, u); //si no desea agregar mas canciones lo regresamos al menu de cliente

}

//muestra la cantida de repreoducciones que tuvo una cancion en todo el sistema (cuantas usuarios agregaron x cancion a su playlist)
void reproduccionCancion (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    char opcion;
    int i=0;
    int j=0;
    int p=0;
    int aux=0;
    int cont=0;
    stCancion cancion;
    int validosCanciones=0;
    stPlaylist*arregloIdCanciones;

    printf("********************************************************************************************************\n");
    printf("Si desea ver el numero de reproducciones de cada cancion seleccione cualquier tecla, caso contrario ESC:\n");
    printf("********************************************************************************************************\n");
    opcion=getch();

    if(opcion!=27)
    {

        validosCanciones=cargarADLTop(&arregloIdCanciones); //carga un arreglo justo con la cantidad de canciones de playlist.dat
        int*arreglo=(int*)malloc(validosCanciones*sizeof(int)); //creo un arreglo tipo int con la cantidad de canciones almacenadas en el otro arreglo

        for(i=0; i<validosCanciones; i++)
        {
            arreglo[i]=-1; //arreglo que contendra la cantidad de reproducciones por cancion. Cargo -1 por cada valido en el arreglo de canciones
        }
        for(i=0; i<validosCanciones; i++)
        {
            cont=1; //cuenta la cantidad de reproducciones por cancion

            for(j=i+1; j<validosCanciones; j++) //j comienza una posicion delante de i
            {
                if(arregloIdCanciones[i].idCancion==arregloIdCanciones[j].idCancion) //si el id de las canciones en cada posicion es igual sumo 1
                {
                    cont++; //cuento 1 reproduccion
                    arreglo[j]=0; // la posicion j donde estaba la cancion repetida tendra valor 0 porque se suma el contador
                }
            }
            if(arreglo[i]!=0) //si es una posicion valida
            {
                arreglo[i]=cont; //almaceno la cantidad de veces que se escucho esa cancion
            }
        }


        system("cls");

        printf("*****************************************************************\n");
        printf("*<>*<>*<>*<>*< CANCIONES MAS ESCUCHADA DEL MOMENTO >*<>*<>*<>*<>*\n");
        printf("*****************************************************************\n\n");

        int masReproducido= mayorReproducido (arreglo, validosCanciones); //busco la posicion del contador con mayor reproduccion

        for(i=0; i<validosCanciones; i++) //para el caso de que haya mas de una cancion con la misma cantidad de reproducciones
        {
            if(arreglo[i]==arreglo[masReproducido])
            {
                cancion=buscarCancionPorId (arregloIdCanciones[i].idCancion); //busco la cancion en esa posicion
                printf("****************************************\n");
                printf("CANCION..............:%s\n", cancion.titulo);
                printf("REPRODUCCIONES.......:%d\n\n", arreglo[i]);
            }
        }


        printf("*****************************************************\n");
        printf("*<>*<>*<>*<>*< REPRODUCCIONES GLOBALES >*<>*<>*<>*<>*\n");
        printf("*****************************************************\n\n");


        for(i=0; i<validosCanciones; i++)
        {
            if(arreglo[i]!=0) //hasta la posicion valida de datos
            {
                cancion=buscarCancionPorId (arregloIdCanciones[i].idCancion);

                printf("****************************************\n");
                printf("CANCION..............:%s\n", cancion.titulo);
                printf("REPRODUCCIONES.......:%d\n\n", arreglo[i]);

            }
        }
        printf("Seleccione cualquier tecla para regresar al menu:\n");
        getch();
        menuCliente(ADL, validos, arbol, u);
    }
    else
    {
        menuCliente(ADL, validos, arbol, u);
    }
}


//busca la mayor reproduccion para la cancion mas escuchada
int mayorReproducido (int reproducciones[], int validos)
{
    int i=0;
    int mayor=0;
    mayor=reproducciones[i];
    int pos=0;
    i++;

    while(i<validos)
    {
        if(mayor<reproducciones[i])
        {
            mayor=reproducciones[i];
            pos=i;
            i++;
        }
        else
        {
            i++;
        }
    }

    return pos;
}

//permite enviar un mensaje al administrador
void enviarMensaje (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    char opcion;
    char mensaje[300];

    printf("**************************************\n");
    printf("*<>*<>*<>*<>*< MENSAJES >*<>*<>*<>*<>*\n");
    printf("**************************************\n");

    printf("Si desea enviar un mensaje al Administrador seleccione cualquier tecla, caso contrario ESC:\n");
    opcion=getch();

    if(opcion!=27)
    {
        system("cls");
        printf("\nIngrese el mensaje que desea enviar:\n");
        gets(mensaje);
        mensajeAdministrador (mensaje, u.nombreUsuario);

        system("cls");
        printf("********************************************\n");
        printf("Su mensaje fue enviado exitosamente\n");
        printf("Presione cualquier tecla para volver al menu:\n");
        printf("********************************************\n");
        getch();
        menuCliente(ADL, validos, arbol, u);
    }
    else
    {
        menuCliente(ADL, validos, arbol, u);
    }
}



//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
///FUNCIONES ADMINISTRADOR

//aprueba a los usuarios que aun no han sido aprobados, para que puedan ingresar al menu de clientes
void aprobarUsuarios (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario x)
{

    stUsuario u;
    stUsuario b;
    int pos=0;
    int flag=0;
    char opcion;

    FILE*archi=fopen("usuarios.dat","r+b");
    if(archi!=NULL)
    {
        while(fread(&u, sizeof(stUsuario), 1, archi)>0) //si no llego al final del archivo
        {
            if(u.aprobado==0 && u.eliminado==0) //si no esta aprobado ni eliminado
            {
                pos=ftell(archi)/sizeof(stUsuario); //busco la posicion actual
                fseek(archi, (pos-1)*sizeof(stUsuario),SEEK_SET); //voy a la posicion deseada (restando -1 para que me ubique el cursor delante del dato a escribir)
                u.aprobado=1; //lo apruebo
                fwrite(&u,sizeof(stUsuario),1,archi); //modifico el valor
                flag=1;
            }
            fseek(archi,0,SEEK_CUR); //reposiciona el cursor en la posicion actual
        }
        fclose(archi);

        (*validos)=cargarADL(ADL); //crea el arreglo de los usuarios que se registraron, fueron aprobados, y quieren iniciar sesion nuevamente sin cerrar el programa

        if(flag==1)
        {
            FILE*archi=fopen("usuarios.dat", "rb");

            if(archi!=NULL)
            {
                printf("*********************************************************\n");
                printf("*<>*<>*<>*<>*< LISTA DE USUARIOS APROBADOS >*<>*<>*<>*<>*\n");
                printf("*********************************************************\n\n");

                while(fread(&b, sizeof(stUsuario), 1, archi)>0)
                {
                    if(b.aprobado==1 && b.tipoUsuario==0)
                    {
                        mostrarUsuariosAprobados(b,ADL, validos, arbol, x);
                    }
                }
                fclose(archi);
            }
            printf("\n\nPresione cualquier tecla para regresar al menu:\n");
            opcion=getch();
            subMenuAdmin(ADL, validos, arbol, x);
        }
        else
        {
            printf("****************************************************************\n");
            printf("--------------------------- ATENCION ---------------------------\n");
            printf("****************************************************************\n");

            printf("No se encuentran usuarios por aprobar\n");
            printf("\nPresione cualquier tecla para regresar al menu:\n");
            getch();
            subMenuAdmin(ADL, validos, arbol, x);
        }
    }
}


//recupera un usuario cliente en caso de haber sido eliminado
void recuperarUsuarioCl(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario x)
{
    system("cls");
    char nomUsuario[30];
    char opcion;
    stUsuario u;
    int flag=0;
    int pos=0;
    int k=99; //para los mostrar

    printf("*****************************************************************\n");
    printf("*<>*<>*<>*<>*< RECUPERAR USUARIO CLIENTE ELIMINADO >*<>*<>*<>*<>*\n");
    printf("*****************************************************************\n\n");

    printf("Si desea recuperar un usuario cliente eliminado seleccione cualquier tecla, caso contrario seleccione ESC:\n");
    opcion=getch();

    if(opcion!=27)
    {
        system("cls");
        int ver=existeUsuariosEliminados(); //comprueba que haya al menos 1 usuario cliente eliminado para recuperar
        if(ver==1)
        {
            todosLosUsuariosEliminados();//muestra todos los usuarios cliente eliminados del archivo usuarios.dat
            printf("\nIngrese el nombre del usuario cliente que desea recuperar:\n");
            gets(nomUsuario);

            FILE*archi=fopen("usuarios.dat","r+b");
            if(archi!=NULL)
            {
                while(!feof(archi)&& flag==0) //mientras el archivo no llegue al final y flag sea 0
                {
                    fread(&u,sizeof(stUsuario),1,archi);

                    if(!feof(archi))
                    {
                        if((strcmpi(u.nombreUsuario, nomUsuario)==0) && u.eliminado==1 && u.tipoUsuario==0) //recupero a un usuario eliminado
                        {
                            pos=ftell(archi)/sizeof(stUsuario); //busco la posicion actual
                            fseek(archi, (pos-1)*sizeof(stUsuario), SEEK_SET); //busco la posicion que necesito, -1 asi me posiciona el curso delante para escribir
                            u.eliminado=0; //recupero el usuario
                            fwrite(&u, sizeof(stUsuario), 1, archi); //modifico el registro
                            flag=1; //corta el while
                            k=1;
                        }
                        else if((strcmpi(u.nombreUsuario, nomUsuario)==0) && u.eliminado==0 && u.tipoUsuario==0) //si el usuario no estaba eliminado retorna flag 2
                        {
                            flag=2;
                            k=2;
                        }
                        else if((strcmpi(u.nombreUsuario, nomUsuario)==0) && u.eliminado==0 && u.tipoUsuario==1) //si el usuario es administrador
                        {
                            flag=4;
                            k=7;
                        }

                        fseek(archi,0, SEEK_CUR); //reposiciona el cursor en la posicion actual
                    }
                }
                if(flag==0) //si el usuario no existe
                {
                    k=0;
                }

                fclose(archi);
                mostrarUsuariosRecuperadosEliminados(u, k, ADL, validos, arbol, x); //distintos mostrar
            }
        }
        else
        {
            system("cls");
            printf("No hay ningun usuario cliente eliminado por recuperar, presione cualquier tecla para volver al menu:\n");
            getch();
            subMenuAdmin(ADL,validos,arbol,u);
        }
    }
    else //si no quiere recuperar ningun usuario eliminado
    {
        subMenuAdmin(ADL,validos,arbol,u);
    }
}


//da de baja a un usuario, es decir que lo elimina logicamente
void darDeBajaUsuario(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario x)
{
    system("cls");
    char opcion;
    char nomUsuario[30];
    stUsuario u;
    int flag=0;
    int pos=0;
    int k=99; //para los mostrar

    printf("*********************************************************\n");
    printf("*<>*<>*<>*<>*< DAR DE BAJA USUARIO CLIENTE >*<>*<>*<>*<>*\n");
    printf("*********************************************************\n\n");

    printf("Si desea dar de baja a un usuario cliente seleccione cualquier tecla, caso contrario seleccione ESC:\n");
    opcion=getch();

    if(opcion!=27)
    {
        system("cls");

        todosLosUsuarios();//muestra todos los usuarios del archivo usuarios.dat

        printf("\nIngrese el nombre del usuario cliente que desea eliminar:\n");

        gets(nomUsuario);

        //se administran todos los usuarios del sistema, aun los no aprobados, por eso se analiza desde el archivo y no el arreglo (Ej.: eliminar usuario aun no aprobado que no esta en el arreglo)
        FILE*archi=fopen("usuarios.dat","r+b");
        if(archi!=NULL)
        {
            while(!feof(archi)&& flag==0) //hasta que llegue al final del archivo y flag valga 0
            {
                fread(&u,sizeof(stUsuario),1,archi);

                if(!feof(archi))
                {
                    if((strcmpi(u.nombreUsuario, nomUsuario)==0) && u.eliminado==0 && u.tipoUsuario==0) //elimino al usuario logicamente
                    {
                        pos=ftell(archi)/sizeof(stUsuario); //busco la posicion actual
                        fseek(archi, (pos-1)*sizeof(stUsuario), SEEK_SET); //busco la posicion que necesito, -1 asi me posiciona el cursor delante para escribir
                        u.eliminado=1; //elimino al usuario logicamente
                        fwrite(&u, sizeof(stUsuario), 1, archi); //modifico el registro
                        flag=1; //corta el while
                        k=4; //para el mostrar
                    }
                    else if ((strcmpi(u.nombreUsuario, nomUsuario)==0) && u.eliminado==1 && u.tipoUsuario==0) //si el usuario ya estaba eliminado
                    {
                        flag=2;
                        k=5; //para el mostrar
                    }
                    else if((strcmpi(u.nombreUsuario, nomUsuario)==0) && u.eliminado==0 && u.tipoUsuario==1) //si el usuario es administrador
                    {
                        flag=4;
                        k=6; //para el mostrar
                    }

                    fseek(archi,0, SEEK_CUR); //reposiciona el cursor en la posicion actual
                }
            }
            if(flag==0) //si el usuario no existe
            {
                k=0; //para el mostrar
            }
            fclose(archi);
            mostrarUsuariosRecuperadosEliminados(u, k, ADL, validos, arbol, x); //mostrar distintas opciones
        }

    }
    else
    {
        subMenuAdmin(ADL,validos,arbol,u);
    }

}



//modifica los datos de un usuario cliente
void modifUssAdmin(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    char opcion;
    int flag=0;
    int id;
    char opc=27;
    stUsuario c;//usuario a modificar

    printf("******************************************************\n");
    printf("*<>*<>*<>*<>*< MODIFICACION DE USUARIOS >*<>*<>*<>*<>*\n");
    printf("******************************************************\n\n");

    printf("Si desea modificar los datos de un usuario cliente presione cualquier tecla, caso contrario ESC:\n");
    opcion=getch();
    if(opcion!=27)
    {
        system("cls");
        printf("**********************************************************\n");
        printf("Ingrese el id del usuario del cliente que desea modificar:\n");
        printf("**********************************************************\n");

        todosLosUsuarios(); //muestro todos los usuarios
        scanf("%d", &id);
        c=buscarId(id,&flag);
        system("cls");

        if(flag==1)  // si existe el usuario y es cliente
        {
            mostrarDatosUsuario(c);
            subMenModifRegAdmin(u,c,ADL,validos,arbol);
        }
        else // mensajes de error
        {
            if(flag==2)
            {
                printf("************************************************\n");
                printf("El usuario que quiere modificar es administrador\n");
                printf("************************************************\n\n");
            }

            else // if flag==0
            {
                printf("****************************************\n");
                printf("No existe un usuario con el id ingresado\n");
                printf("****************************************\n\n");
            }

            printf("Intente nuevamente presionando cualquier tecla o presione ESC para volver al menu de administracion de usuarios:\n");
            opc=getch();
            if(opc!=27)
                modifUssAdmin(ADL,validos,arbol,u);
            else
                subMenuAdmin(ADL,validos,arbol,u);
        }
    }
    else
    {
        subMenuAdmin(ADL,validos,arbol,u);
    }
}

//consulta un usuario a traves de su ID
void consultaExistUsuario(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    int flag=0;
    int id=0;
    char opc=27;
    char opcion;
    stUsuario c;//usuario a buscar
    printf("**************************************************\n");
    printf("*<>*<>*<>*<>*< CONSULTA DE USUARIOS >*<>*<>*<>*<>*\n");
    printf("**************************************************\n");

    printf("Si desea consultar los datos de un usuario presione cualquier tecla, caso contrario ESC:\n");
    opcion=getch();
    if(opcion!=27)
    {
        system("cls");
        todosLosUsuarios(); //muestro todos los usuarios

        printf("Ingrese el ID del usuario que desea consultar:\n");

        scanf("%d", &id);
        fflush(stdin);
        c=buscarId(id,&flag); //busca el registro del usuario (que debe estar registrado)

        if(flag==1 || flag==2)  // sea admin o cliente
        {
            system("cls");
            mostrarDatosUsuario(c);
            printf("Si desea volver a intentar presione cualquier tecla, caso contrario ESC:\n");
            opc=getch();
            if(opc!=27)
            {
                consultaExistUsuario(ADL,validos,arbol,u);
            }
            else
            {
                subMenuAdmin(ADL,validos,arbol,u);
            }

        }
        else// if flag==0 - mensaje de error
        {
            system("cls");
            printf("************************************************************************\n");
            printf("ERROR: El usuario ingresado no se encuentra registrado en el sistema\n");
            printf("Si desea volver a intentar presione cualquier tecla, caso contrario ESC:\n");
            printf("************************************************************************\n");

            opc=getch();
            if(opc!=27)
            {
                consultaExistUsuario(ADL,validos,arbol,u);
            }
            else
            {
                subMenuAdmin(ADL,validos,arbol,u);
            }
        }
    }
    else //si no desea consultar
    {
        subMenuAdmin(ADL,validos,arbol,u);
    }
}


/*
Cuenta la cantidad de usuarios totales que hay en el archivo, crea un arreglo de dimension justa
Copia los elementos del archivo al arreglo de dimension justa ordenandolos de menor a mayor
y los muestra por pantalla
*/

void listadoUsuarios(stCelda **ADL, int *validos, nodoArbolCancion *arbol, stUsuario u)
{
    system("cls");
    char opcion;
    printf("***************************************************************************************\n");
    printf("*<>*<>*<>*<>*< LISTADO DE USUARIOS ORDENADOS POR NOMBRE DE MAYOR A MENOR >*<>*<>*<>*<>*\n");
    printf("***************************************************************************************\n\n");

    printf("Si desea ver la lista de usuario presione cualquier tecla, caso contrario ESC:\n");
    opcion=getch();

    if(opcion!=27)
    {
    system("cls");
    int cantidad= cuentaRegistroArchivo(); // cuenta la cantidad de usuarios totales en el archivo
    stUsuario*a = (stUsuario*)malloc(sizeof(stUsuario)*cantidad); // crea un arreglo dinamico de dimension justa

    archivoToArreglo(a); //pasa los elementos del archivo al arreglo
    ordenarPorNombreUsr(a,cantidad); // ordena el arreglo por nombre
    mostrarArregloUsuarios(a,cantidad); //muetra el arreglo por pantalla

    printf("\nFIN de la lista de usuarios\n");
    printf("Presione cualquier tecla para volver al menu de administracion de usuarios:\n");
    getch();

    subMenuAdmin(ADL,validos,arbol,u); // retorna al sub menu de aministracion
    }
    else
    {
        subMenuAdmin(ADL,validos,arbol,u); // retorna al sub menu de aministracion
    }

}



//permite dar de baja una cancion logicamente del arbol de canciones disponibles
void darDeBajaCancion(stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    char opcion;
    int id=0;

    printf("**********************************************\n");
    printf("*<>*<>*<>*<>*< ELIMINAR CANCION >*<>*<>*<>*<>*\n");
    printf("**********************************************\n");

    printf("Si desea eliminar una cancion de la lista seleccione cualquier tecla, caso contrario seleccione ESC:\n");

    opcion=getch();

    if(opcion!=27)//si desea eliminar una cancion
    {
        do
        {
            inOrder(arbol);
            printf("************************************************************************\n");
            printf("Ingrese el ID de la cancion que desea eliminar de la lista de canciones\n:");
            printf("************************************************************************\n");
            fflush(stdin);
            scanf("%d", &id);

            int validacion=validarIdCancion(id); //valida que el ID ingresado sea un ID valido para alguna cancion
            if(validacion!=1) //si el ID no es valido
            {
                system("cls");
                printf("\nERROR: El ID seleccionado no es valido\n");
                printf("Si desea volver a intentar presione cualquier tecla, caso contrario seleccione ESC:\n");
                opcion=getch();

                if(opcion!=27)
                {
                    darDeBajaCancion(ADL, validos, arbol, u); //si ingreso un id errone y desea continuar, llamada recursiva a la misma funcion
                }
                else
                {
                    subMenuAdminCanciones(ADL, validos, arbol, u); //si no quiere dar de baja una cancion regresa al menu de admin canciones
                }
            }
            else
            {
                arbol=borrarCancionArbol(arbol, id); //elimina la cancion del arbol
                eliminarCancionArchivo (id); //elimina la cancion del archivo canciones.dat (cambia a 1)

                system("cls");

                printf("*******************************************************************************\n");
                printf("La cancion fue eliminada con exito\n");
                printf("Si desea eliminar mas canciones seleccione cualquier tecla, caso contrario ESC:\n");
                printf("********************************************************************************\n");

                opcion=getch();
            }
        }
        while(opcion!=27);
    }
    else
    {
        subMenuAdminCanciones(ADL, validos, arbol, u); //si no quiere agregar canciones lo retorna al menu de administracion de canciones
    }

    subMenuAdminCanciones(ADL, validos, arbol, u); //si no quiere continuar eliminando canciones, lo envia al menu

}


//restaura canciones eliminadas logicamente
void restaurarCancion (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    char opcion;
    int id=0;
    stCancion cancion;

    printf("*********************************************************\n");
    printf("*<>*<>*<>*<>*< RESTAURAR CANCION ELIMINADA >*<>*<>*<>*<>*\n");
    printf("*********************************************************\n");

    printf("Si desea restaurar una cancion eliminada seleccione cualquier tecla, caso contrario seleccione ESC:\n");


    opcion=getch();

    if(opcion!=27)//si desea restaurar una cancion
    {
        do
        {
            int verif=verificarCancionesEliminadas();
            if(verif==1) //si hay almenos 1 cancion eliminada
            {
                system("cls");
                mostrarCancionesEliminadas();

                printf("*********************************************************************\n");
                printf("Ingrese el ID de la cancion que desea restaurar a lista de canciones:\n");
                printf("*********************************************************************\n");
                fflush(stdin);
                scanf("%d", &id);

                int validar=validarCancionEliminada(id);

                if(validar!=1) //si el ID no es valido
                {
                    system("cls");
                    printf("***********************************************************************************\n");
                    printf("ERROR: El ID seleccionado no es valido\n");
                    printf("Si desea volver a intentar presione cualquier tecla, caso contrario seleccione ESC:\n");
                    printf("***********************************************************************************\n");
                    opcion=getch();

                    if(opcion!=27)
                    {
                        restaurarCancion(ADL, validos, arbol, u); //si ingreso un id errone y desea continuar, llamada recursiva a la misma funcion
                    }
                    else
                    {
                        subMenuAdminCanciones (ADL, validos, arbol, u); //lo envia al submenu si no quiere restaurar canciones
                    }
                }
                else
                {
                    restaurarCancionArchivo (id); //restaura la cancion elegida
                    cancion=retornaCancionEliminada (id); //retorna la cancion buscada para cargarla en el arbol
                    nodoArbolCancion*restCancion=crearNodoArbol(cancion); //creo un nodo arbol con la cancion
                    arbol=InsertarCancionArbol(arbol, restCancion); //agrego la cancion al arbol de canciones

                    system("cls");

                    printf("\n\n******************************************************************************\n");
                    printf("La cancion fue restaurada con exito\n");
                    printf("\nSi desea restaurar mas canciones seleccione cualquier tecla, caso contrario ESC:\n");
                    printf("**********************************************************************************\n");

                    opcion=getch();
                }

            }
            else
            {
                system("cls");
                printf("*******************************************************************************************\n");
                printf("No hay canciones eliminadas para restaurar, seleccione cualquier tecla para volver al menu:\n");
                printf("*******************************************************************************************\n");
                getch();
                subMenuAdminCanciones (ADL, validos, arbol, u);
            }

        }
        while(opcion!=27);

    }
    else
    {
        subMenuAdminCanciones(ADL, validos, arbol, u); //si no quiere eliminar canciones lo retorna al menu de administracion de canciones
    }

    subMenuAdminCanciones(ADL, validos, arbol, u); //si no quiere continuar eliminando canciones, luego de haber eliminado ya, lo envia al menu

}



void cancionesGenero (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    char opcion;
    int validosCanciones=0;
    char generoBuscado[20];
    int flag;
    stCancion*arregloCancion;

    validosCanciones=cargarADLConsulta(&arregloCancion); //carga un arreglo justo con la cantidad de canciones de canciones.dat

    printf("************************************************\n");
    printf("*<>*<>*<>*<>*< CANCION POR GENERO >*<>*<>*<>*<>*\n");
    printf("************************************************\n");

    printf("Ingrese el genero que desea buscar:\n");

    fflush(stdin);
    gets(generoBuscado);
    flag=verificarCancionesGenero(generoBuscado); //verifica que el genero ingresado exista en el archivo de canciones.dat

    if(flag!=1) //si el genero no se encontro
    {
        system("cls");
        printf("***********************************************************************************\n");
        printf("ERROR: No fue encontrada ninguna cancion con el genero deseado\n");
        printf("Si desea volver a intentar presione cualquier tecla, caso contrario seleccione ESC:\n");
        printf("***********************************************************************************\n");
        opcion=getch();

        if(opcion!=27)
        {
            cancionesGenero(ADL, validos, arbol, u); //si ingreso un genero que no existe y desea continuar, llamada recursiva a la misma funcion
        }
        else
        {
            subMenuAdminCanciones (ADL, validos, arbol, u); //lo envia al submenu si no quiere continuar
        }
    }
    else
    {
        system("cls");
        printf("*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>* GENERO <%s> *<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*\n", generoBuscado);
        buscarCancionGenero (&arregloCancion, validosCanciones, generoBuscado);

        printf("Si desea ver otro genero presione cualquier tecla, caso contrario seleccione ESC:\n");
        opcion=getch();

        if(opcion!=27)
        {
            cancionesGenero(ADL, validos, arbol, u); //desea continuar, llamada recursiva a la misma funcion
        }
        else
        {
            subMenuAdminCanciones (ADL, validos, arbol, u); //lo envia al submenu si no quiere continuar
        }

    }

}


//carga un arreglo de canciones con canciones de archivo canciones.dat
int cargarADLConsulta(stCancion**ADL)
{
    int dimension=cancionesActivas(); //cuenta la cantidad de canciones para determinar la dimension justa para el arreglo
    int validos=0;
    stCancion cancion;

    (*ADL)=(stCancion*)malloc(dimension*sizeof(stCancion)); // le doy dimension justa con la cantidad de canciones en el archivo

    FILE*archi=fopen("canciones.dat","rb");
    if(archi!=NULL)
    {
        while(fread(&cancion,sizeof(stCancion),1,archi)>0)
        {
            validos=cancionToArregloConsulta(ADL,validos,cancion); // cargo la cancion en el arreglo
        }
        fclose(archi);
    }
    return validos; //retorno la cantidad de usuarios que cargue en el arreglo
}



//almacena la cancion en el arreglo dinamico
int cancionToArregloConsulta (stCancion**ADL, int validos, stCancion cancion)
{
    strcpy((*ADL)[validos].titulo, cancion.titulo); //agrego la cancion al arreglo en la posicion "validos" mi poosicion sin datos
    strcpy((*ADL)[validos].album, cancion.album);
    strcpy((*ADL)[validos].artista, cancion.artista);
    strcpy((*ADL)[validos].genero, cancion.genero);
    strcpy((*ADL)[validos].comentario, cancion.comentario);
    (*ADL)[validos].anio=cancion.anio;
    (*ADL)[validos].duracion=cancion.duracion;
    (*ADL)[validos].eliminado=cancion.eliminado;
    (*ADL)[validos].idCancion=cancion.idCancion;

    validos++; //sumo validos por cada cancion agregada
    return validos;
}



//muestra una cancion por titulo ingresado
void cancionesTitulo (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    char opcion;
    int validosCanciones=0;
    char tituloBuscado[20];
    int flag;
    stCancion*arregloCancion;

    validosCanciones=cargarADLConsulta(&arregloCancion); //carga un arreglo justo con la cantidad de canciones de canciones.dat
    printf("************************************************\n");
    printf("*<>*<>*<>*<>*< CANCION POR TITULO >*<>*<>*<>*<>*\n");
    printf("************************************************\n");

    mostrarArregloCanCorto(&arregloCancion, validosCanciones);

    printf("Ingrese el titulo que desea buscar:\n");


    fflush(stdin);
    gets(tituloBuscado);
    flag=verificarCancionesTitulo(tituloBuscado); //verifica que el titulo ingresado exista en el archivo de canciones.dat

    if(flag!=1) //si el genero no se encontro
    {
        system("cls");
        printf("***********************************************************************************\n");
        printf("ERROR: No fue encontrada ninguna cancion con el titulo deseado\n");
        printf("Si desea volver a intentar presione cualquier tecla, caso contrario seleccione ESC:\n");
        printf("***********************************************************************************\n");
        opcion=getch();

        if(opcion!=27)
        {
            cancionesTitulo(ADL, validos, arbol, u); //si ingreso un titulo que no existe y desea continuar, llamada recursiva a la misma funcion
        }
        else
        {
            subMenuAdminCanciones (ADL, validos, arbol, u); //lo envia al submenu si no quiere continuar
        }
    }
    else
    {
        system("cls");
        printf("*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>* TITULO <%s> *<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*\n", tituloBuscado);
        buscarCancionTitulo (&arregloCancion, validosCanciones, tituloBuscado);

        printf("Si desea ver otra cancion presione cualquier tecla, caso contrario seleccione ESC:\n");
        opcion=getch();

        if(opcion!=27)
        {
            cancionesTitulo(ADL, validos, arbol, u); //desea continuar, llamada recursiva a la misma funcion
        }
        else
        {
            subMenuAdminCanciones (ADL, validos, arbol, u); //lo envia al submenu si no quiere continuar
        }
    }
}


//busca en el arreglo alguna cancion con el mismo titulo al solicitado
void buscarCancionTitulo (stCancion**ADL, int validos, char titulo[])
{
    int i=0;
    while(i<validos)
    {
        if(strcmpi((*ADL)[i].titulo, titulo)==0) //si el genero solicitado es igual al genero de la cancion
        {
            mostrarArregloCan(ADL, i); //muestra la cancion
            i++;
        }
        else
        {
            i++;
        }
    }
}

//muestra los datos de una cancion a traves de su ID
void consultaCanciones (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    char opcion;
    int validosCanciones=0;
    int id=0;
    int flag;
    stCancion*arregloCancion; //se crea un arreglo de canciones como se solicita

    validosCanciones=cargarADLConsulta(&arregloCancion); //carga un arreglo justo con la cantidad de canciones de canciones.dat

    printf("***************************************************\n");
    printf("*<>*<>*<>*<>*< CONSULTA DE CANCIONES >*<>*<>*<>*<>*\n");
    printf("***************************************************\n");

    mostrarArregloCanCorto(&arregloCancion, validosCanciones);

    printf("Ingrese el id de la cancion desea consultar:\n");

    fflush(stdin);
    scanf("%d", &id);
    flag=verificarExisteId(id); //verifica que el id ingresado exista en el archivo de canciones.dat

    if(flag!=1) //si el ID no se encontro
    {
        system("cls");
        printf("***********************************************************************************\n");
        printf("ERROR: No fue encontrada ninguna cancion con el id ingresado\n");
        printf("Si desea volver a intentar presione cualquier tecla, caso contrario seleccione ESC:\n");
        printf("***********************************************************************************\n");

        opcion=getch();

        if(opcion!=27)
        {
            consultaCanciones(ADL, validos, arbol, u); //si ingreso un id que no existe y desea continuar, llamada recursiva a la misma funcion
        }
        else
        {
            subMenuAdminCanciones (ADL, validos, arbol, u); //lo envia al submenu si no quiere continuar
        }
    }
    else
    {
        system("cls");
        printf("*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>* ID <%d> *<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*\n", id);
        printf("\n");
        buscarCanIdArreglo(&arregloCancion, validosCanciones, id);


        printf("Si desea consultar por otra cancion presione cualquier tecla, caso contrario seleccione ESC:\n");
        opcion=getch();

        if(opcion!=27)
        {
            consultaCanciones(ADL, validos, arbol, u); //desea continuar, llamada recursiva a la misma funcion
        }
        else
        {
            subMenuAdminCanciones (ADL, validos, arbol, u); //lo envia al submenu si no quiere continuar
        }
    }
}


//busca en el arreglo alguna cancion con el mismo ID al solicitado
void buscarCanIdArreglo (stCancion**ADL, int validos, int id)
{
    int i=0;
    while(i<validos)
    {
        if((*ADL)[i].idCancion==id) //si el id solicitado es el mismo al ID de la cancion
        {
            mostrarArregloCan(ADL, i); //muestra la cancion
            i++;
        }
        else
        {
            i++;
        }
    }
}

//permite modificar todas las canciones existentes en el sistema, aun las eliminadas logicamente
void modificacionDeCanciones (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    char opcion;
    stCancion cancion;
    int id=0;
    printf("*******************************************************\n");
    printf("*<>*<>*<>*<>*< MODIFICACION DE CANCIONES >*<>*<>*<>*<>*\n");
    printf("*******************************************************\n");

    printf("Si desea modificar una cancion presione cualquier tecla, caso contrario ESC:\n");
    opcion=getch();

    if(opcion!=27)
    {
        system("cls");
        mostrarArchivoCanciones (); //muestra todas las canciones existentes para modificar
        printf("\nIngrese el ID de la cancion que desea modificar:\n");
        fflush(stdin);
        scanf("%d", &id);

        int flag=verificarExisteId(id); //verifica que el id ingresado exista en el archivo de canciones.dat

        if(flag!=1) //si el ID no se encontro
        {
            system("cls");
            printf("***********************************************************************************\n");
            printf("ERROR: No fue encontrada ninguna cancion con el id ingresado\n");
            printf("Si desea volver a intentar presione cualquier tecla, caso contrario seleccione ESC:\n");
            printf("***********************************************************************************\n");

            opcion=getch();

            if(opcion!=27)
            {
                modificacionDeCanciones(ADL, validos, arbol, u); //si ingreso un id que no existe y desea continuar, llamada recursiva a la misma funcion
            }
            else
            {
                subMenuAdminCanciones (ADL, validos, arbol, u); //lo envia al submenu si no quiere continuar
            }
        }
        else
        {
            system("cls");
            cancion=buscarCancionRetornarla (id); //busco la cancion y la retorno para modificarla
            cancion=menuModificacionCanciones (ADL, validos, arbol, u, cancion); //envio la cancion al menu de modificacion
            arbol=borrarCancionArbol(arbol, id); //borro la cancion sin modificar del arbol
            nodoArbolCancion*modificado=crearNodoArbol(cancion); //crear nodo para agregar al arbol
            arbol=InsertarCancionArbol(arbol, modificado); //inserto la cancion con datos modificacion en el arbol
            modificarCancionArchivo (cancion.idCancion, cancion); //modifico los datos en el archivo
            system("cls");

            mostrarDatosCancion(cancion);

            printf("La cancion fue modificada con exito\n");
            printf("Si desea modificar otra cancion presione cualquier tecla, caso contrario ESC:\n");
            opcion=getch();

            if(opcion!=27)
            {
                modificacionDeCanciones(ADL, validos, arbol, u); //si ingreso un id que no existe y desea continuar, llamada recursiva a la misma funcion
            }
            else
            {
                subMenuAdminCanciones (ADL, validos, arbol, u); //lo envia al submenu si no quiere continuar
            }
        }

    }
    else
    {
        subMenuAdminCanciones (ADL, validos, arbol, u);
    }

}



void recibirMensaje (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    char opcion;
    char mensaje[300];

    printf("************************************\n");
    printf("*<>*<>*<>*<>*< CORREO >*<>*<>*<>*<>*\n");
    printf("************************************\n");

    printf("Si desea leer un mensaje seleccione cualquier tecla, caso contrario ESC:\n");
    opcion=getch();

    if(opcion!=27)
    {
        system("cls");
        leerMensajeAdministrador ();
    }

    subMenuAdmin(ADL, validos, arbol, u);
}


void listaTotalCancionesActivas(stCelda **ADL, int *validos, nodoArbolCancion *arbol, stUsuario u)
{
    system("cls");
    char opcion;
    stCancion cancion;
    int id=0;
    printf("**********************************************************\n");
    printf("*<>*<>*<>*<>*< LISTADO DE CANCIONES ACTIVAS >*<>*<>*<>*<>*\n");
    printf("**********************************************************\n");

    printf("Si desea ver la lista de canciones activas presione cualquier tecla, caso contrario ESC:\n");
    opcion=getch();

    if(opcion!=27)
    {
        inOrder(arbol);
        printf("\nPresione cualquier tecla para regresar al menu de administracion de canciones\n");
        getch();
    }

    subMenuAdminCanciones(ADL, validos, arbol, u);
}



//consulta si el administrador desea eliminar una cancion de forma permanente (fisicamente) del archivo de canciones.dat
void eliminarCancionAdminFisicamente (stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    stCancion cancion;
    char opcion;
    printf("***********************************************************************\n");
    printf("ATENCION: la cancion elegida sera eliminada permanentemente del sistema\n");
    printf("Si desea continuar seleccione cualquier tecla, caso contrario ESC:\n");
    printf("***********************************************************************\n");
    opcion=getch();
    int id;
    if(opcion!=27)
    {
        int verifExiste=verificarExisteAlgunaCancion(); //verifica que haya al menos 1 cancion en el archivo de canciones
        if(verifExiste==1) //si hay al menos 1 cancion en el archivo de canciones
        {
            system("cls");

            totalidadCancionesArchivo(); //muestra la totalidad de las canciones en el archivo.dat (aun las eliminadas logicamente)

            printf("***************************************************************************\n");
            printf("Ingrese el ID de la cancion que desea eliminar permanentemente del sistema:\n");
            printf("***************************************************************************\n");
            fflush(stdin);
            scanf("%d", &id);

            int flag=verificarExisteId(id); //verifica que exista la cancion en el archivo

            if(flag!=1) //si el ID no es valido
            {
                system("cls");
                printf("***********************************************************************************\n");
                printf("ERROR: El ID seleccionado no es valido\n");
                printf("Si desea volver a intentar presione cualquier tecla, caso contrario seleccione ESC:\n");
                printf("***********************************************************************************\n");
                opcion=getch();

                if(opcion!=27)
                {
                    eliminarCancionAdminFisicamente (ADL, validos, arbol, u); //si ingreso un id errone y desea continuar, llamada recursiva a la misma funcion
                }
                else
                {
                    subMenuAdminCanciones (ADL, validos, arbol, u); //lo envia al submenu si no quiere eliminar cancion
                }
            }
            else
            {
                cancion=buscarCancionRetornarla (id); //busco la cancion en el archivo y la retorno
                arbol=borrarCancionArbol(arbol, id); //elimina la cancion del arbol de canciones
                eliminarCancionArchivoCanciones (cancion); //elimino la cancion del archivo fisicamente

                system("cls");

                printf("\n\n**************************************************************************\n");
                printf("La cancion fue eliminada permanentemente con exito\n");
                printf("\nSi desea intentar nuevamente seleccione cualquier tecla, caso contrario ESC:\n");
                printf("******************************************************************************\n");

                opcion=getch();

                if(opcion!=27)
                {
                    eliminarCancionAdminFisicamente (ADL, validos, arbol, u);
                }
                else
                {
                    subMenuAdminCanciones(ADL, validos, arbol, u); //si no quiere eliminar canciones lo retorna al menu de administracion de canciones
                }
            }

        }
        else //si no hay ninguna cancion en el archivo de canciones
        {
            system("cls");
            printf("*******************************************************************************\n");
            printf("No hay canciones en el sistema, seleccione cualquier tecla para volver al menu:\n");
            printf("*******************************************************************************\n");
            getch();
            subMenuAdminCanciones (ADL, validos, arbol, u);
        }

    }
    else
    {
        subMenuAdminCanciones(ADL, validos, arbol, u); //si no quiere eliminar canciones lo retorna al menu de administracion de canciones
    }
}



