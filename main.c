#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "list.h"
#include "Map.h"
#include "SortedMap.h"
#include "funciones.c"



int cmp_to_a_float(const void* key1, const void * key2){
    double Key1 = deStringAFlotante((const char*)key1);
    double Key2 = deStringAFlotante((const char*)key2);
    if(Key1 == Key2){
        return 0;
    }
    else
    {
        if(Key1 > Key2){
            return -1;
        }
        else{
            return 1;

        }
    }

}

int cmp_str_map(const void * key1, const void * key2){
    const char * Key1 = key1;
    const char * Key2 = key2;
    if (strcmp(Key1,Key2) == 0) return 1;

    else return 0;

}

int cmp_str_smap(const void * key1, const void * key2){
    const char * Key1 = key1;
    const char * Key2 = key2;
    return strcmp(Key1,Key2);

}

int main()
{

    SortedMap* mapa_con_listas = NULL;
    mapa_con_listas = createSortedMap(cmp_str_smap);

    Map* mapa_con_todas_las_peliculas = NULL;
    mapa_con_todas_las_peliculas = createMap(cmp_str_map);

    int numero=5;

    while(numero != 0){
        char * tipo = (char*) malloc(sizeof(char)*100);
        printf("Ingrese el tipo de la pelicula\n");
        scanf("%100[^\n]s", tipo);
        ingresoDeArchivo(tipo,mapa_con_todas_las_peliculas,mapa_con_listas,cmp_to_a_float);//, cmp_double);
        printf("Si desea Seguir con la aplicacion, ingrese un numero distinto a cero\n");
        scanf("%d", &numero);
        getchar();
//        printf("cantidad: %ld\n",*(((lista_con_peliculas*)(firstSortedMap(mapa_con_listas)))->peliculas->count));
    }

    menu(mapa_con_listas,mapa_con_todas_las_peliculas);

    printf("termino\n");

    return 0;
}
