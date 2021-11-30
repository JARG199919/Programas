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
        printf("\n\nIngrese una opción: ");
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
                system("clear");//Es te caso muestra los puntajes guardados con anterioridad
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
                system("clear");//Reglas estableciadas
                printf("Bienvenido al las reglas de juego\n\n");
                printf("1. Trata de ingresar numeros no letras ni simblos estraños para que no tengas errores.\n");
                printf("2. Solo ingresa numeros de un intervalo del 1 al 9.\n"); 
                printf("3. Guardar tus puntos con un nombre sin espacios.\n");
                printf("4. Si quieres hacer mas grande la tabla puedes ir al apartado numero 4,\n   pero ten en consideracion que un numero muy grande puede ocasionar errores o poca visibilidad de si misma,\n   el numero maximo es de 16, asi que ten en cuenta este limite.\n");
                printf("5. No configures la tabla menor a 2 ya que seria demasiado facil jugar y podria probocar errores fatales.\n\n");
                printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------");
                 printf("\n\n");
                break;
            case 4:
                system("clear");
                printf("'Ingrese una cantida mayor a 2 numeros enteros'\n\n");
                reconfigGame(&boardMemory);// Se configura el tamaño de la tabla
                break;
            case 5:
                printf("Gracias por jugar\n");
                liberarmemoria(&boardMemory);// Finaliza el programa
                break;
            default:
                printf("No existe esa opcion, por favor ingrese una opcion valida\n");
                break;
        }
    } 
    while (opcion != 5);
    return 0;
}
