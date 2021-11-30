#include "Funciones.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Forma y colores de la tabla
void EstructuraDelJuego(struct board *boardMemory) {
    strcpy(boardMemory->borderColor, "\033[0;35m");//color de los bordes
    strcpy(boardMemory->contentColor, "\033[1;32m");//color de el contenido
    initBoard(boardMemory);
    fillBoard(boardMemory);
    system("clear"); 
}
//Estructura de la tabla 
struct size getBoardSize(int argc, const char *argv[]) {
    struct size board = {DEFAULT_ROWS, DEFAULT_COLUMNS};
    if (argc >= 3) {
        int n = atoi(argv[1]);
        int m = atoi(argv[2]);
        board.n = (n == 0) ? DEFAULT_ROWS : n;
        board.m = (m == 0) ? DEFAULT_COLUMNS : m;
        if ((board.n * board.m) % 2 != 0) {
            printf("Seleccione una dimension de tablero que contenga una cantidad " "par de elementos\n");
            exit(1);
        }
    }
    return board;
}
//llenado de la tabla con valores aleatorios
void initBoard(struct board *board) {
    int nFilas = board->dimensions.n;
    int nColumnas = board->dimensions.m;
    board->contenido = (struct celda **) malloc(sizeof(struct celda*) * nFilas);
    if (board->contenido != NULL) {
        for(int i = 0; i < nFilas; i++) {
            (board->contenido)[i] = (struct celda *) malloc(sizeof(struct celda) * nColumnas );
            if ((board->contenido)[i] == NULL) {
                printf("No se puede reservar memoria para el tablero");//este apartado es por si ocurre un error en la tabla
                exit(1);
            }
            for(int j = 0; j< nColumnas; j++) {
                board->contenido[i][j].card = '\0';
                board->contenido[i][j].status = HIDDEN;
            }
        }
    } 
    else {
        printf("No se puede reservar memoria para el tablero");//este apartado es por si ocurre un error en la tabla
        exit(1);
    }
}
//Llenado de tabla
void fillBoard(struct board *board) {
    int nFilas = board->dimensions.n;
    int nColumnas = board->dimensions.m;
    srand(time(NULL));
    int nOptions = (nColumnas * nFilas) / 2;
    char options[nOptions];
    for (int j = 0; j < nOptions; j++) {
        options[j] = '0' +rand() % 10;//Llenando con letras aleatorias //TODO: cambiar a numeros aleatorios del 1 al 9
    }
    int i = 0;
    while (i < nOptions) {
        int xPos1, yPos1, xPos2, yPos2;
        do {
            xPos1 = rand() % nFilas;
            yPos1 = rand() % nColumnas;
        } while (board->contenido[xPos1][yPos1].card != '\0');
        do {   
            xPos2 = rand() % nFilas;
            yPos2 = rand() % nColumnas;
        } while (board->contenido[xPos2][yPos2].card != '\0');
        if (xPos1 == xPos2 && yPos1 == yPos2) {
            continue;
        }
        board->contenido[xPos2][yPos2].card = options[i];
        board->contenido[xPos1][yPos1].card = options[i];
        i++;
    }
}
//liberacion de memoria
void liberarmemoria(struct board *board) {
    int nFilas = board->dimensions.n;
    for(int i = 0 ;i < nFilas; i++ ) {
        free((board->contenido)[i]);
    }  
    free(board->contenido);
}
//funcion de muestra en pantalla con decoracion
void displayBoard(struct board *board) {
    printf("\n\n%s┌", board->borderColor);
    for (int j = 0; j < board->dimensions.m - 1; j++) {
        printf("───┬");
    }
        printf("───┐\n");
        for (int i = 0; i < board->dimensions.n - 1; i++) {
            for (int j = 0; j < board->dimensions.m; j++) {
            char *contentColor = board->contentColor;
            char *borderColor = board->borderColor;
            mostrar_celda(borderColor, contentColor, board->contenido[i][j]);
        }
        printf("│\n├");
        for (int j = 0; j < board->dimensions.m - 1; j++) {        
        printf("───┤");
        }
        printf("───┤\n");
        }
        for (int j = 0; j < board->dimensions.m; j++) {
        char *contentColor = board->contentColor;
        char *borderColor = board->borderColor;
        mostrar_celda(borderColor, contentColor,board->contenido[board->dimensions.n - 1][j]);
        }
        printf("│\n└");
        for (int j = 0; j < board->dimensions.m - 1; j++) {
        printf("───┴");
    }
    printf("───┘\033[0m\n\n");
}
//mostrando o ocultando variables
void mostrar_celda(char *borderColor, char *contentColor, struct celda celda) {
    char *ocultarvariable = "♣"; 
    char contenido[2];
    contenido[0] = celda.card;
    contenido[1] = '\0';
    char *vacio = " "; 
    char *displayString; 

    //Modos de presentacion de contenido
    switch (celda.status){
        case HIDDEN:
            displayString = ocultarvariable;
            break;
        case SHOW:
            displayString = contenido;
            break;
        case MATCH:
            displayString =  vacio;
            break;
    }
    printf("│%s %s %s", contentColor, displayString, borderColor);
}
//Creacion de pares
bool formandopares(struct board *board) {
    int nFilas = board->dimensions.n;
    int nColumnas = board->dimensions.m;

    for (int i = 0; i < nFilas; i++) {
        for (int j = 0; j < nColumnas; j++) {
            if (board->contenido[i][j].status == HIDDEN) {
                return true;
            }
        }
    }
    return false;
}
void cleanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
int memoryGame(struct board *boardMemory) {
    char cont;
    int puntajes = 0;
    
    do {
        int xPos1, yPos1, xPos2, yPos2;

        system("clear");
        printf("\nPuntos %d", puntajes);
        displayBoard(boardMemory);
        printf("Seleccione la tarjeta que desea ver (#,#): ");
        scanf("%d,%d", &xPos1, &yPos1);
 
        while ((xPos1>9?:xPos1<1) ^ (yPos1>9?:yPos1<1)){//Arreglo de ingreso de numeros
        system("clear");
        printf("Error al insertar el numero\n");
        displayBoard(boardMemory);
        printf("Ingrese un numero valido en formato ( #,# ) con una coma: ");
        scanf("%d,%d", &xPos1, &yPos1);
        system("clear");
        }
        
        xPos1--;
        yPos1--;
        system("clear");  
        
        boardMemory->contenido[xPos1][yPos1].status = SHOW;
        printf("\nPuntos %d", puntajes);
        displayBoard(boardMemory);

        printf("Seleccione la segunda tarjeta que desea ver (#,#): ");
        scanf("%d,%d", &xPos2, &yPos2);

        while ((xPos2>9?:xPos2<1) ^ (yPos2>9?:yPos2<1)){//Arreglo de ingreso de numeros
        system("clear");
        printf("Error al insertar el numero\n");
        displayBoard(boardMemory);
        printf("Ingrese un numero valido en formato ( #,# ) con una coma: ");
        scanf("%d,%d", &xPos2, &yPos2);
        system("clear");
        }

        xPos2--;
        yPos2--;
        system("clear");

        boardMemory->contenido[xPos2][yPos2].status = SHOW;
        printf("\nPuntos %d", puntajes);
        displayBoard(boardMemory);
        scanf("%c", &cont);

        if (boardMemory->contenido[xPos2][yPos2].card ==
            boardMemory->contenido[xPos1][yPos1].card) {
            boardMemory->contenido[xPos2][yPos2].status = MATCH;
            boardMemory->contenido[xPos1][yPos1].status = MATCH;
            printf("\nHas encontrado una pareja\n");
            puntajes++;
        } else {
            printf("\nLa seleccion no forma una pareja\n");
            boardMemory->contenido[xPos2][yPos2].status = HIDDEN;
            boardMemory->contenido[xPos1][yPos1].status = HIDDEN;
        }
        printf("Presione cualquier tecla para continuar o N para salir: ");
        scanf("%c", &cont);
        system("clear");
        if (cont == 'N' || cont == 'n') {
            return puntajes;
        }
        cleanBuffer();
    } 
    while (formandopares(boardMemory));
    return puntajes;
}
void reconfigGame(struct board *boardMemory) {
    int n = 1, m = 1;

    if ((n * m) % 2 != 0) {
        printf("Ingrese la cantidad de filas: ");
        scanf("%d", &n);
        printf("Ingrese la cantidad de columnas: ");
        scanf("%d", &m);
    }
    while (n<2 || m<2){
        system("clear"); 
        printf("Ingrese correctamente los numeros pares, ejemplo 2 * 2 \n\n");
        printf("Ingrese la cantidad de filas: ");
        scanf("%d", &n);
        printf("Ingrese la cantidad de columnas: ");
        scanf("%d", &m);
    }
    while (n>16 || m>16){
        system("clear"); 
        printf("Ingreso un numero demasiado grande, pruebe con un numero entre 2 y 16\n\n");
        printf("Ingrese la cantidad de filas: ");
        scanf("%d", &n);
        printf("Ingrese la cantidad de columnas: ");
        scanf("%d", &m);
    }
    liberarmemoria(boardMemory);
    boardMemory->dimensions.n = n;
    boardMemory->dimensions.m = m;

    EstructuraDelJuego(boardMemory);
    system("clear"); 
}
void showGameMenu() {
    printf("1.Jugar\n2.Ver Puntajes\n3.Relas del juego\n4.Configuración\n5.Salir");
}