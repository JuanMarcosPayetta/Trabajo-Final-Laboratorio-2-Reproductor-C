#ifndef GESTIONCANCIONES_H_INCLUDED
#define GESTIONCANCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>


//-----------------------------------------------------ESTRUCTURA--------------------------------------------------------

//Datos cancion
typedef struct
{
    int idCancion;
    char titulo[30];
    char artista[20];
    int duracion;
    char album[20];
    int anio;
    char genero[20];
    char comentario[100];
    int eliminado; /// indica 1 o 0 si la canción fue eliminada
} stCancion;



//-----------------------------------------------------PROTOTIPADOS-----------------------------------------------------
stCancion IngresarDatosCancion();
stCancion modificarTitulo (stCancion c);
stCancion modificarArtista (stCancion c);
stCancion modificarGenero (stCancion c);
stCancion modificarAnio (stCancion c);
stCancion modificarAlbum (stCancion c);
stCancion modificarComentario (stCancion c);



#endif // GESTIONCANCIONES_H_INCLUDED
