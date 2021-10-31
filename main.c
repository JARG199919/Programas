#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define DEFAULT_ROWS 9
#define DEFAULT_COLUMNS 9

struct size {
    int n;
    int m;
    };
struct board {
    struct size dimensions;
    char *content[]; 
    };

//void showParameters(int, const char *[]);
struct size getBoardSize(int, const char *[]);
void initBoard(struct board*);
void displayBoard(struct board*);

int main(int argc, const char *argv[]) {
    srand(time(NULL));
    //showParameters(argc, argv);
    struct board boardMemory;
    boardMemory.dimensions = getBoardSize(argc, argv);
    //printf("Iniciando juego de memoria con tablero de dimensiones de %d x %d\n",boardMemory.dimensions.n, boardMemory.dimensions.m);
    initBoard(&boardMemory);
    displayBoard(&boardMemory);
    return 0;
}

/*void showParameters(int argc, const char *argv[]) {
    printf("Parametros\n");
    for (int i = 0; i < argc; i++) {
        printf("#%d\t%s\n", i, argv[i]);
    }
    printf("Fin\n");
}*/


struct size getBoardSize(int argc, const char *argv[]) {
    struct size board = {DEFAULT_ROWS, DEFAULT_COLUMNS};
    if (argc >= 3) {
        int n = atoi(argv[1]);
        int m = atoi(argv[2]);

        board.n = (n == 0) ? DEFAULT_ROWS : n;
        board.m = (m == 0) ? DEFAULT_COLUMNS : m;

        if ((board.n * board.m) % 2 != 0) {
            printf(
                "Seleccione una dimension de tablero que contenga una cantidad "
                "par de elementos\n");
            exit(1);
        }
    }
    return board;
}

/**
 * Llenar el contendio del tablero con parajes
 * posicionadas de forma aleatoria segun las dimensiones 
 * del tablero
 **/
void initBoard(struct board* board) {
    int cRows = board->dimensions.n;
    int cColumns = board->dimensions.m;
    printf("Llenando el tablero %d x %d", cRows, cColumns);
}
void displayBoard(struct board *board) {
    printf("\n\n");
    srand(time(NULL));
    for (int i = 0 ; i < board->dimensions.n ; i ++) {
        for( int j = 0 ; j < board->dimensions.m; j ++) {
            printf("| %d ",rand()% (10-1)+1);
        }
        printf("|\n");
    }
    printf("\n\n");
}
