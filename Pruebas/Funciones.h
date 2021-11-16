#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//costantes definidas en ES y hay algunas en ingles
#define DEFAULT_ROWS 4
#define DEFAULT_COLUMNS 4
#define COLOR_STRING_SIZE 12


//Estructuras definidas
enum showStatus { HIDDEN, SHOW, MATCH };

struct size {
    int n;
    int m;
};
struct celda{
    char card;
    enum showStatus status;
};
struct board {
    struct size dimensions;
    char borderColor[COLOR_STRING_SIZE];
    char contentColor[COLOR_STRING_SIZE]; 
    struct celda **contenido; 
};
//Declaracion de funciones
struct size getBoardSize(int, const char *[]);
void initBoard(struct board*);
void fillBoard(struct board*); 
void liberarmemoria(struct board*);
void displayBoard(struct board*);
void mostrar_celda(char*, char*,struct celda);
bool formandopares(struct board*);
void EstructuraDelJuego(struct board *);
int memoryGame(struct board *);
void reconfigGame(struct board *);
void showGameMenu();
void cleanBuffer();