#include "list.c"
#include "hashmap.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>


//Programa principal

int main(void){

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