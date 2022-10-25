#include "list.c"
#include "treemap.c"
#include "hashmap.c"

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

void Importar(TreeMap* Arbol_Precio, TreeMap* Arbol_Valoracion, TreeMap* Arbol_Fecha, HashMap* Mapa_Juegos);
int sacar_fecha(const char* fecha);

void Agregar_Juego(TreeMap* Arbol_Precio, TreeMap* Arbol_Valoracion, TreeMap* Arbol_Fecha, HashMap* Mapa_Juegos);

void AgregarArbol_Precio(TreeMap* Arbol_Precio, Juego* new_game);
void Mostrar_juegos_precio(TreeMap* Arbol_Precio);

void AgregarArbol_Valoracion(TreeMap* Arbol_Valoracion, Juego* new_game);
void Mostrar_juegos_valoracion(TreeMap* Arbol_Valoracion);

void AgregarArbol_fecha(TreeMap* Arbol_Fecha, Juego* new_game);
void Mostrar_juegos_fecha(TreeMap* Arbol_Fecha);

void Buscar_Juego(TreeMap* Arbol_Precio, TreeMap* Arbol_Valoracion, TreeMap* Arbol_Fecha, HashMap* Mapa_Juegos);

void exportar(HashMap* Mapa_Juegos);

int lower_than_int(void* key1, void* key2);
const char *get_csv_field (char * tmp, int k);

//Programa principal

int main(void){

    //Inicializar datos que se usaran

    TreeMap* Arbol_Precio = createTreeMap(lower_than_int);
    TreeMap* Arbol_Valoracion = createTreeMap(lower_than_int);
    TreeMap* Arbol_Fecha = createTreeMap(lower_than_int);
    HashMap* Mapa_Juegos = createMap(100);

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
        printf("5.- Mostrar Juego del año\n");
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
            Importar(Arbol_Precio, Arbol_Valoracion, Arbol_Fecha, Mapa_Juegos);
            printf("\nSe cargaron los datos con exito!.\n");
            break;
        case 2:
            system("cls");
            Agregar_Juego(Arbol_Precio,Arbol_Valoracion,Arbol_Fecha,Mapa_Juegos);
            break;
        case 3:
            system("cls");
            Mostrar_juegos_precio(Arbol_Precio);
            break;
        case 4:
            system("cls");
            Mostrar_juegos_valoracion(Arbol_Valoracion);
            break;
        case 5:
            system("cls");
            Mostrar_juegos_fecha(Arbol_Fecha);
            break;
        case 6:
            system("cls");
            Buscar_Juego(Arbol_Precio,Arbol_Valoracion,Arbol_Fecha,Mapa_Juegos);
            break;
        case 7:
            system("cls");
            exportar(Mapa_Juegos);
            break;
        case 0:
            break;
        }

    }

    return 0;
}

//Funciones

void Importar(TreeMap* Arbol_Precio, TreeMap* Arbol_Valoracion,TreeMap* Arbol_Fecha, HashMap* Mapa_Juegos){

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

        Juego* new_game = (Juego*)malloc(sizeof(Juego));
        strcpy(new_game->nombre,nombre);
        new_game->fecha = fecha;
        new_game->valoracion = valoracion;
        new_game->precio = precio;

        insertMap(Mapa_Juegos,new_game->nombre,new_game);
        AgregarArbol_Precio(Arbol_Precio, new_game);
        AgregarArbol_Valoracion(Arbol_Valoracion, new_game);
        AgregarArbol_fecha(Arbol_Fecha,new_game);

    }
    
}
    
int sacar_fecha(const char* fecha){

    char extraido[4] = "";
    int inicio = 6;
    int cant = 4;

    strncpy(extraido, fecha + inicio, cant);
    return atoi(extraido);

}



void Agregar_Juego(TreeMap* Arbol_Precio, TreeMap* Arbol_Valoracion, TreeMap* Arbol_Fecha, HashMap* Mapa_Juegos){

    char nombre[50],fecha_aux[50];
    int fecha,valoracion,precio;

    printf("\n Nombre del juego: \n");
    fflush(stdin);
    scanf("%50[^\n]",&nombre);

    printf("\n Fecha de salida (DD/MM/YYYY): \n");
    fflush(stdin);
    scanf("%s",&fecha_aux);
    fecha = sacar_fecha(fecha_aux);

    printf("\n Valoracion: \n");
    fflush(stdin);
    scanf("%d",&valoracion);

    printf("\n Precio: \n");
    fflush(stdin);
    scanf("%d",&precio);

    Juego* new_game = (Juego*)malloc(sizeof(Juego));
    strcpy(new_game->nombre,nombre);
    new_game->fecha = fecha;
    new_game->valoracion = valoracion;
    new_game->precio = precio;

    insertMap(Mapa_Juegos, new_game->nombre,new_game);
    AgregarArbol_Precio(Arbol_Precio, new_game);
    AgregarArbol_Valoracion(Arbol_Valoracion, new_game);
    AgregarArbol_fecha(Arbol_Fecha,new_game);

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
        printf("Aun no se ingresan juegos, intente de nuevo.\n");
    }else{
        
        while(data != NULL){
            List* List = data->value;
            Juego* data_2 = firstList(List);
            while(data_2 != NULL){
                pushFront(List_2,data_2);
                data_2 = nextList(List);
            }
            data = nextTreeMap(Arbol_Precio);
        }

        fflush(stdin);
        printf("--Presione 1 si quiere de mayor a menor.--\n--Presione 2 si quiere de menor a mayor.--\n\n");
        scanf("%d",&flag);
        printf("\nNombre,año de salida,valoracion,precio:\n\n");
        if(flag == 1){
            Juego* dato = firstList(List_2);
            while(dato != NULL){
                printf("%s,%d,%d,%d\n",dato->nombre,dato->fecha,dato->valoracion,dato->precio);
                dato = nextList(List_2);
            }
        }else if(flag == 2){
            Juego* dato = lastList(List_2);
            while(dato != NULL){
                printf("%s,%d,%d,%d\n",dato->nombre,dato->fecha,dato->valoracion,dato->precio);
                dato = prevList(List_2);
            }
        }else{
            printf("Numero ingresado no es ni 1 ni 2, intente de nuevo\n");
        } 
        
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

    int num;
    fflush(stdin);
    printf("Ingrese dato de valoracion deseada y se le imprimiran mayores a ese:\n");
    scanf("%d", &num);
    Pair* data = firstTreeMap(Arbol_Valoracion);

    if(data == NULL){
        printf("Aun no se ingresan juegos.\n");
    }else{

        Pair* data = upperBound(Arbol_Valoracion,&num);
        printf("\nNombre,año de salida,valoracion,precio:\n\n");
        while(data != NULL){
            List* List = data->value;
            Juego* data_2 = firstList(List);
            while(data_2 != NULL){
                
                printf("%s,%d,%d,%d\n",data_2->nombre,data_2->fecha,data_2->valoracion,data_2->precio);

                data_2 = nextList(List);
            }
            data = nextTreeMap(Arbol_Valoracion);
        }

    }

}



void AgregarArbol_fecha(TreeMap* Arbol_Fecha, Juego* new_game){

    Pair* data = searchTreeMap(Arbol_Fecha, &new_game->fecha);

    if(data != NULL ){
        List* List = data->value;
        pushFront(List,new_game);

        eraseTreeMap(Arbol_Fecha,&new_game->fecha);
        insertTreeMap(Arbol_Fecha,&new_game->fecha,List);

    }else{
        List *List = createList();
        pushFront(List,new_game);

        insertTreeMap(Arbol_Fecha,&new_game->fecha,List);
    }
  

}

void Mostrar_juegos_fecha(TreeMap* Arbol_Fecha){

    Pair* data = firstTreeMap(Arbol_Fecha);

    if(data == NULL){
        printf("Aun no se ingresan juegos.\n");

    }else{
        int num;
        fflush(stdin);
        printf("Ingrese año en que desea saber el juego del año:\n");
        scanf("%d", &num);

        Pair* data = searchTreeMap(Arbol_Fecha,&num);

        if (data == NULL){
            printf("NO existe ese año dentro de la lista de juegos, por favor intente de nuevo.\n");
        }else{
            
            List* List = data->value;
            Juego* data_2 = firstList(List);
            Juego* aux = data_2;
            while(data_2 != NULL){
                data_2 =nextList(List);
                if(data_2 == NULL) break;
                else if(aux->valoracion < data_2->valoracion) aux = data_2;
            }
            
            printf("El juego del año %d es:\n\n",num);
            printf("\nNombre,año de salida,valoracion,precio:\n\n");
            printf("%s,%d,%d,%d\n",aux->nombre,aux->fecha,aux->valoracion,aux->precio);

        }

    }

}



void Buscar_Juego(TreeMap* Arbol_Precio, TreeMap* Arbol_Valoracion, TreeMap* Arbol_Fecha, HashMap* Mapa_Juegos){

    Pair_2* data = firstMap(Mapa_Juegos);

    if(data == NULL){
        printf("Aun no se ingresan juegos, intente de nuevo.\n");
    }else{
        char name[50];
        printf("Ingrese nombre del juego que desea buscar:\n");
        fflush(stdin);
        scanf("%50[^\n]",&name);

        Pair_2* dato = searchMap(Mapa_Juegos,name);

        if(dato == NULL){
            printf("\nNO existe ese juego en la lista, intente de nuevo.\n");
        }else{
            int num;
            printf("\n Juego encontrado!!\n");
            printf("\n-- Ingrese 1 para actualizar el juego de la lista (Tendra que ingresar datos del juego nuevo) -- \n");
            printf("\n-- Ingrese 2 para eliminar el juego de la lista--\n\n");

            fflush(stdin);
            scanf("%d",&num);
            if(num == 1){
                Juego* data_2 = data->value; 
                eraseTreeMap(Arbol_Precio,&data_2->precio);
                eraseTreeMap(Arbol_Valoracion,&data_2->valoracion);
                eraseTreeMap(Arbol_Fecha,&data_2->fecha);
                eraseMap(Mapa_Juegos,name);

                Agregar_Juego(Arbol_Precio,Arbol_Valoracion,Arbol_Fecha,Mapa_Juegos);

                printf(" Se ha completado con exito la actualizacin del juego!!\n");

            }else if(num == 2){

                Juego* data_2 = data->value; 
                eraseTreeMap(Arbol_Precio,&data_2->precio);
                eraseTreeMap(Arbol_Valoracion,&data_2->valoracion);
                eraseTreeMap(Arbol_Fecha,&data_2->fecha);
                eraseMap(Mapa_Juegos,name);

                printf(" Se ha realizado con exito la eliminacion del juego!!\n");

            }else{
                printf("Numero ingresado no es ni 1 ni 2, intente de nuevo\n");
            }

        }
    }

}

void exportar(HashMap* Mapa_Juegos){

    Pair_2* data = firstMap(Mapa_Juegos);
    if(data == NULL){
        printf("Aun no se ingresan juegos, intente de nuevo.\n");
    }else{

        FILE* file;
        char NombreArchivo[50];
        printf("Ingrese el nombre del archivo: \n");
        fflush(stdin);
        scanf("%50[^\n]", NombreArchivo);
        file = fopen(NombreArchivo, "w");
        if (NombreArchivo==NULL){
            printf("Archivo inexistente, compruebe nuevamente\n");
        return;
        }  
        
        while(data != NULL){
            Juego* data_2 = data->value;
            fprintf(file,"%s,%d,%d,%d\n",data_2->nombre,data_2->fecha,data_2->valoracion,data_2->precio);
            data = nextMap(Mapa_Juegos);
        }
        fclose(file);

        printf("\nSe ha realizado con exito el exportar datos de juegos!\n");
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





