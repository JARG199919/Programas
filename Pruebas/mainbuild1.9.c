#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "Funciones.h"

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
                reconfigGame(&boardMemory);
                break;
            case 4:
                printf("Gracias por jugar\n");
                liberarmemoria(&boardMemory);
                break;
            default:
                printf("Obcion no encontrada, por favor ingrese una opcion valida\n");
                break;
        }
    } 
    while (opcion != 4);
    return 0;
}

