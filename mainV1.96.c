#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "Funciones.h"
/*

Para iniciar el codigo inserta en tu consola el comando:
gcc mainbuild1.9.c Funciones.h Declaraciones.c -o main && ./main

*/
int main(int argc, const char *argv[]) {
    FILE *pointFile;
    struct board boardMemory;
    boardMemory.dimensions = getBoardSize(argc, argv);
    EstructuraDelJuego(&boardMemory);
    system("clear");
    printf("Bienvenido al juego de memoria\n\n\n");

    int opcion;
    do {
        int puntaje;
        showGameMenu();
        printf("\n: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                puntaje = memoryGame(&boardMemory);
                char nombre[20];
                printf("Ingresa tu nombre de jugador: ");
                scanf("%s", nombre);
                pointFile = fopen("./puntos.txt","a");
                fprintf(pointFile,"%d,%s\n",puntaje,nombre);
                fclose(pointFile);// Guardar en un archivo
                break;
            case 2:
                system("clear");
                int puntajeTop = 0;
                char nombreJugador[20];
                pointFile = fopen("./puntos.txt","r");
                while(fscanf(pointFile,"%d,%s", &puntajeTop, nombreJugador)!= EOF) {
                    printf("%s\t%d\n",nombreJugador,puntajeTop);
                }
                fclose(pointFile);
                printf("\n\n");
                break;
            case 3:
                system("clear");
                printf("Bienvenido al las reglas de juego\n\n");
                printf("1. Trata de ingresar numeros no letras ni simblos estraños para que no tengas errores.\n");
                printf("2. Solo ingresa numeros de un intervalo del 1 al 9.\n");
                printf("3. Si quieres hacer mas grande la tabla puedes ir al apartado numero 4,\n   pero ten en consideracion que un numero muy grande puede ocasionar errores o poca visibilidad de si misma.");
                printf("4. No te olvides de tu nombre al guardar tus puntos\n");
                 printf("\n\n");
                break;
            case 4:
                reconfigGame(&boardMemory);
                break;
            case 5:
                printf("Gracias por jugar\n");
                liberarmemoria(&boardMemory);
                break;
            default:
                printf("Opcion no encontrada, por favor ingrese una opcion valida\n");
                break;
        }
    } 
    while (opcion != 5);
    return 0;
}
