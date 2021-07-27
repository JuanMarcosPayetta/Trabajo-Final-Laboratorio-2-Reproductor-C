#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "gestionArchivos.h"
#include "gestionPlaylist.h"
#include "sistema.h"

//busca que el nombre de usuario ingresado se encuentre registrado
stUsuario buscarNombreInicioSesion(char nombre[], int*flag)
{
    stUsuario u;
    int corte=0;

    FILE*archi=fopen("usuarios.dat","rb");
    if(archi!=NULL)
    {
        while((*flag==0) && corte==0) //si flag nunca cambia de valor, "corte" evita que se continue llamando infinitamente
        {

            while((*flag)==0 && fread(&u,sizeof(stUsuario),1,archi)>0)  //que lea el archivo mientras que no haya encontrado el nombre y flag sea =0
            {
                if(strcmpi(u.nombreUsuario, nombre)==0)
                {
                    (*flag)=1; //encontro el nombre en el archivo
                }
            }
            if(*flag==0) //si recorrio todo el archivo y NO encontro el nombre, corta
            {
                corte=1;
            }

        }
        fclose(archi);
    }
    return u;
}


//agrega un usuario al final del archivo usaurios.dat
void agregarUsuarioToArchivo (stUsuario u)
{
    FILE*archi=fopen("usuarios.dat", "ab");

    if(archi!=NULL)
    {
        fwrite(&u, sizeof(stUsuario), 1, archi);
        fclose(archi);
    }
    else
    {
        printf("ERROR: El archivo no pudo escribirse\n");
    }
}



//lee el archivo usuarios.dat y cuenta los usuarios activos
int usuariosActivos()
{
    int usuarioActiv=0;
    stUsuario u;

    FILE*archi=fopen("usuarios.dat","rb");
    if(archi!=NULL)
    {
        while(fread(&u,sizeof(stUsuario),1,archi)>0)
        {
            if(u.eliminado==0 && u.aprobado==1 && u.tipoUsuario==0) //si el usuario (no administrador) no esta eliminado y ademas esta aprobado,lo cuento
            {
                usuarioActiv++;
            }
        }
        fclose(archi);
    }
    return usuarioActiv;
}


//muestra todos los usuarios existentes en el archivo de usuarios.dat
void todosLosUsuarios()
{
    stUsuario u;

    FILE*archi=fopen("usuarios.dat","rb");
    if(archi!=NULL)
    {
        while(fread(&u,sizeof(stUsuario),1,archi)>0)
        {
          mostrarDatosUsuario(u);
        }

        fclose(archi);
    }
}


//muestra todos los usuarios cliente eliminados en el archivo de usuarios.dat
void todosLosUsuariosEliminados()
{
    stUsuario u;

    FILE*archi=fopen("usuarios.dat","rb");
    if(archi!=NULL)
    {
        while(fread(&u,sizeof(stUsuario),1,archi)>0)
        {
            if(u.eliminado==1 && u.tipoUsuario==0) //si el usuario cliente esta eliminado lo muestra
            {
                mostrarDatosUsuario(u);
            }
        }

        fclose(archi);
    }
}


//cuenta la cantidad de registros en el archivo de usuarios
int cuentaRegistroArchivo()
{

    int cantidad =0;
    FILE *archi=fopen("usuarios.dat","rb");
    if(archi!=NULL)
    {
        // me posiciono al final del archivo
        fseek(archi,0,SEEK_END);

        cantidad = ftell(archi)/sizeof(stUsuario);
        fclose(archi);
    }
    return cantidad;
}


//busca que el id de usuario ingresado se encuentre registrado
stUsuario buscarId (int id, int*flag)
{
    stUsuario u;
    int corte=0;

    FILE*archi=fopen("usuarios.dat","rb");
    if(archi!=NULL)
    {
        while((*flag==0) && corte==0) //si flag nunca cambia de valor, "corte" evita que se continue llamando infinitamente
        {
            while((*flag)==0 && fread(&u,sizeof(stUsuario),1,archi)>0)  //que lea el archivo mientras que no haya encontrado el nombre y flag sea =0
            {
                if(u.idUsuario == id && u.tipoUsuario==0) // si el id pertenece a un cliente (se puede modificar)
                {
                    (*flag)=1; //encontro el id en el archivo
                }
                else if(u.idUsuario == id && u.tipoUsuario==1) // si el id pertenece a un admin (NO se puede modificar)
                {
                    (*flag)=2;
                }
            }
            if(*flag==0) //si recorrio todo el archivo y NO encontro el id, corta
            {
                corte=1;
            }
        }
        fclose(archi);
    }
    return u;
}




//busca la posicion de un usuario cliente en el archivo de usuarios.dat
int buscarPosicionUsuarioArchivo(stUsuario usuario)
{
    stUsuario u;
    int flag=0;
    int pos=0;

    FILE*archi=fopen("usuarios.dat","rb");
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag==0) //mientras el archivo no llegue al final y flag sea 0
        {
            fread(&u,sizeof(stUsuario),1,archi);

            if(!feof(archi))
            {
                if((strcmpi(u.nombreUsuario, usuario.nombreUsuario)==0)&& u.tipoUsuario==0) //busco el usuario
                {
                    pos=ftell(archi)/sizeof(stUsuario); //busco la posicion actual
                    flag=1; //corta el while
                }
                fseek(archi,0, SEEK_CUR); //reposiciona el cursor en la posicion actual
            }
        }

        fclose(archi);
    }
    return pos;
}

//modifica los datos de un usuario cliente
void modificarClienteArchivo(stUsuario c, int flag, stCelda**ADL, int*validos, nodoArbolCancion*arbol, stUsuario u)
{
    system("cls");
    int pos=0;

    printf("\n\n");
    pos=buscarPosicionUsuarioArchivo(c);

    FILE*archi=fopen("usuarios.dat","r+b");
    if(archi!=NULL)
    {
        fseek(archi, (pos-1)*sizeof(stUsuario), SEEK_SET); //busco la posicion que necesito, -1 asi me posiciona el curso delante para escribir

        if(flag==1)
        {
            c=cargaAnioNac(c);
            fwrite(&c, sizeof(stUsuario), 1, archi);
        }
        if(flag==2)
        {
            c=cargaGenero(c);
            fwrite(&c, sizeof(stUsuario), 1, archi);
        }
        if(flag==3)
        {
            c=cargaPais(c);
            fwrite(&c, sizeof(stUsuario), 1, archi);
        }
        if(flag==4)
        {
            c=cargaCorreoE(c);
            fwrite(&c, sizeof(c), 1, archi);
        }
        fclose(archi);
    }
    system("cls");
    printf("\n\n");
    mostrarDatosUsuario(c);
    subMenModifRegAdmin(u,c,ADL,validos,arbol);
}


/*
Pasa los elementos del archivo al arreglo dinamico, no utiliza validos ya que el arreglo es
de dimension justa
*/
void archivoToArreglo(stUsuario a[])
{
    stUsuario u;
    FILE*archi = fopen("usuarios.dat","rb"); //abre el archivo en modo lectura
    int i=0;
    if(archi)
    {
        while(fread(&u,sizeof(stUsuario),1,archi)>0)
        {
            a[i] = u; // copia la variable leida del archivo al arreglo
            i++; // recorre el arrglo dinamico
        }
        fclose(archi);
    }
}


//modificacion del registro de usuario en el archivo de usuarios
void modificacionUsuario (stUsuario u)
{
    int flag=0;
    int pos=0;
    stUsuario dato;
    FILE*archi=fopen("usuarios.dat","r+b");
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag==0) //hasta que llegue al final del archivo y flag valga 0
        {
            fread(&dato,sizeof(stUsuario),1,archi);

            if(!feof(archi))
            {
                if(dato.idUsuario==u.idUsuario) //si el id del usuario es igual al que esta registrado en el archivo
                {
                    pos=ftell(archi)/sizeof(stUsuario); //busco la posicion actual
                    fseek(archi, (pos-1)*sizeof(stUsuario), SEEK_SET); //busco la posicion que necesito, -1 asi me posiciona el cursor delante para escribir
                    strcpy(dato.nombreUsuario, u.nombreUsuario);
                    strcpy(dato.correoElectronico, u.correoElectronico);
                    dato.genero=u.genero;
                    strcpy(dato.pais, u.pais);
                    strcpy(dato.pass, u.pass);
                    dato.anioNacimiento=u.anioNacimiento;
                    fwrite(&dato, sizeof(stUsuario), 1, archi); //modifico el registro
                    flag=1; //corta el while
                }

            }
        }
        fclose(archi);
    }
}



//retorno el id generado para una cancion
int idCancionesAutomaticas()
{
    stCancion cancion;
    int id = -1; //si no hay datos aun cargados, devolvera -1, y luego en la otra funcion se aumentara en 1 por lo que el primer id sera 0

    FILE *archi= fopen("canciones.dat","rb");
    if(archi!=NULL)
    {
        fseek(archi,sizeof(stCancion)*(-1),SEEK_END); //voy a la ultima posicion -1 para leerla
        if(fread(&cancion,sizeof(stCancion),1,archi)>0)
        {

            id=cancion.idCancion; //leo el ultimo id del archivo
        }
        fclose(archi);
    }
    return id;
}

//agregar una nueva cancion al archivo de canciones.dat
void cargarCancionArchivo(stCelda**ADL, int*validos, nodoArbolCancion**arbol, stUsuario u)
{
    system("cls");
    char opcion;
    stCancion cancion;
    int flag=3;

    printf("********************************************\n");
    printf("*<>*<>*<>*<>*< CARGAR CANCION >*<>*<>*<>*<>*\n");
    printf("********************************************\n");
    printf("Si desea ingresar una nueva cancion seleccione cualquier tecla, caso contrario seleccione ESC:\n");

    opcion=getch();

    if(opcion!=27)//si desea cargar una cancion
    {

        do
        {
            cancion=IngresarDatosCancion(); //cargo una variable de tipo stCancion con todas las propiedades de la cancion y la retorno
            system("cls");

            FILE*archi =fopen("canciones.dat","ab"); //si no existe lo crea y se posiciona al final para escribir la nueva cancion

            if(archi!=NULL)
            {
                fwrite(&cancion,sizeof(stCancion),1,archi); //escribo esa cancion en el archivo
                fclose(archi);
                mostrarArchivoCanciones ();
                getch();
                (*arbol)= InsertarCancionArbol(*arbol, crearNodoArbol(cancion)); //cargo esa nueva cancion al arbol

                system("cls");


                printf("********************************************\n");
                printf("*<>*<>*<>*<>*< CARGAR CANCION >*<>*<>*<>*<>*\n");
                printf("********************************************\n");
                printf("Cancion cargada en el sistema con exito\n");
                printf("Si desea cargar mas canciones seleccione cualquier tecla, caso contrario seleccione ESC:\n");
                opcion=getch();
            }
        }
        while(opcion!=27);    //carga tantas canciones como desee

        subMenuAdminCanciones (ADL, validos, *arbol, u); //si no quiere agregar canciones lo retorna al menu de administracion de canciones
    }
    else
    {
        subMenuAdminCanciones (ADL, validos, *arbol, u); //si no quiere agregar canciones lo retorna al menu de administracion de canciones
    }

}


//cuenta la cantidad de registros de canciones no eliminadas existentes en el archivo canciones.dat (para darle dimension al arreglo en el cual pasaremos la canciones, y luego este al arbol)
int registrosCanciones ()
{
    int registros=0;
    stCancion cancion;
    FILE*archi=fopen("canciones.dat", "rb");

    if(archi==NULL)
    {
        printf("ES NULL\n");
    }

    if(archi!=NULL)
    {
        while(fread(&cancion, sizeof(stCancion), 1, archi)>0)
        {
            if(cancion.eliminado==0) //cuenta las canciones no eliminadas
            {
                registros++;

            }
        }
        fclose(archi);

    }
    return registros;
}


//busca una cancion en el archivo de canciones y la devuelve
stCancion buscarCancionRetornarla (int id)
{
    stCancion c;
    int corte=0;
    int flag=0;

    FILE*archi=fopen("canciones.dat","rb");
    if(archi!=NULL)
    {
        while(flag==0 && corte==0) //si flag nunca cambia de valor, "corte" evita que se continue llamando
        {
            while(flag==0 && fread(&c,sizeof(stCancion),1,archi)>0)  //que lea el archivo mientras que no haya encontrado el nombre y flag sea =0
            {
                if(c.idCancion==id)
                {
                    flag=1; //encontro la cancion buscada
                }
            }
            if(flag==0) //si recorrio todo el archivo y NO encontro la cancion, corta
            {
                corte=1;
            }

        }
        fclose(archi);
    }
    return c; //retorno la cancion buscada
}


//Carga las canciones que no se encuentren eliminadas (eliminado=0) al arreglo dinamico para luego pasarlas al arbol de canciones balanceado
int archivoCancionesToArreglo(stCancion arreglo[])
{
    int i=0;
    stCancion cancion;

    FILE*archi=fopen("canciones.dat", "rb"); //abro en modo lectura
    if(archi!=NULL)
    {
        while(fread(&cancion,sizeof(stCancion),1, archi)>0) //mientras tenga datos el archivo que lea
        {
            if(cancion.eliminado==0) //la cancion no debe estar eliminada logicamente
            {
                arreglo[i] =cancion; //cargo en un arreglo de tipo stCancion una cancion
                i++;
            }
        }

        fclose(archi);
    }
    return i;
}


//elimina logicamente una cancion del archivo a traves de su ID
void eliminarCancionArchivo (int id)
{
    int flag=0;
    int pos;
    stCancion cancion;
    FILE*archi=fopen("canciones.dat","r+b");
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag==0) //hasta que llegue al final del archivo y flag valga 0
        {
            fread(&cancion,sizeof(stCancion),1,archi);

            if(!feof(archi))
            {
                if((cancion.idCancion==id) && cancion.eliminado==0) //si el id de la cancion leida es igual a la que quiero eliminar
                {
                    pos=ftell(archi)/sizeof(stCancion); //busco la posicion actual
                    fseek(archi, (pos-1)*sizeof(stCancion), SEEK_SET); //busco la posicion que necesito, -1 asi me posiciona el cursor delante para escribir
                    cancion.eliminado=1; //elimino la cancion logicamente
                    fwrite(&cancion, sizeof(stCancion), 1, archi); //modifico el registro
                    flag=1; //corta el while
                }

            }
        }
        fclose(archi);
    }
}

///se elimina FISICAMENTE una cancion del archivo playlist. Se crea un archivo auxiliar, se pasan todos los datos que se quieren mantener, y luego se borra y renombra el nuevo archivo
void eliminarCancionArchivoPlaylist (int idC, int idU)
{
    stPlaylist cancion;
    FILE*archi=fopen("playlist.dat","r+b");
    FILE*archiaux=fopen("playlistAux.dat", "a+b"); //creo un archivo auxiliar que contendra los archivos que no se quieren eliminar


    if((archi!=NULL) && (archiaux!=NULL))
    {
        while(!feof(archi)) //hasta que llegue al final del archivo
        {
            fread(&cancion,sizeof(stPlaylist),1,archi);

            if(!feof(archi))
            {
                if(cancion.idUsuario!=idU)  //escribo todas las canciones que no sean del usuario pasado por paramtro, al archivo auxiliar
                {
                    fwrite(&cancion, sizeof(stPlaylist), 1, archiaux);
                }

            }

        }
        fseek(archi, 0, SEEK_SET); //vuelvo al inicio

        while(fread(&cancion, sizeof(stPlaylist), 1, archi)>0)
        {
            if(cancion.idCancion!=idC && cancion.idUsuario==idU)
            {
                fwrite(&cancion, sizeof(stPlaylist), 1, archiaux);
            }
        }

        fclose(archi);
        fclose(archiaux);
        remove("playlist.dat"); //elimino el archivo que tiene el dato que no quiero
        rename("playlistAux.dat", "playlist.dat"); //nombro al nuevo archivo con los datos que quiero, como "playlist.dat"

    }
}


//retorna una cancion buscada
stCancion retornaCancionEliminada (int id)
{
    int flag=0;
    stCancion aux;
    stCancion cancion;
    FILE*archi=fopen("canciones.dat","r+b");
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag==0) //hasta que llegue al final del archivo y flag valga 0
        {
            fread(&cancion,sizeof(stCancion),1,archi);

            if(!feof(archi))
            {
                if(cancion.idCancion==id) //si el id de la cancion leida es igual a la que quiero eliminar
                {
                    aux=cancion;
                    flag=1; //corta el while
                }

            }
        }
        fclose(archi);
    }

    return aux;
}


//elimina una cancion del archivo a traves de su ID
void restaurarCancionArchivo (int id)
{
    int flag=0;
    int pos;
    stCancion cancion;
    FILE*archi=fopen("canciones.dat","r+b");
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag==0) //hasta que llegue al final del archivo y flag valga 0
        {
            fread(&cancion,sizeof(stCancion),1,archi);

            if(!feof(archi))
            {
                if((cancion.idCancion==id) && cancion.eliminado==1) //si el id de la cancion leida es igual a la que quiero eliminar
                {
                    pos=ftell(archi)/sizeof(stCancion); //busco la posicion actual
                    fseek(archi, (pos-1)*sizeof(stCancion), SEEK_SET); //busco la posicion que necesito, -1 asi me posiciona el cursor delante para escribir
                    cancion.eliminado=0; //elimino la cancion logicamente
                    fwrite(&cancion, sizeof(stCancion), 1, archi); //modifico el registro
                    flag=1; //corta el while
                }

            }
        }
        fclose(archi);
    }
}


//lee el archivo canciones.dat y cuenta las canciones
int cancionesActivas()
{
    int cancionesActivas=0;
    stCancion cancion;

    FILE*archi=fopen("canciones.dat","rb");
    if(archi!=NULL)
    {
        while(fread(&cancion,sizeof(stCancion),1,archi)>0)
        {
            cancionesActivas++; //cuenta la cantidad de canciones en el archivo canciones.dat
        }
        fclose(archi);
    }
    return cancionesActivas;
}


//modifico los datos de una cancion (lo hago en el archivo ya que esta es nuestra base de datos y puedo modificar canciones eliminadas logicamente)
void modificarCancionArchivo (int id, stCancion cModificada)
{
    int flag=0;
    int pos;
    stCancion cancion;
    FILE*archi=fopen("canciones.dat","r+b");
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag==0) //hasta que llegue al final del archivo y flag valga 0
        {
            fread(&cancion,sizeof(stCancion),1,archi);

            if(!feof(archi))
            {
                if(cancion.idCancion==id) //si el id de la cancion leida es igual a la que quiero modificar
                {
                    pos=ftell(archi)/sizeof(stCancion); //busco la posicion actual
                    fseek(archi, (pos-1)*sizeof(stCancion), SEEK_SET); //busco la posicion que necesito, -1 asi me posiciona el cursor delante para escribir
                    strcpy(cancion.artista, cModificada.artista);
                    strcpy(cancion.album, cModificada.album);
                    strcpy(cancion.genero, cModificada.genero);
                    strcpy(cancion.comentario, cModificada.comentario);
                    cancion.anio==cModificada.anio;
                    strcpy(cancion.titulo, cModificada.titulo);
                    fwrite(&cancion, sizeof(stCancion), 1, archi); //modifico el registro
                    flag=1; //corta el while
                }

            }
        }
        fclose(archi);
    }
}

//guardo una cancion escuchada por el usuario en el archivo playlist.dat
void guardarCancionEnArchPlayl(int idCancion, int idUsuario)
{
    stPlaylist guardar;
    int registros=0;
    //genero un idPlaylist incremental
    registros=cuentaRegistros("playlist.dat",sizeof(stPlaylist)); //cuento la cantidad de registros que haya en el archivo playlist.dat para poder generar un nuevo idPlaylist

    if(registros==-1) //si no hay ningun registro aun en el archivo
    {
        registros++; //genero un id para el nuevo registro, que siempre sera mayor al ultimo agregado al archivo (se incrementa)
    }

    FILE*archi=fopen("playlist.dat","ab"); //crea el archivo si no existe y coloca el cursor a lo ultimo para escribir
    if(archi!=NULL)
    {
        registros++; //genero un nuevo idPlaylist
        guardar.idPlaylist=registros;
        guardar.idUsuario=idUsuario; //guardo los datos mas representativos
        guardar.idCancion=idCancion;

        fwrite(&guardar,sizeof(stPlaylist),1,archi); //cargo el dato en el archivo playslit
        fclose(archi);
    }
}


//cuenta la cantidad de registros existente en el archivo playlist.dat
int cuentaRegistros(char archivo[], int dim)
{
    int registros=0;
    FILE*archi=fopen("archivo","rb");
    if(archi!=NULL)
    {
        fseek(archi,0,SEEK_END); //me posiciono al final del archivo
        registros=ftell(archi)/dim; //la dimension sera el tipo de dato almacenado en el archivo (sizeof (tipoDeDato).

        fclose(archi);
    }
    return registros;
}


//lee el archivo playslit.dat y cuenta la cantidad de canciones guardadas
int cantidadCancionesID()
{
    int idCanciones=0;
    stPlaylist u;

    FILE*archi=fopen("playlist.dat","rb");
    if(archi!=NULL)
    {
        while(fread(&u,sizeof(stPlaylist),1,archi)>0)
        {
            idCanciones++;
        }

        fclose(archi);
    }
    return idCanciones;
}

//retorna una cancion buscada por el top canciones
stCancion buscarCancionPorId (int id)
{
    int flag=0;
    stCancion aux;
    stCancion cancion;
    FILE*archi=fopen("canciones.dat","rb");
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag==0) //hasta que llegue al final del archivo y flag valga 0
        {
            fread(&cancion,sizeof(stCancion),1,archi);

            if(!feof(archi))
            {
                if(cancion.idCancion==id) //si el id de la cancion leida es igual a la que quiero eliminar
                {
                    aux=cancion;
                    flag=1; //corta el while
                }

            }
        }
        fclose(archi);
    }

    return aux;
}

//almacena los mensajes enviados al administrador por un usuario
void mensajeAdministrador (char mensaje[], char usuario[])
{
    stMensaje x;
    strcpy(x.mensaje, mensaje);
    strcpy(x.nombreUsuario, usuario);

    FILE*archi=fopen("mensajesAdministrador.dat", "ab");
    if(archi!=NULL)
    {
        fwrite(&x, sizeof(stMensaje), 1, archi);
        fclose(archi);
    }
}

//lee los mensajes enviados por los usuarios
void leerMensajeAdministrador ()
{
    stMensaje x;
    int flag=0;
    char opcion;
    FILE*archi=fopen("mensajesAdministrador.dat", "rb");
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag==0)
        {
            fread(&x, sizeof(stMensaje), 1, archi);

            if(feof(archi))
            {
                printf("******************************************\n");
                printf("No hay mensajes sin leer\n");
                printf("Seleccione cualquier tecla para continuar:\n");
                printf("******************************************\n");
                getch();
            }

            if(!feof(archi))
            {
                mostrarMensajeRecibido(x.mensaje, x.nombreUsuario);

                printf("\n***********************************************************************\n");
                printf("Si desea buscar mas mensajes presione cualquier tecla, caso contrario ESC\n");
                printf("*************************************************************************\n");
                opcion=getch();
                if(opcion==27)
                {
                    flag=1;
                }
                system("cls");
            }
        }

        fclose(archi);

        system("cls");
        printf("Si desea eliminar todos los mensajes precione la tecla (S):\n");
        opcion=getch();

        if(opcion==115)
        {
            remove("mensajesAdministrador.dat");
        }

    }

    if(archi==NULL)
    {
        printf("*******************************************\n");
        printf("No ha recibido ningun mensaje aun\n");
        printf("Seleccione cualquier tecla para continuar:\n");
        printf("******************************************\n");
        getch();
    }
}


//lee el archivo canciones.dat y muestra la totalidad de las canciones (activas y eliminadas)
void totalidadCancionesArchivo()
{
    int canciones=0;
    stCancion cancion;

    FILE*archi=fopen("canciones.dat","rb");
    if(archi!=NULL)
    {
        while(fread(&cancion,sizeof(stCancion),1,archi)>0)
        {
            mostrarDatosCancion(cancion); //mostrar
        }
        fclose(archi);
    }

}


///se elimina FISICAMENTE una cancion del archivo canciones.dat / Se crea un archivo auxiliar, se pasan todos los datos que se quieren mantener, y luego se borra y renombra el nuevo archivo
void eliminarCancionArchivoCanciones (stCancion x)
{
    stCancion cancion;
    FILE*archi=fopen("canciones.dat","r+b");
    FILE*archiaux=fopen("cancionesAux.dat", "a+b"); //creo un archivo auxiliar que contendra los archivos que no se quieren eliminar


    if((archi!=NULL) && (archiaux!=NULL))
    {
        while(!feof(archi)) //hasta que llegue al final del archivo
        {
            fread(&cancion,sizeof(stCancion),1,archi);

            if(!feof(archi))
            {
                if(cancion.idCancion!=x.idCancion)  //escribo todas las canciones que no sea la que quiero eliminar al archivo auxiliar
                {
                    fwrite(&cancion, sizeof(stCancion), 1, archiaux);
                }

            }
        }

        fclose(archi);
        fclose(archiaux);
        remove("canciones.dat"); //elimino el archivo que tiene el dato que no quiero
        rename("cancionesAux.dat", "canciones.dat"); //nombro al nuevo archivo con los datos que quiero, como "canciones.dat"

    }
}
