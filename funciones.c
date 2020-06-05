
typedef struct Pelicula Pelicula;
typedef struct lista_con_peliculas lista_con_peliculas;


struct Pelicula{
    list * generos;//12
    //char lista_corespondiente[100]; //char ** listas_correspondientes;
    void ** listas_correspondientes;
    char director[1000];//15
    char nombre_pelicula[100];//6
    char id[50];//2
    double IMDb_rating;//9
    char IMDb_rating_string[5];//9
    int year;//11
    bool favorito;
    int numero_de_enlaces;
};

struct lista_con_peliculas{

    SortedMap* mapa_ordenado_de_peliculas;
    list * peliculas;
    int puntaje;
    char nombre[100];
};

const char *get_csv_field (char * tmp, int k) {
    //se crea una copia del string tmp

    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

double deStringAFlotante(const char * palabra){
    double numero = 0;
    int suma = 0;
    int potencia = 10;
    for(int i = 0; i < strlen(palabra);i++){
        if(isdigit(palabra[i]) == 1){
            suma += potencia * (palabra[i] - 48 );
            potencia/=10;

        }
    }
    numero =suma*0.1; // suma/10 + 0.1*(suma%10);
    return numero;
    printf("%.1f\n", numero);
}

Pelicula* crear_pelicula(char * linea,char * tipo_lista){

    Pelicula * pelicula = (Pelicula*) malloc (sizeof(Pelicula));
    //pelicula -> generos = list_create_empty();

    pelicula ->favorito = false;

    pelicula ->listas_correspondientes = (void**) malloc (sizeof(void*));
    pelicula ->listas_correspondientes[0] = tipo_lista;

    pelicula->numero_de_enlaces = 1;
    strcpy(pelicula->id,get_csv_field(linea,1));
    strcpy(pelicula->nombre_pelicula , get_csv_field(linea,5));
    pelicula->IMDb_rating = deStringAFlotante(get_csv_field(linea,8));
    pelicula->year = atoi(get_csv_field(linea,10));
    strcpy(pelicula->director,get_csv_field(linea,14));
    strcpy(pelicula ->IMDb_rating_string,get_csv_field(linea,8));

    return pelicula;

}

lista_con_peliculas* crearListaDePeliculas(const char* nombre){
    lista_con_peliculas * lista_de_peliculas = (lista_con_peliculas *) malloc (sizeof(lista_con_peliculas));
    lista_de_peliculas -> peliculas = list_create_empty();
    strcpy(lista_de_peliculas->nombre, nombre);
    lista_de_peliculas -> puntaje = 0;
//    strcpy(lista_de_peliculas->nombre,'\0');
    return lista_de_peliculas;

}
/*
void imprimirDatos (lista_con_peliculas * lista){
    printf("\n-----------------------------------------------------------------------\n");
    for(Pelicula* actual = list_first(lista->peliculas); actual != NULL; actual = list_next(lista->peliculas)){
        printf("%s\n%.1lf\n%d\n", actual -> nombre_pelicula , actual->IMDb_rating , actual->year);
    }
}
*/
void ingresoDeArchivo(char* tipo,Map * mapa_todas_las_peliculas,SortedMap * mapa_con_listas, int cmp_to_a_float(const void* , const void*)){//, int cmp_double(const void*, const void *)){
    char linea[1000];
    char direccion[1000] = "Generos\\";

    if(searchSortedMap(mapa_con_listas,tipo) != NULL){
        printf("Esta Lista de peliculas ya ha sido agregada\n");
        return;
    }

    strcat(direccion,tipo);
//    printf("%s %d\n%s %d\n",(const char *)direccion,strlen(direccion),"Generos\\BestAction.csv",strlen("Generos\\BestAction.csv"));

    FILE * fp = fopen((const char *) direccion,"r");//|"Generos\\BestAction.csv"
    int bandera = 0;

    if(fp == NULL){

        printf("el archivo no existe\n");
        fclose(fp);
        return;

    }
    else{

        lista_con_peliculas * lista = NULL;
        lista = crearListaDePeliculas(tipo);
        Pelicula* pelicula = NULL;
        Pelicula* verificador = NULL;

        SortedMap* mapa_de_peliculas_ordenado= createSortedMap(cmp_to_a_float);

        while(fgets(linea,500,fp) ){

            if(bandera == 0){
                bandera = 1;
                continue;
            }
            else
            {
                verificador = (Pelicula*) searchMap(mapa_todas_las_peliculas , get_csv_field(linea,1));

                if(verificador == NULL){
                    pelicula = crear_pelicula(linea, tipo);
                    list_push_back(lista-> peliculas, pelicula);
                    insertSortedMap(mapa_de_peliculas_ordenado,pelicula->IMDb_rating_string,pelicula);
                    insertMap(mapa_todas_las_peliculas,pelicula->id,pelicula);

                }
                else
                {
                    //printf("Dentro\n");
                    verificador->numero_de_enlaces++;
                    list_push_back(lista-> peliculas, verificador);
                    verificador->listas_correspondientes = (void**) realloc (verificador->listas_correspondientes, verificador->numero_de_enlaces*sizeof(void*));
                    verificador->listas_correspondientes[verificador->numero_de_enlaces-1] = tipo;
                    insertSortedMap(mapa_de_peliculas_ordenado,verificador->IMDb_rating_string,verificador);


                }
            }

        }
        fclose(fp);
        lista ->mapa_ordenado_de_peliculas = mapa_de_peliculas_ordenado;
        insertSortedMap(mapa_con_listas,lista->nombre,lista);

        //imprimirDatos(lista);

    }

}

void recomendarPelicula(SortedMap* mapa_con_listas){//5
    lista_con_peliculas* mayor = firstSortedMap(mapa_con_listas);
    lista_con_peliculas* actual = firstSortedMap(mapa_con_listas);

    for(;actual != NULL; actual = nextSortedMap(mapa_con_listas)){
        if(mayor->puntaje < actual->puntaje){
            mayor = actual;
        }
    }
    int cont = 0;
    Pelicula* pelicula_actual = firstSortedMap(mayor->mapa_ordenado_de_peliculas);
    for(;pelicula_actual != NULL && cont <= 9 ; pelicula_actual = nextSortedMap(mayor->mapa_ordenado_de_peliculas)){
        if(pelicula_actual->favorito == false){
            printf("%.1lf %s\n",pelicula_actual->IMDb_rating,pelicula_actual->nombre_pelicula);
            cont++;
        }
    }

}

void marcarComoFavorita(const char* id, Map* mapa_con_todas_las_pelis,SortedMap* mapa_con_listas){//4
    Pelicula* pelicula = searchMap(mapa_con_todas_las_pelis,id);
    lista_con_peliculas* lista = NULL;
    if(pelicula == NULL){
        printf("La pelicula No existe\n");
    }
    else
    {
        if(pelicula ->favorito == true){
            printf("Esta pelicula ya ha sido marcada\n");
            return;
        }

        pelicula ->favorito = true;
        void** listas_correspondientes = pelicula ->listas_correspondientes;
        for(int i=0; i< pelicula->numero_de_enlaces ; i++){
            lista = searchSortedMap(mapa_con_listas,(const char*)listas_correspondientes[i]);
            if(lista == NULL){
                printf("NO\n");
            }
            else
            {
                lista ->puntaje++;
            }

        }

    }

}

void mostrarInfoPelicula(const char* id,Map* mapa_de_peliculas){//3
    Pelicula* peli = searchMap(mapa_de_peliculas,id);
    if(peli != NULL){
        printf("Informacion de la pelicula:\n\nPelicula: %s\nAno: %d\nID: %s\nDirector\\es: %s\nIMDb rating: %.1lf\n",peli->nombre_pelicula,peli->year,peli->id,peli->director,peli->IMDb_rating);
    }
    else
    {
        printf("La pelicula no existe\n");
    }

}

void mostrarListasDePeliculas(SortedMap* mapa_con_listas){//1
    lista_con_peliculas* lista_actual =firstSortedMap(mapa_con_listas);

    if(lista_actual == NULL){
        return;
    }
    else
    {
        for(;lista_actual != NULL; lista_actual = nextSortedMap(mapa_con_listas)){
            printf("puntaje:%d %s\n",lista_actual->puntaje,lista_actual->nombre);
        }
    }

}

void mostarUnaListaDePeliculas(SortedMap* mapa_con_listas, const char* nombre_lista){//2
    lista_con_peliculas* lista = searchSortedMap(mapa_con_listas,nombre_lista);
    if(lista == NULL){
        printf("La lista NO existe\n");
        return;
    }
    Pelicula* pelicula_actual = list_first(lista->peliculas);

    if(pelicula_actual == NULL){
        printf("Falla2\n");
        return;
    }

    int cont = 0;

    for(;pelicula_actual!= NULL;pelicula_actual=list_next(lista->peliculas)){
        printf("%d Pelicula: %s\nAno: %d\nID: %s\nIMDb rating: %.1lf\n",cont,pelicula_actual->nombre_pelicula,pelicula_actual->year,pelicula_actual->id,pelicula_actual->IMDb_rating);
        cont++;
    }

}

void menu(SortedMap* mapa_con_listas , Map* mapa_con_todas_las_peliculas){

    int opcion = 5;
    printf("Si deseas ver las listas cargadas seleciona 1\n");
    printf("Si deseas ver una lista seleciona 2\n");
    printf("Si deseas ver la informacion de una pelicula selecciona 3\n");
    printf("Si deseas marcar una pelicula como favorita selecciona 4\n");
    printf("Si deseas ver la lista de recomendaciones selecciona 5\n");

    char nombre[20];

    while(opcion != 0){

        scanf("%d", &opcion);

        if(opcion == 1){
            mostrarListasDePeliculas(mapa_con_listas);
        }

        if(opcion == 2){
            printf("Ingresa el nombre de la lista\n");
            scanf("%s",nombre);
            mostarUnaListaDePeliculas(mapa_con_listas,nombre);
        }

        if(opcion == 3){
            printf("Ingresa el ID de la pelicula\n");
            scanf("%s",nombre);
            mostrarInfoPelicula(nombre,mapa_con_todas_las_peliculas);

        }

        if(opcion == 4){
            printf("Ingresa el ID de la pelicula\n");
            scanf("%s",nombre);
            marcarComoFavorita(nombre,mapa_con_todas_las_peliculas,mapa_con_listas);
        }

        if(opcion == 5){
            recomendarPelicula(mapa_con_listas);
        }

    }


}
