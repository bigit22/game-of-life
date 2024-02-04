#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 25
#define WIDTH 80

void input(int arr[HEIGHT][WIDTH]);
void draw(int arr[HEIGHT][WIDTH]);
void calculate_next(int current[HEIGHT][WIDTH], int next_field[HEIGHT][WIDTH]);
void init_field(int current_field[HEIGHT][WIDTH]);
void place_alive(int current_field[HEIGHT][WIDTH], int y, int x);
void copy(int current_field[HEIGHT][WIDTH], int next_field[HEIGHT][WIDTH]);

int main() {
    int current[HEIGHT][WIDTH];
    int next_field[HEIGHT][WIDTH];
    int population = 1;

    init_field(current);
    init_field(next_field);

    input(current);

    while (1) {
        draw(current);
        calculate_next(current, next_field);
        copy(next_field, current);
        init_field(next_field);
        printf("Population: %d", population);
        population++;
        usleep(100000);
        system("cls");
    }
    return 0;
}

void input(int arr[HEIGHT][WIDTH]){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            scanf("%d", &arr[i][j]);
        }
    }
}

void init_field(int current_field[HEIGHT][WIDTH])
{
	for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            current_field[y][x] = 0;
        }
    }
}

void place_alive(int current_field[HEIGHT][WIDTH], int y, int x)
{
    current_field[y][x] = 1;
}

void copy(int current_field[HEIGHT][WIDTH], int next_field[HEIGHT][WIDTH])
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            next_field[y][x] = current_field[y][x];
        }
    }
}

int count_alive_neigbours(int current_field[HEIGHT][WIDTH], int y, int x)
{
    return
        current_field[(HEIGHT + y - 1) % HEIGHT][(WIDTH + x) % WIDTH] +
        current_field[(HEIGHT + y - 1) % HEIGHT][(WIDTH + x + 1) % WIDTH] +
        current_field[(HEIGHT + y) % HEIGHT][(WIDTH + x + 1) % WIDTH] +
        current_field[(HEIGHT + y + 1) % HEIGHT][(WIDTH + x + 1) % WIDTH] +
        current_field[(HEIGHT + y + 1) % HEIGHT][(WIDTH + x) % WIDTH] +
        current_field[(HEIGHT + y + 1) % HEIGHT][(WIDTH + x - 1) % WIDTH] +
        current_field[(HEIGHT + y) % HEIGHT][(WIDTH + x - 1) % WIDTH] +
        current_field[(HEIGHT + y - 1) % HEIGHT][(WIDTH + x - 1) % WIDTH];
}

void calculate_next(int current[HEIGHT][WIDTH], int next_field[HEIGHT][WIDTH])
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            int aliveCount = count_alive_neigbours(current, y, x);
            // current is ALIVE && have 2 or 3 alive neighbours is alive -> keep it ALIVE
            // else -> make it DEAD
            if (current[y][x] == 1 && aliveCount != 2 && aliveCount != 3)
            {
                next_field[y][x] = 0;
            }
            // current is DEAD && more than 3 neigbours is alive -> make it ALIVE
            else if (current[y][x] == 0 && aliveCount == 3)
            {
                next_field[y][x] = 1;
            }
            else
            {
				next_field[y][x] = current[y][x];
			}
		}
	}
}

void draw(int arr[HEIGHT][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (arr[i][j] == 1)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}
