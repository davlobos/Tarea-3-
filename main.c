#include "list.c"
#include "treemap.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

//Declaracion structs

typedef struct {
    char nombre[50];
    int fecha;
    int valoracion;
    int precio;
}Juego;


//Declaracion funciones


void Importar(List* ListJuegos, TreeMap* Arbol_Precio);
void agregar_List(List* ListJuegos, char* nombre, int fecha, int valoracion, int precio);
int sacar_fecha(const char* fecha);
Juego* buscar_List(List *List, char *name);
void agregarArbol_Precio(List* ListJuegos, TreeMap* Arbol_Precio);
void crearList_Precio(List* ListJuegos, List* List_precio);
int lower_than_int(void* key1, void* key2);
const char *get_csv_field (char * tmp, int k);

//Programa principal

int main(void){


    //Inicializar datos que se usaran
    List* ListJuegos = createList();
    List* List_precio = createList();

    TreeMap* Arbol_Precio = createTreeMap(lower_than_int);


    //Menu
    int opcion = -1;

    printf("-----------------------------------------------------------\n");
    printf("Bienvenido/a a la aplicacion\n");
    while(opcion != 0){

        printf("\nIngresa el numero de la operacion que deseas realizar\n");
        printf("-----------------------------------------------------------\n");
        printf("1.- Importar Archivos de Juego\n");
        printf("2.- Agregar Juego\n");
        printf("3.- Mostrar Juegos por precio\n");
        printf("4.- Filtrar Juegos por valoracion\n");
        printf("5.- Mostrar Juegos del año\n");
        printf("6.- Buscar Juego\n");
        printf("7.- Exportar datos\n");
        printf("0.- Salir\n");
        printf("-----------------------------------------------------------\n");

        //Pedir opcion
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            system("cls");
            Importar(ListJuegos, Arbol_Precio);
            /*
        
            Juego* aux = firstList(ListJuegos);
            while(aux != NULL){
                printf("%s,%d,%d,%d\n",aux->nombre,aux->fecha,aux->valoracion,aux->precio);
                aux = nextList(ListJuegos);
            }
            */
            

            
            Pair* aux_2 = firstTreeMap(Arbol_Precio);
            while(aux_2 != NULL){
                List* aux_3 = aux_2->value;
                Juego* aux_4 = firstList(aux_3); 
                while(aux_3 != NULL){
                    printf("key = %d     %s,%d,%d,%d\n",aux_2->key,aux_4->nombre,aux_4->fecha,aux_4->valoracion,aux_4->precio);
                    aux_4 = nextList(aux_3);
                }
                aux_2 = nextTreeMap(Arbol_Precio);
            }
            

            printf("se cargaron los datos.\n");
            break;
        case 2:
            system("cls");
            break;
        case 3:
            system("cls");
            break;
        case 4:
            system("cls");
            break;
        case 5:
            system("cls");
            break;
        case 6:
            system("cls");
            break;
        case 7:
            system("cls");
            break;
        case 0:
            break;
        }
    }

    return 0;

    

}

//Funciones

void Importar(List* ListJuegos, TreeMap* Arbol_Precio){


    FILE *archivo;
    char NombreArchivo[50];
    printf("Ingrese el nombre del archivo: \n");
    fflush(stdin);
    scanf("%50[^\n]", NombreArchivo);
    archivo = fopen(NombreArchivo, "r");
    if (NombreArchivo==NULL){
        printf("Archivo inexistente, compruebe nuevamente\n");
    return;
    }    

    char nombre[50];
    int fecha,valoracion,precio;
    char *linea = (char *)malloc(1023 * sizeof(char *));
    fgets(linea, 1024, archivo); //lectura de la linea inutil

    while (fgets(linea, 1024, archivo) != NULL) {

        strcpy(nombre, get_csv_field(linea, 0));
        fecha = sacar_fecha(get_csv_field(linea, 1));
        valoracion = atoi(get_csv_field(linea, 2));
        precio = atoi(get_csv_field(linea, 3));

        agregar_List(ListJuegos,nombre,fecha,valoracion,precio);

    }

    agregarArbol_Precio(ListJuegos, Arbol_Precio);
    
}
    
int sacar_fecha(const char* fecha){

    char extraido[4] = "";
    int inicio = 6;
    int cant = 4;

    strncpy(extraido, fecha + inicio, cant);
    return atoi(extraido);
}

void agregar_List(List* ListJuegos, char* nombre, int fecha, int valoracion, int precio){

    if(buscar_List(ListJuegos,nombre)==NULL){
        Juego* new_game = (Juego*)malloc(sizeof(Juego));

        strcpy(new_game->nombre,nombre);
        new_game->fecha = fecha;
        new_game->valoracion = valoracion;
        new_game->precio = precio;

        pushFront(ListJuegos,new_game);

    }

}

Juego* buscar_List(List *List, char *name){
  Juego* aux = firstList(List);

  while(1){
    if (aux == NULL) return NULL;//si no está retorna nulo
    else if(strcmp(aux->nombre,name) == 0) return aux;//si está retorna el nombre
    aux = nextList(List);
  }
}

void agregarArbol_Precio(List* ListJuegos, TreeMap* Arbol_Precio){

    List* List_precio = createList();
    crearList_Precio(ListJuegos, List_precio);


    List* aux = firstList(List_precio);

    /*
    while(aux!= NULL){
        Juego* aux_3 = (Juego*)malloc(sizeof(Juego));
        aux_3 = firstList(aux);
        while(aux_3 != NULL){
            printf("%s",aux_3->nombre);
            aux_3 = nextList(aux);

        }
        aux = nextList(List_precio);

    }
    */

    Juego* aux_2 = (Juego*)malloc(sizeof(Juego));
    aux_2 = firstList(aux);

    while(aux != NULL){
        insertTreeMap(Arbol_Precio,&aux_2->precio,aux);

        aux = nextList(List_precio);
        aux_2 = firstList(aux);
    }

}

void crearList_Precio(List* ListJuegos, List* List_precio){
    List* List_Aux = ListJuegos;
    List* List_Aux2 = ListJuegos;

    Juego* aux = (Juego*)malloc(sizeof(Juego));
    Juego* aux_2 = (Juego*)malloc(sizeof(Juego));
    
    aux = firstList(List_Aux);
    while(aux != NULL){
        List* List = createList();
        pushFront(List,aux);
        aux_2 = firstList(List_Aux2); 
        while(aux_2 != NULL){
            if(aux->precio == aux_2->precio && strcmp(aux->nombre,aux_2->nombre) != 0){
                pushFront(List,aux_2);
            }
            aux_2 = nextList(List_Aux2);
        }
        pushFront(List_precio,List);
        aux = nextList(List_Aux);

    }
}

int lower_than_int(void* key1, void* key2){
    int k1 = *((int*) (key1));
    int k2 = *((int*) (key2));
    return k1<k2;
}


//Funcion del profe.
const char *get_csv_field (char * tmp, int k) {
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


