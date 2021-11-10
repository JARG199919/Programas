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
    struct celda **content; 
};
//Declaracion de funciones
struct size getBoardSize(int, const char *[]);
void initBoard(struct board*);
void fillBoard(struct board*); 
void freeBoard(struct board*);
void displayBoard(struct board*);
void displaycelda(char*, char*,struct celda);
bool hasPairs(struct board*);


void initGame(struct board *);

int main(int argc, const char *argv[]) {
    struct board boardMemory;
    boardMemory.dimensions = getBoardSize(argc, argv);
    initGame(&boardMemory);
    char cont = 'Y';
    do {
        int xPos1, yPos1, xPos2, yPos2;
        displayBoard(&boardMemory);
        printf("Seleccione la tarjeta que desea ver (-,#): ");
        scanf("%d,%d",&xPos1,&yPos1);
        xPos1--; 
        yPos1--;
        boardMemory.content[xPos1][yPos1].status = SHOW;
        system("clear"); 
        displayBoard(&boardMemory);
        
        printf("Seleccione la segunda tarjeta que desea ver (#,-): ");
        scanf("%d,%d",&xPos2,&yPos2);
        xPos2--;
        yPos2--;
        boardMemory.content[xPos2][yPos2].status = SHOW;
        displayBoard(&boardMemory);
        if (boardMemory.content[xPos2][yPos2].card == boardMemory.content[xPos1][yPos1].card) {
             boardMemory.content[xPos2][yPos2].status = MATCH;
             boardMemory.content[xPos1][yPos1].status = MATCH;
             printf("Has encontrado una pareja");
        } else {
             printf("La seleccion no forma una pareja");
             boardMemory.content[xPos2][yPos2].status = HIDDEN;
             boardMemory.content[xPos1][yPos1].status = HIDDEN;
        } 
        scanf("%c",&cont);
        scanf("%c",&cont);
        system("clear");       
    } while(hasPairs(&boardMemory));
    freeBoard(&boardMemory);
    return 0;
    /*struct board boardMemory;
    boardMemory.dimensions = getBoardSize(argc, argv);
    strcpy(boardMemory.borderColor, "\033[0;35m");
    strcpy(boardMemory.contentColor, "\033[1;36m");
    printf("Iniciando juego de memoria con tablero %d x %d\n",boardMemory.dimensions.n, boardMemory.dimensions.m);
    initBoard(&boardMemory);
    displayBoard(&boardMemory);
    freeBoard(&boardMemory);
    printf("Jugador 1, ingrese sus numeros para jugar:\n");
    playerGame();
    return 0;*/
}
void initGame(struct board *boardMemory) {
    strcpy(boardMemory->borderColor, "\033[0;35m");
    strcpy(boardMemory->contentColor, "\033[1;36m");
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
    int cRows = board->dimensions.n;
    int cColumns = board->dimensions.m;
    board->content = (struct celda **) malloc(sizeof(struct celda*) * cRows);
    if (board->content != NULL) {
        for(int i = 0; i < cRows; i++) {
            (board->content)[i] = (struct celda *) malloc(sizeof(struct celda) * cColumns );
            if ((board->content)[i] == NULL) {
                printf("No se puede reservar memoria para el tablero");
                exit(1);
            }
            for(int j = 0; j< cColumns; j++) {
                board->content[i][j].card = '\0';
                board->content[i][j].status = HIDDEN;
            }
        }
    } 
    else {
        printf("No se puede reservar memoria para el tablero");
        exit(1);
    }
}

void fillBoard(struct board *board) {
    int cRows = board->dimensions.n;
    int cColumns = board->dimensions.m;
    srand(time(NULL));
    int nOptions = (cColumns * cRows) / 2;
    char options[nOptions];
    for (int j = 0; j < nOptions; j++) {
        options[j] = 'A' + rand() % 25;
    }
    int i = 0;
    while (i < nOptions) {
        int xPos1, yPos1, xPos2, yPos2;
        do {
            xPos1 = rand() % cRows;
            yPos1 = rand() % cColumns;
        } while (board->content[xPos1][yPos1].card != '\0');
        do {        // TODO: Hacer tiempo para que el usuario vea el contenido de la opcion 2
            xPos2 = rand() % cRows;
            yPos2 = rand() % cColumns;
        } while (board->content[xPos2][yPos2].card != '\0');
        if (xPos1 == xPos2 && yPos1 == yPos2) {
            continue;
        }
        // printf("Llenando posion %d %d y %d %d %c\n", xPos1,yPos1, xPos2,
        // yPos2, options[i]);
        board->content[xPos2][yPos2].card = options[i];
        board->content[xPos1][yPos1].card = options[i];
        i++;
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
            char *contentColor = board->contentColor;
            char *borderColor = board->borderColor;
            displayCelda(borderColor, contentColor, board->content[i][j]);
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
        displayCelda(borderColor, contentColor,board->content[board->dimensions.n - 1][j]);
        }
        printf("│\n└");
        for (int j = 0; j < board->dimensions.m - 1; j++) {
        printf("───┴");
    }
    printf("───┘\033[0m\n\n");
}

void displayCelda(char *borderColor, char *contentColor, struct celda celda) {
    char *hiddenSymbol = "♠"; 
    char content[2];
    content[0] = celda.card;
    content[1] = '\0';
    char *matchString = " "; 

    char *displayString; 
    switch (celda.status){
        case HIDDEN:
            displayString = hiddenSymbol;
            //printf("│%s %s %s", contentColor, displayString ,borderColor);
            break;
        case SHOW:
            displayString = content;
            //printf("│%s %d %s", contentColor, displayString ,borderColor);
            break;
        case MATCH:
            displayString =  matchString;
            //printf("│%s %s %s", contentColor, displayString ,borderColor);
            break;
    }
    printf("│%s %s %s", contentColor, displayString, borderColor);
}
bool hasPairs(struct board *board) {
    int cRow = board->dimensions.n;
    int cColumns = board->dimensions.m;

    for (int i = 0; i < cRow; i++) {
        for (int j = 0; j < cColumns; j++) {
            if (board->content[i][j].status == HIDDEN) {
                return true;
            }
        }
    }
    return false;
}