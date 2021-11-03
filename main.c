#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

//costantes definidas en ingles
#define DEFAULT_ROWS 9
#define DEFAULT_COLUMNS 9
#define COLOR_STRING_SIZE 12
//Estructuras definidas
struct size {
    int n;
    int m;
};
struct board {
    struct size dimensions;
    char borderColor[COLOR_STRING_SIZE];
    char contentColor[COLOR_STRING_SIZE]; 
    char **content; 
};

//Declaracion de funciones
struct size getBoardSize(int, const char *[]);
void initBoard(struct board*);
void freeBoard(struct board*);
void displayBoard(struct board*);
void playerGame(void);
void innumeros(void);


int main(int argc, const char *argv[]) {
    struct board boardMemory;
    boardMemory.dimensions = getBoardSize(argc, argv);
    strcpy(boardMemory.borderColor, "\033[0;35m");
    strcpy(boardMemory.contentColor, "\033[1;36m");
    printf("Iniciando juego de memoria con tablero %d x %d\n",boardMemory.dimensions.n, boardMemory.dimensions.m);
    initBoard(&boardMemory);
    displayBoard(&boardMemory);
    freeBoard(&boardMemory);
    printf("Jugador 1, ingrese sus numeros para jugar:\n");
    playerGame();
    /*printf("Jugador 2, ingrese sus numeros para juagar:\n");
    playerGame();*/
    return 0;
}
//Estructura de la tabla 
struct size getBoardSize(int argc, const char *argv[]) {
    struct size board = {DEFAULT_ROWS, DEFAULT_COLUMNS};
    if (argc >= 3) {
        int n = atoi(argv[1]);
        int m = atoi(argv[2]);
        board.n = (n == 0) ? DEFAULT_ROWS : n;
        board.m = (m == 0) ? DEFAULT_COLUMNS : m;
    }
    return board;
}
//llenado de la tabla con valores aleatorios
void initBoard(struct board *board) {
    int cRows = board->dimensions.n;
    int cColumns = board->dimensions.m;
    board->content = (char **) malloc(sizeof(char *) * cRows);
    if (board->content != NULL) {
        for(int i = 0; i < cRows; i++) {
            (board->content)[i] = (char *) malloc(sizeof(char) * cColumns );
            if ((board->content)[i] == NULL) {
                printf("No se puede reservar memoria para el tablero");
                exit(1);
            }
            for(int j = 0; j< cColumns; j++) {
                board->content[i][j] = rand()% (10-1)+1;
            }
        }
    } 
    else {
        printf("No se puede reservar memoria para el tablero");
        exit(1);
    }
}
void freeBoard(struct board *board) {
    int cRows = board->dimensions.n;
    for(int i = 0 ;i < cRows; i++ ) {
        free((board->content)[i]);
    }
    free(board->content);
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
            printf("│%s %d %s",board->contentColor, board->content[i][j], board->borderColor);
        }
        printf("│\n├");
        for (int j = 0; j < board->dimensions.m - 1; j++) {
            printf("───┼");
        }
        printf("───┤\n");
        }
        for (int j = 0; j < board->dimensions.m; j++) {
        printf("│%s %d %s",board->contentColor, board->content[board->dimensions.n -1][j], board->borderColor);
    }
        printf("│\n└");
        for (int j = 0; j < board->dimensions.m - 1; j++) {
        printf("───┴");
    }
    printf("───┘\033[0m\n\n");
}
void innumeros(void){
     int jugador1=0;
    int jugador2=0;
        printf("turno de jugador 1\n");
         printf("ingrese el numero que quiere elegir: ");
          scanf("%d",&jugador1);
        printf("%d\n",jugador1);
        
        printf("turno de jugador 2\n");
          printf("ingrese el numero que quiere elegir: ");
            scanf("%d",&jugador2);
        printf("%d\n",jugador2);
    
}
void playerGame(void){
    innumeros();   
}
