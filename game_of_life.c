#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#define BOARD_HEIGHT 25
#define BOARD_WIDTH 80

void input(int Field[BOARD_HEIGHT][BOARD_WIDTH]);
void doo(int Field[BOARD_HEIGHT][BOARD_WIDTH],int FieldSave[BOARD_HEIGHT][BOARD_WIDTH]);
int ReturnNeighboors(int Field[BOARD_HEIGHT][BOARD_WIDTH], int X, int Y);

int main() {
    int FieldSave[BOARD_HEIGHT][BOARD_WIDTH];
    int Field[BOARD_HEIGHT][BOARD_WIDTH];
    input(Field);
    doo(Field, FieldSave);
    return 0;
}

void input(int Field[BOARD_HEIGHT][BOARD_WIDTH]){
    for(int i = 0; i < BOARD_HEIGHT; i++){
        for(int j = 0; j < BOARD_WIDTH; j++){
            scanf("%d", &Field[i][j]);
        }
    }
}

void doo(int Field[BOARD_HEIGHT][BOARD_WIDTH],int  FieldSave[BOARD_HEIGHT][BOARD_WIDTH]){ 
    while(1) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            for (int x = 0; x < BOARD_WIDTH; x++) {
                if (Field[y][x] == 1){
                    printf("X");
                }
                else{
                    printf("-");
                }
            }
            printf("\n");
        }
        usleep(100000);
        system("clear");
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            for (int x = 0; x < BOARD_WIDTH; x++) {
                FieldSave[y][x] = Field[y][x];
                if (Field[y][x] == 1) {
                    if (ReturnNeighboors(Field, x, y) == 2) FieldSave[y][x] = 1;
                    else if (ReturnNeighboors(Field, x, y) == 3) FieldSave[y][x] = 1;
                    else if (ReturnNeighboors(Field, x, y) > 3) FieldSave[y][x] = 0;
                    else if (ReturnNeighboors(Field, x, y) < 2) FieldSave[y][x] = 0;
                } else {
                    if (ReturnNeighboors(Field, x, y) == 3) FieldSave[y][x] = 1;
                }
            }
        }
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            for (int x = 0; x < BOARD_WIDTH; x++) {
                Field[y][x] = FieldSave[y][x];
            }
        }
    }
}

int ReturnNeighboors(int Field[BOARD_HEIGHT][BOARD_WIDTH], int X, int Y) {
    int N = 0;
    if(Y + 1 == BOARD_HEIGHT && X + 1 == BOARD_WIDTH){
        N = Field[0][X - 1] + Field[0][X] + Field[0][0] + Field[Y][X - 1] + Field[Y][0] +
        Field[Y - 1][X - 1] + Field[Y - 1][X] + Field[Y - 1][0];
    }
    else if(Y + 1 == BOARD_HEIGHT && X + 1 < BOARD_WIDTH){
        N = Field[0][X - 1] + Field[0][X] + Field[0][X + 1] + Field[Y][X - 1] + Field[Y][X + 1] +
        Field[Y - 1][X - 1] + Field[Y - 1][X] + Field[Y - 1][X + 1];
    }
    else if(Y + 1 < BOARD_HEIGHT && X + 1 == BOARD_WIDTH){
       N = Field[Y + 1][X - 1] + Field[Y + 1][X] + Field[Y + 1][0] + Field[Y][X - 1] + Field[Y][0] +
        Field[Y - 1][X - 1] + Field[Y - 1][X] + Field[Y - 1][0];
    }
    else if(Y - 1 < 0 && X - 1 < 0){
        N = Field[Y + 1][BOARD_WIDTH] + Field[Y + 1][X] + Field[Y + 1][X + 1] + Field[Y][BOARD_WIDTH] + Field[Y][X + 1] + 
        Field[BOARD_HEIGHT][BOARD_WIDTH] + Field[BOARD_HEIGHT][X] + Field[BOARD_HEIGHT][X + 1];
    }
    else if(Y - 1 > 0 && X - 1 == 0){
        N = Field[Y + 1][BOARD_WIDTH] + Field[Y + 1][X] + Field[Y + 1][X + 1] + Field[Y][BOARD_WIDTH] + Field[Y][X + 1] + 
        Field[Y - 1][BOARD_WIDTH] + Field[Y - 1][X] + Field[Y - 1][X + 1];
    }
    else if(Y - 1 == 0 && X - 1 > 0){
        N = Field[Y + 1][X - 1] + Field[Y + 1][X] + Field[Y + 1][X + 1] + Field[Y][X - 1] + Field[Y][X + 1] + 
        Field[BOARD_HEIGHT][X - 1] + Field[BOARD_HEIGHT][X] + Field[BOARD_HEIGHT][X + 1];
    }
    else{
        N = Field[Y + 1][X - 1] + Field[Y + 1][X] + Field[Y + 1][X + 1] + Field[Y][X - 1] + Field[Y][X + 1] + 
        Field[Y - 1][X - 1] + Field[Y - 1][X] + Field[Y - 1][X + 1];
    }
    return N;
}
