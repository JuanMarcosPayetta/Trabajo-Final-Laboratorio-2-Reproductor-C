#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "gestionPlaylist.h"
#include "sistema.h"
#include "gestionArchivos.h"
#include "gestionValidacion.h"

//funcion para el inicio de sesion, tanto para usuario cliente como administradores.
void iniciarSesion (stCelda**ADL, int*validos, nodoArbolCancion*arbol)
{
    char nombreUsuario[30];
    stUsuario usuario;
    int flag=0;
    char opcion;

    system("cls");
    printf("Si desea iniciar sesion presione cualquier tecla, caso contrario ESC:\n");
    opcion=getch();
    if(opcion!=27)
    {
        system("cls");
        printf("**********************************************\n");
        printf("*<>*<>*<>*<>*< INICIO DE SESION >*<>*<>*<>*<>*\n");
        printf("**********************************************\n\n");

        printf("**********************************************\n");
        printf("Ingrese su nombre de usuario:\n");
        printf("**********************************************\n");

        fflush(stdin);
        scanf("%s", &nombreUsuario);
        usuario=buscarNombreInicioSesion(nombreUsuario, &flag); //devuelve el usuario encontrado y un flag
        printf("\n");

        if(flag==0) //no encontro el nombre en el archivo
        {
            system("cls");
            printf("************************************************************************************\n");
            printf("El nombre de usuario ingresado no a sido encontrado\n");
            printf("Si desea intentar nuevamente ingrese cualquier tecla, caso contrario seleccione ESC:\n");
            printf("************************************************************************************\n");
            opcion=getch();

            if(opcion!=27) //desea volver a intentar
            {
                system("cls");
                iniciarSesion (ADL, validos, arbol); //llamada recursiva a la funcion para volver a pedir nombre
            }
            else //vuelve al menu de inicio
            {
                menuInicio (ADL, validos, arbol);
            }
        }
        else if(flag==1 && usuario.eliminado==0) //el usuario no esta eliminado, puede continuar ingresando
        {
            continuaInicioSesion (usuario, ADL, validos, arbol); //si el nombre fue encontrado, llama a la funcion de pedir contraseña
        }
        else
        {
            system("cls");
            printf("******************************************************************\n");
            printf("Usted se encuentra baneado en esta plataforma por el administrador\n");
            printf("Presione cualquier tecla para volver al menu de inicio:\n");
            printf("******************************************************************\n");
            getch();
            menuInicio (ADL, validos, arbol);
        }
    }
    else
    {
        menuInicio(ADL, validos, arbol);
    }

}


//analiza si el nombre fue encontrado o no, y dependiendo del resultado solicitara volver a intentar o pide la contraseña
//si la contraseña es correcta analiza que tipo de usuario es (si es cliente analiza que este aprobado) y lo redirige al menu correspondiente
void continuaInicioSesion (stUsuario usuario, stCelda**ADL, int*validos, nodoArbolCancion*arbol)
{
    system("cls");
    char opcion;
    char contrasenia[20];
    int dimension=20;
    int flag=3;

    ocultarContraseniaInicioSesion(contrasenia, dimension); //pide la contraseña
    flag=validarContrasenia (contrasenia, usuario); // verifica la contraseña ingresada con la guardada en el archivo de usuario y devuelve 1 si es correcta

    if(flag==1)//contraseña correcta
    {
        ingresoContraCorrecta(usuario, ADL, validos, arbol);
    }
    else // contraseña incorrecta
    {
        printf("*******************************************************************************\n");
        printf("La contrasenia ingresada es incorrecta\n");
        printf("Presione cualquier tecla para volver intentarlo, caso contrario seleccione ESC \n");
        printf("********************************************************************************\n");
        opcion=getch();

        if(opcion!=27) //quiere volver a intentarlo
        {
            continuaInicioSesion (usuario, ADL, validos, arbol); //llamada recursiva a la misma funcion, para volver a pedir contraseña
        }
        else //vuelve al menu
        {
            menuInicio(ADL, validos, arbol);
        }
    }
}


/* Luego de que la contraseña ingresada haya sido la correcta:
 Segun el tipo de usuario, en caso de administrador lo lleva a su menu.
 Si es usuario cliente, primero verifica si este fue aprobado o no, en caso de que este aprobado lo lleva a su menu.
 En caso de que no lo esté, le notifica y lo lleva al menu de inicio */
void ingresoContraCorrecta (stUsuario usuario, stCelda**ADL, int*validos, nodoArbolCancion*arbol)
{
    int tipoDeUsuario=2;
    int condicion=2; //se inicializa con 2 para que no tenga basura ni sea 1 o 0 el valor

    tipoDeUsuario=verifTipoUsuario(usuario); // verifica que el tipo de usuario

    if(tipoDeUsuario==1) //es admin
    {
        pasarDeArchivoPlaylistToADL(ADL, validos, arbol, usuario); //carga todos las lista de canciones de los usuarios
        menuPpalAdmin(ADL, validos, arbol, usuario);
    }

    else // es usuario cliente, pero antes de iniciar sesion verifica que este aprobado por el administrador
    {
        pasarArchivoAListaUsuario(ADL, validos, usuario.idUsuario, arbol, usuario); //carga la lista de canciones del usuario
        condicion=verifAprobUsuario(usuario);

        if(condicion==1) //esta aprobado
        {
            menuCliente(ADL, validos, arbol, usuario);
        }
        else //no esta aprobado
        {
            system("cls");
            printf("***********************************ATENCION*************************************\n");
            printf("El usuario aun no fue aprobado por el administrador, vuelva a intentar mas tarde\n");
            printf("Presione ENTER para continuar:\n");
            printf("*********************************************************************************\n");
            getch();
            menuInicio(ADL,validos,arbol);
        }
    }
}


/*Esta funcion pide la contraseña y guarda cada caracter en el arreglo, y por pantantalla
 en su lugar muestra un ***. No permite ingresar espacios,  al precionar enter finaliza.*/
void ocultarContraseniaInicioSesion(char contrasenia[],int dimension)
{
    int caracter=0;
    int i=0;

    printf("\n***********************\n");
    printf("Ingrese su contrasenia\n");
    printf("***********************\n\n");

    while(i<dimension)
    {
        fflush(stdin);
        caracter=getch();// lee cada caracter ingresado

        if(caracter!=13 && caracter!=8) // si no se ingresa enter (13) o retroceso (8) o ESC (27) o espacio (32)
        {
            contrasenia[i]=caracter; // Guardo en el string
            printf("\b* "); // lo reemplaza por un * para ocultar el dato ingresado
            i++;
        }
        if( (caracter==8 && i>0) || i==dimension) // si se ingresa retroceso o llego al maximo de caracteres
        {
            printf("\b\b "); // borra el ultimo ingresado
            i--;
            contrasenia[i]='\0'; // marcamos el fin del arreglo
        }
        if( (caracter==27 && i>0) || i==dimension) // si se ingresa ESC o llego al maximo de caracteres
        {
            printf("\b\b "); // borra el ultimo ingresado
            i--;
            contrasenia[i]='\0'; // marcamos el fin del arreglo
        }
        if( (caracter==32 && i>0) || i==dimension) // si se ingresa espacio o llego al maximo de caracteres
        {
            printf("\b\b "); // borra el ultimo ingresado
            i--;
            contrasenia[i]='\0'; // marcamos el fin del arreglo
        }
        if(caracter==13) // Si presiono ENTER salgo del while
        {
            contrasenia[i]='\0'; // marcamos el fin del arreglo
            i=dimension; // i toma el valor de dimension para salir del while

        }
    }

    if(contrasenia[0]=='\0' || contrasenia[1]=='\0' || contrasenia[2]=='\0' || contrasenia[3]=='\0') //analiza que las posiciones 0, 1,2 y 3 esten ocupadas (\0 indica el final del string, es el campo que no tiene datos)
    {
        system("cls");
        printf("****************************************************************************************\n");
        printf("Cantidad insuficiente de caracteres, intentelo nuevamente con un minimo de 4 caracteres\n");
        printf("****************************************************************************************\n");
        ocultarContraseniaInicioSesion(contrasenia,dimension);

    }
}


// Solicita el ingreso de la nueva clave dos veces y compara si los strings son iguales, si no vuelve a pedir su ingreso

void pedirPassDosVeces(char contrasenia[], int dimension)
{

    int flag=0;
    char contraseniaTest1[20];
    char contraseniaTest2[20];

    while(flag==0)
    {
        system("cls");
        ocultarContraseniaInicioSesion(contraseniaTest1,dimension);
        system("cls");
        printf("*********************************************\n");
        printf("Por favor vuelva a re ingresar su contrasenia\n");
        printf("*********************************************\n");
        ocultarContraseniaInicioSesion(contraseniaTest2,dimension);


        if(strcmp(contraseniaTest1,contraseniaTest2)==0)
        {
            strcpy(contrasenia,contraseniaTest1);
            flag=1;
        }

        if(flag==0)
        {
            system("cls");
            printf("*****************************************************************\n");
            printf("Las contraseñas no son iguales,precione una tecla para reintentar\n");
            printf("*****************************************************************\n");
            getch();
        }
    }
}

///registro de un usuario, ingreso de los datos personales y sus respectivas validaciones.
void registroUsuario (stCelda**ADL, int*validos, nodoArbolCancion*arbol, int usuarioTipo)
{
    stUsuario u;
    char confirmar;
    char opcion;
    system("cls");
    printf("************************************************\n");
    printf("*<>*<>*<>*<>*< CREACION DE CUENTA >*<>*<>*<>*<>*\n");
    printf("************************************************\n\n");

    printf("Si desea crear una cuenta presione cualquier tecla, caso contrario ESC:\n");
    opcion=getch();
    if(opcion!=27)
    {
        u=cargaNombreU(u);

        pedirPassDosVeces(u.pass,20);

        u=cargaAnioNac(u);

        u=cargaGenero(u);

        u=cargaPais(u);

        u=cargaCorreoE(u);

        u.eliminado=0; //el usuario no esta eliminado

        u.aprobado=0;//el usuario no esta aprobado por el admin //el administrador debera verificar todos aquellos usuario que tengan aprobado=0 y aprobarlos

        u.tipoUsuario=usuarioTipo; //si esto es ejecutado desde el administrador tipo de usuario sera 1, sino 0 para usuarios corrientes

        u.idUsuario=usuariosTotales()+1; //recorre el archivo de usuario y retorna la cantidad total. A este valor se le incrementa 1 y sera el ID del nuevo usuario.


        system("cls");
        mostrarDatosUsuario(u); //muestra la totalidad de los datos ingresados antes de confirmar el registro

        printf("\n");
        printf("***************************************************************************************\n");
        printf("Si desea confirmar su registro presione cualquier tecla, caso contrario seleccione ESC:\n");
        printf("***************************************************************************************\n");

        fflush(stdin);
        confirmar=getch();

        if(confirmar!=27) //si acepta confirmar se lo agrega al archivo de usuarios y finaliza su registro
        {
            system("cls");

            agregarUsuarioToArchivo (u); //agrega el nuevo usuario al archio de usuarios.dat

            printf("********************************************************************\n");
            printf(" Usted se ha registrado correctamente, presione ENTER para continuar\n");
            printf("********************************************************************\n");

            getch();
        }

        menuInicio(ADL, validos, arbol); // si no confirma su registro lo regresa al menu de inicio
    }
    else
    {
        menuInicio(ADL, validos, arbol);
    }

}


//cargo el arreglo de listas con los usuarios del archivo usuarios.dat
int cargarADL(stCelda**ADL)
{
    int dimension=usuariosActivos(); //cuenta la cantidad de usuarios activos para determinar la dimension justa para el arreglo
    int validos=0; //al iniciar el sistema los validos del arreglo siempre seran 0 porque es cuando comienzo a cargarlos por primera vez (y al cerrar el sistema se borran)
    stUsuario u;

    (*ADL)=(stCelda*)malloc(dimension*sizeof(stCelda)); // creo el arreglo y le doy dimension justa (la dimension es la cantidad de usuarios activos en el archivo)

    FILE*archi=fopen("usuarios.dat","rb");
    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&u,sizeof(stUsuario),1,archi);
            if(!feof(archi))
            {
                if(u.eliminado==0 && u.aprobado==1 && u.tipoUsuario==0) //si el usuario (no administrador) no esta eliminado y ademas esta aprobado, lo transfiero del archivo de usuarios al arreglo
                {
                    validos=agregarUsuariosActivosToADL(ADL,validos,u); // cargo en el arreglo de lista los usuarios activos, y retorno validos
                }
            }

        }
        fclose(archi);
    }
    return validos; //retorno la cantidad de usuarios que cargue en el arreglo
}


// Agrega un usuario activo al Arreglo Dinamico
int agregarUsuariosActivosToADL(stCelda ** ADL, int validos, stUsuario usuario)
{
    (*ADL)=realloc((*ADL),(validos+1)*sizeof(stCelda)); //sirve para cuando necesito sumar un nuevo usuario al arreglo, redimensiono con los validos +1
    ///podriamos utilizarla para cuando el admin aprueba a un usuario, pueda llamar la funcion y agregarlo al arreglo sin tener que pasar a todos los usuarios desde el archivo
    (*ADL)[validos].usr=usuario; //agrego al usuario en la ultima posicion sin datos
    (*ADL)[validos].listaCanciones=inicLista(); //cada usuario tiene su propia lista de canciones (playlist), y la inicializamos en NULL (porque aun esta vacia)
    validos++; //por cada usuario que agrego al arreglo hago validos +1
    return validos; //retorno la cantidad de usuarios que tiene el arreglo
}



/*
Ordena el arreglo dinamico de menor a mayor comparando una ubicacion con la siguiente
*/
void ordenarPorNombreUsr(stUsuario a[],int validos)
{
    stUsuario u;
    int i,j;
    for(i=0; i<validos; i++)
    {
        for(j=i+1; j<validos; j++) //j inicia en el valor siguiente  a i
        {
            if(strcmpi(a[i].nombreUsuario, a[j].nombreUsuario)>0) //de menor a mayor
            {
                u=a[i];
                a[i]=a[j];
                a[j]=u;
            }
        }
    }
}




//solicita que se ingrese el nombre de usuario al momento del registro
stUsuario cargaNombreU (stUsuario u)
{
    system("cls");
    printf("************************************************\n");
    printf("*<>*<>*<>*<>*< CREACION DE CUENTA >*<>*<>*<>*<>*\n");
    printf("************************************************\n\n");
    int disponible=0;
    printf("**************************************************************\n");
    printf("Ingrese el nombre de usuario con un minimo de tres caracteres:\n");
    printf("**************************************************************\n");
    fflush(stdin);
    gets(u.nombreUsuario);
    cantidadMinima (u.nombreUsuario); //verifica la cantidad minima de caracteres sea 3
    disponible=nombreDisponible (u.nombreUsuario); //verifica que el nombre no se encuentre ocupado (1=ocupado / 0=desocupado)

    while(disponible==1)
    {
        system("cls");
        printf("*****************************************************\n");
        printf("El nombre ya se encuentra en uso, intente nuevamente:\n");
        printf("*****************************************************\n");
        fflush(stdin);
        scanf("%s", u.nombreUsuario);
        disponible=nombreDisponible (u.nombreUsuario); //verifica nuevamente que el nuevo nombre ingresado se encuentre disponible
    }

    return u;
}


//solicita que se ingrese el año de nacimiento al momento del registro
stUsuario cargaAnioNac (stUsuario u)
{
    system("cls");
    printf("************************************************\n");
    printf("*<>*<>*<>*<>*< CREACION DE CUENTA >*<>*<>*<>*<>*\n");
    printf("************************************************\n\n");
    printf("******************************\n");
    printf("Ingrese su anio de nacimiento:\n");
    printf("******************************\n");
    fflush(stdin);
    scanf("%d", &u.anioNacimiento);
    u.anioNacimiento=validarAnioNacimiento(u.anioNacimiento); //verifica que el año de nacimiento se encuentre entre los años permitidos (1930-2020)

    return u;
}


//solicita que se ingrese el genero al momento del registro
stUsuario cargaGenero (stUsuario u)
{
    system("cls");
    printf("************************************************\n");
    printf("*<>*<>*<>*<>*< CREACION DE CUENTA >*<>*<>*<>*<>*\n");
    printf("************************************************\n\n");
    printf("******************\n");
    printf("Ingrese su genero:\n");
    printf("******************\n");
    printf("Masculino = M\n");
    printf("Femenino = F\n");
    fflush(stdin);
    scanf("%c", &u.genero);
    u=generoValido (u); //verifica que el genero ingresado sea m o f
    return u;
}


//solicita que se ingrese el pais de origen al momento del registro
stUsuario cargaPais(stUsuario u)
{
    system("cls");
    printf("************************************************\n");
    printf("*<>*<>*<>*<>*< CREACION DE CUENTA >*<>*<>*<>*<>*\n");
    printf("************************************************\n\n");
    printf("*************************\n");
    printf("Ingrese su pais de origen:\n");
    printf("*************************\n");
    fflush(stdin);
    gets(u.pais);
    cantidadMinima (u.pais); //verifica que el nombre del pais tenga al menos 3 caracteres

    return u;
}


//solicita que se ingrese el correo electronico al momento del registro
stUsuario cargaCorreoE(stUsuario u)
{
    system("cls");
    printf("************************************************\n");
    printf("*<>*<>*<>*<>*< CREACION DE CUENTA >*<>*<>*<>*<>*\n");
    printf("************************************************\n\n");
    printf("*****************************\n");
    printf("Ingrese su correo electronico:\n");
    printf("*****************************\n");
    fflush(stdin);
    gets(u.correoElectronico);
    int v=1;
    while(v==1) //mientras que v sea = a 1, el correo va a ser invalido
    {
        v=validCorreoE(u.correoElectronico); //valida que el correo tenga @ y .

        if (v==1) // si v=1 el correo es incorrecto.
        {
            system("cls");
            printf("************************************************\n");
            printf("*<>*<>*<>*<>*< CREACION DE CUENTA >*<>*<>*<>*<>*\n");
            printf("************************************************\n\n");
            printf("********************************************************************************************\n");
            printf("El correo ingresado es invalido, intente nuevamente. Recuerde utilizar los caracteres . y @\n");
            printf("Ingrese su correo electronico:\n");
            printf("********************************************************************************************\n");
            fflush(stdin);
            gets(u.correoElectronico);
        }
    }
    return u;
}


