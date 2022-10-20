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


void Importar(List* ListJuegos, TreeMap* Arbol_Precio, TreeMap* Arbol_Valoracion);
void agregar_List(List* ListJuegos, char* nombre, int fecha, int valoracion, int precio);
int sacar_fecha(const char* fecha);
Juego* buscar_List(List *List, char *name);

void AgregarArbol_Precio(TreeMap* Arbol_Precio, Juego* new_game);
void Mostrar_juegos_precio(TreeMap* Arbol_Precio);

void AgregarArbol_Valoracion(TreeMap* Arbol_Valoracion, Juego* new_game);
void Mostrar_juegos_valoracion(TreeMap* Arbol_Valoracion);

int lower_than_int(void* key1, void* key2);
const char *get_csv_field (char * tmp, int k);

//Programa principal

int main(void){


    //Inicializar datos que se usaran
    List* ListJuegos = createList();
    
    TreeMap* Arbol_Precio = createTreeMap(lower_than_int);
    TreeMap* Arbol_Valoracion = createTreeMap(lower_than_int);


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
            Importar(ListJuegos, Arbol_Precio, Arbol_Valoracion);
            /*
        
            Juego* aux = firstList(ListJuegos);
            while(aux != NULL){
                printf("%s,%d,%d,%d\n",aux->nombre,aux->fecha,aux->valoracion,aux->precio);
                aux = nextList(ListJuegos);
            }
            */
            

            printf("se cargaron los datos.\n");
            break;
        case 2:
            system("cls");
            break;
        case 3:
            system("cls");
            Mostrar_juegos_precio(Arbol_Precio);
            break;
        case 4:
            system("cls");
            Mostrar_juegos_valoracion(Arbol_Precio);
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

void Importar(List* ListJuegos, TreeMap* Arbol_Precio, TreeMap* Arbol_Valoracion){


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

        Juego* new_game = (Juego*)malloc(sizeof(Juego));
        strcpy(new_game->nombre,nombre);
        new_game->fecha = fecha;
        new_game->valoracion = valoracion;
        new_game->precio = precio;

        AgregarArbol_Precio(Arbol_Precio, new_game);
        AgregarArbol_Valoracion(Arbol_Precio, new_game);

    }

    
}
    
int sacar_fecha(const char* fecha){

    char extraido[4] = "";
    int inicio = 6;
    int cant = 4;

    strncpy(extraido, fecha + inicio, cant);
    return atoi(extraido);
}











void AgregarArbol_Precio(TreeMap* Arbol_Precio, Juego* new_game){

    Pair* data = searchTreeMap(Arbol_Precio, &new_game->precio);

    if(data != NULL ){
        List* List = data->value;

        pushFront(List,new_game);

        eraseTreeMap(Arbol_Precio,&new_game->precio);
        insertTreeMap(Arbol_Precio,&new_game->precio,List);

    }else{
        List *List = createList();
        pushFront(List,new_game);

        insertTreeMap(Arbol_Precio,&new_game->precio,List);
    }

}

void Mostrar_juegos_precio(TreeMap* Arbol_Precio){

    Pair* data = firstTreeMap(Arbol_Precio);
    List* List_2 = createList();
    int flag;

    if(data == NULL){
        printf("Aun no se ingresan juegos.\n");
    }else{
        
        while(data != NULL){
            List* List = data->value;
            Juego* data_2 = firstList(List);
            while(data_2 != NULL){
                printf("%s,%d,%d,%d\n",data_2->nombre,data_2->fecha,data_2->valoracion,data_2->precio);
                //pushFront(List_2,data_2);
                data_2 = nextList(List);
            }
            data = nextTreeMap(Arbol_Precio);
        }

        /*

        printf("--Presione 1 si quiere de menor a mayor.--\n--Presione 2 si quiere de mayor a menor.--\n\n");
        scanf("%d\n",flag);

        if(flag == 1){
            Juego* dato = firstList(List_2);
            while(dato != NULL){
                printf("%s,%d,%d,%d\n",dato->nombre,dato->fecha,dato->valoracion,dato->precio);
                dato = nextList(List_2);
            }
        }else{
            Juego* dato = lastList(List_2);
            while(dato != NULL){
                printf("%s,%d,%d,%d\n",dato->nombre,dato->fecha,dato->valoracion,dato->precio);
                dato = prevList(List_2);
            }
        } 
        */
    }


}








void AgregarArbol_Valoracion(TreeMap* Arbol_Valoracion, Juego* new_game){

    Pair* data = searchTreeMap(Arbol_Valoracion, &new_game->valoracion);

    if(data != NULL ){
        List* List = data->value;
        pushFront(List,new_game);

        eraseTreeMap(Arbol_Valoracion,&new_game->valoracion);
        insertTreeMap(Arbol_Valoracion,&new_game->valoracion,List);

    }else{
        List *List = createList();
        pushFront(List,new_game);

        insertTreeMap(Arbol_Valoracion,&new_game->valoracion,List);
    }

}

void Mostrar_juegos_valoracion(TreeMap* Arbol_Valoracion){
    Pair* data = firstTreeMap(Arbol_Valoracion);
    List* List_2 = createList();
    int num;

    if(data == NULL){
        printf("Aun no se ingresan juegos.\n");
    }else{
        scanf("Ingrese valoracion y se buscaran juegos mayores al dato ingresado: %d",num);

        while(data != NULL){
            List* List = data->value;
            Juego* data_2 = firstList(List);
            while(data_2 != NULL){
                
                printf("%s,%d,%d,%d\n",data_2->nombre,data_2->fecha,data_2->valoracion,data_2->precio);

                pushFront(List_2,data_2);
                data_2 = nextList(List);
            }
            data = nextTreeMap(Arbol_Valoracion);
        }
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

