#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]){
    int mumber=0;
    int matris[3][5];
    srand(time(NULL));

for (int i = 0; i < 3; i++){
    for (int j = 0; j < 5 ;j++){
        matris[i][j]=rand()% (1,9+1);
    }
    
}
for (int i = 0; i < 3; i++){
    for (int j = 0; j < 5; j++){
        printf("%d\t",matris[i][j]);
    }
    printf("\n");
}   
    return 0;
}
