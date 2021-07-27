#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "gestionValidacion.h"


//Comprobacion de contraseña de seguridad en caso de querer registrarse como administrador. Si ingresa la contraseña correcta podra continuar con el registro correspondiente.
void contraseniaAdministrador (stCelda**ADL, int*validos, nodoArbolCancion*arbol)
{
    char contrasenia[20];
    int dimension=20;
    char opc;
    int valor=1;

    system("cls");
    printf("*****************************************************\n");
    printf("*<>*<>*<>*<>*< CONTRASEÑA DE SEGURIDAD >*<>*<>*<>*<>*\n");
    printf("*****************************************************\n\n");
    printf("Ingrese la contrasenia de seguridad para registrarse como administrador:\n");
    ocultarContraseniaInicioSesion(contrasenia,dimension);


    if(strcmp(contrasenia, contraseniaAdmin)!=0) //comparacion de la contraseña ingresada (contraseniaAdmin es global)
    {
        system("cls");
        printf("*****************************************************************************************\n");
        printf("Contrasenia invalida\n");
        printf("Si desea intentar nuevamente seleccione cualquier tecla, caso contrario seleccione ESC:\n");
        printf("*****************************************************************************************\n");
        opc=getch();

        if(opc==27)
        {
            menuInicio(ADL, validos,arbol); //si no quiere continuar intentando, lo redirige al menu de inicio
        }
        else
        {
            contraseniaAdministrador (ADL, validos, arbol); //llamada recursiva en caso de querer volver a ingresar la contraseña
        }
    }
    else //la contraseña ingresada es correcta
    {
        system("cls");
        registroUsuario (ADL, validos, arbol, valor); //continua el registro
    }
}



//funcion que analiza si se ingresaron la cantidad minina de caracteres en una palabra. En este caso el minimo es de 3 caracteres.
void cantidadMinima (char palabra[])
{
    while(palabra[0]=='\0' || palabra[1]=='\0' || palabra[2]=='\0') //analiza que las posiciones 0, 1 y 2 esten ocupadas (\0 indica el final del string, es el campo que no tiene datos)
    {
        system("cls");
        printf("****************************************************************************************\n");
        printf("Cantidad insuficiente de caracteres, intentelo nuevamente con un minimo de 3 caracteres:\n");
        printf("****************************************************************************************\n");
        gets(palabra);
        system("cls");
    }
}


//funcion que indica si el nombre seleccionado esta dispobiel o no, retornando 1 en caso de no estar disponible, y 0 en caso contrario.
int nombreDisponible (char nombre[])
{
    int disponible=0; //flag
    stUsuario usuario;

    FILE*archi=fopen("usuarios.dat","rb"); //abro el archivo de usuarios en modo lectura
    if(archi==NULL)
    {
        archi=fopen("usuarios.dat", "ab"); //si no existe lo crea

    }
    if(archi!=NULL) //si ya esta creado
    {
        while(fread(&usuario,sizeof(stUsuario),1,archi)>0 && disponible==0) //lee mientras no haya encontrado el nombre
        {
            if(strcmpi(usuario.nombreUsuario,nombre)==0) //comparo el nombre ingresado con los que ya se encuentran registrados y almacenados en el archivo de usuarios
            {
                disponible=1; //si el nombre ya esta ocupado, retorna 1
            }
        }
        fclose(archi);
    }
    return disponible;
}


//verifica que el año de nacimiento ingresado se encuentre entre los parametros correctos (1930-2020)
int validarAnioNacimiento(int anio)
{
    while((anio<1930)||(anio>2020))
    {
        system("cls");
        printf("***************************************\n");
        printf("Ingrese una fecha de nacimiento valida:\n");
        printf("***************************************\n");
        fflush(stdin);
        scanf("%d", &anio);
    }
    return anio;
}

//verificar que el año de la cancion ingresado sea valido
stCancion validarAnioCancion (stCancion c)
{
    while((c.anio<1200)||(c.anio>2020))
    {
        system("cls");
        printf("***************************************\n");
        printf("Ingrese una fecha valida:\n");
        printf("***************************************\n");
        fflush(stdin);
        scanf("%d", &c.anio);
    }
    return c;
}

//verifica que el genero ingresado sea m o f
stUsuario generoValido (stUsuario u)
{
    while(u.genero!='M' && u.genero!='F' && u.genero!='m' &&  u.genero!='f')
    {
        system("cls");
        printf("************************************************************************\n");
        printf("El genero ingresado es incorrecto, por favor intente nuevamente (m o f):\n");
        printf("************************************************************************\n");
        scanf("%c",&u.genero);
    }
    return u;
}



//cuenta la cantidad de usuarios en el archivo de usuarios (utilizado para darle una ID diferente a cada usuario)3
int usuariosTotales ()
{
    FILE*archi=fopen("usuarios.dat", "rb");

    stUsuario u;
    int i=0;
    if(archi!=NULL)
    {
        while(fread(&u, sizeof(stUsuario), 1, archi)>0)
        {
            i++;
        }
        fclose(archi);
    }
    else
    {
        printf("No pudo abrirse el archivo\n");
    }
    return i;
}

//verifica que el correo ingresado cumpla con determinados parametros minimos.
int validCorreoE(char mail[])
{
    int flag=0;
    mail = strchr(mail, '@'); //para ser valido debe poseer este caracter
    if (mail==NULL)
    {
        flag=1; ///el mail ingresado es incorrecto
    }
    else if (strchr( mail, '.' ) == NULL) //para ser valido debe poseer este caracter
    {
        flag=1;
    }
    return flag; //retorno 1 si es invalido y 0 si no lo es
}

//verifica que el Tipo de usuario, ya sea cliente(0) u administrador(1)
int verifTipoUsuario (stUsuario u)
{
    int flag=3;

    if(u.tipoUsuario==0)
    {
        flag=0; // si es cliente devuelve 0, si administrador 1
    }
    else
    {
        flag=1;
    }

    return flag;
}

// verifica si el usuario cliente esta aprobado o no
int verifAprobUsuario(stUsuario u)
{
    int flag=3;

    if(u.aprobado==0)
    {
        flag=0; // no esta aprobado, si esta aprobado devuelve 1
    }
    else
    {
        flag=1;
    }
    return flag;
}



//compara la contraseña ingresada con la del archivo de usuarios, devolviendo 1 si es correcta, de lo contrario 0-
int validarContrasenia (char contrasenia[], stUsuario u)
{
    int flag=0;
    if(strcmp(contrasenia,u.pass)==0) // si la contraseña coincide flag=1
    {
        flag=1;
    }
    return flag;
}

//funcion que valida que la el nombre de la cancion que desea ingresarse no exista ya en el archivo de canciones.dat
int validarCancionRepetida (char nombreCancion[])
{
    stCancion aux;
    int flag=0;

    FILE*archi=fopen("canciones.dat", "rb");
    if(archi==NULL)
    {
        FILE*archi=fopen("canciones.dat", "a+b"); //como el archivo por primera vez no existe, lo crea
    }

    if(archi!=NULL)
    {
        while(fread(&aux, sizeof(stCancion), 1, archi)>0)
        {
            if(strcmpi(aux.titulo, nombreCancion)==0) //si el nombre ingresado ya existe en el archivo
            {
                flag=1;
            }
        }
        fclose(archi);
    }
    return flag;
}

//busca si existe la cancion en el archivo y NO esta eliminada
int validarIdCancion(int id)
{
    stCancion aux;
    int flag=0;
    FILE*archi=fopen("canciones.dat", "rb");
    if(archi!=NULL)
    {
        while(flag==0 && (!feof(archi)))
        {
            fread(&aux, sizeof(stCancion), 1, archi);

            if(!feof(archi))
            {
                if(aux.idCancion==id && aux.eliminado==0)
                {
                    flag=1;
                }
            }
        }
        fclose(archi);
    }
    return flag;
}


//busca si la cancion esta realmente eliminada
int validarCancionEliminada(int id)
{
    stCancion aux;
    int flag=0;
    FILE*archi=fopen("canciones.dat", "rb");
    if(archi!=NULL)
    {
        while(fread(&aux, sizeof(stCancion), 1, archi)>0 && flag==0)
        {
            if(aux.idCancion==id && aux.eliminado==1) //si esta eliminada, es correcto
            {
                flag=1;
            }
        }
        fclose(archi);
    }
    return flag;
}

//busca en el arreglo alguna cancion con el mismo genero al solicitado
void buscarCancionGenero (stCancion**ADL, int validos, char genero[])
{
    int i=0;
    while(i<validos)
    {
        if(strcmpi((*ADL)[i].genero, genero)==0) //si el genero solicitado es igual al genero de la cancion
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


//verifica si existe alguna cancion con el genero solicitado
int verificarCancionesTitulo(char titulo[])
{
    stCancion aux;
    int flag=0;
    FILE*archi=fopen("canciones.dat", "rb");
    if(archi!=NULL)
    {
        while((fread(&aux, sizeof(stCancion), 1, archi)>0) && flag==0)
        {
            if(strcmpi(aux.titulo, titulo)==0)//si los generos son iguales
            {
                flag=1; //si encuentra al menos 1 cancion con el titulo solicitado
            }
        }

        fclose(archi);
    }
    return flag;
}

//verifica si existe alguna cancion con el genero solicitado
int verificarCancionesGenero(char genero[])
{
    stCancion aux;
    int flag=0;
    FILE*archi=fopen("canciones.dat", "rb");
    if(archi!=NULL)
    {
        while((fread(&aux, sizeof(stCancion), 1, archi)>0) && flag==0)
        {
            if(strcmpi(aux.genero, genero)==0)//si los generos son iguales
            {
                flag=1; //si encuentra al menos 1 cancion con el genero solicitado
            }
        }

        fclose(archi);
    }
    return flag;
}

//verifica si existe el id solicitado en el archivo de canciones.dat (puede estar eliminada)
int verificarExisteId(int id)
{
    stCancion aux;
    int flag=0;
    FILE*archi=fopen("canciones.dat", "rb");
    if(archi!=NULL)
    {
        while((fread(&aux, sizeof(stCancion), 1, archi)>0) && flag==0)
        {
            if(aux.idCancion==id)//si los ID son iguales
            {
                flag=1; //si encuentra una cancion con el ID solicitado
            }
        }

        fclose(archi);
    }
    return flag;
}


//verifica si hay canciones eliminadas o no
int verificarCancionesEliminadas()
{
    stCancion aux;
    int flag=0;
    FILE*archi=fopen("canciones.dat", "rb");
    if(archi!=NULL)
    {
        while((fread(&aux, sizeof(stCancion), 1, archi)>0) && flag==0)
        {
            if(aux.eliminado==1)
            {
                flag=1; //si encuentra al menos 1 canciones eliminada retorna 1
            }
        }

        fclose(archi);
    }
    return flag;
}

//verifica si el archivo de canciones tiene al menos 1 cancion (aunque este eliminada logicamente)
int verificarExisteAlgunaCancion()
{
    stCancion aux;
    int flag=0;
    FILE*archi=fopen("canciones.dat", "rb");
    if(archi!=NULL)
    {
        while((fread(&aux, sizeof(stCancion), 1, archi)>0) && flag==0)
        {
            flag=1; //si lee al menos 1 cancion, flag=1
        }

        fclose(archi);
    }
    return flag;
}

//verifica que haya al menos 1 usuario cliente eliminado en el archivo de usuarios.dat
 int existeUsuariosEliminados()
{
    stUsuario u;
    int flag=0;

    FILE*archi=fopen("usuarios.dat","rb");
    if(archi!=NULL)
    {
        while(fread(&u,sizeof(stUsuario),1,archi)>0 && flag==0)
        {
            if(u.eliminado==1 && u.tipoUsuario==0) //si el usuario cliente esta eliminado lo muestra
            {
                flag=1;
            }
        }

        fclose(archi);
    }
    return flag;
}

