#include <stdio.h>      
//#include <stdlib.h>    / gonna be used    /
//#include <fcntl.h>    /  for interactive /
//#include <unistd.h>  /   mode later     /

#define N 30
#define M 90

void interface(int array[][M]);
void input(int array[][M]);
void filling_array(int array[][M]);
int cell_life(int array[][M]);
int check_neighbours(int array[][M], int cell_y, int cell_x);
int live_neighbours(int x, int y, int array[][M]);

int main() {
    int matrix[N][M];
    filling_array(matrix);
    input(matrix);
    interface(matrix);
    while(1)
    {
        if (cell_life(matrix)) break;
        interface(matrix);
    }

    return 0;
}
 
 void filling_array(int array[][M])
 {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            array[i][j]=0;
        }
    }
 }

 void input(int array[][M])
 {
    int x;
    int y;
    while(scanf("%d%d", &x, &y) == 2)
    {
        if (x == -0 && y == -0) break;
        else array[x][y] = 1;
    }
 }

void interface(int array[][M])
 {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            //printf("%d", array[i][j]);
            if (array[i][j] == 1) printf("*");
            else printf(" ");
        }
        printf("\n");
    }
 }

 int cell_life(int array[][M])
 {
    int flag_stop = 1;
    int neighbours[N][M];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++) neighbours[i][j] = check_neighbours(array, i, j);
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if(array[i][j] == 0 && neighbours[i][j] == 3)
            {
                array[i][j] = 1;
                flag_stop = 0;
            }
            else if(array[i][j] == 1 && (neighbours[i][j] > 3 || neighbours[i][j] < 2))
            {
                array[i][j] = 0;
                flag_stop = 0;
            }
        }
    }
    return flag_stop;
 }

 int check_neighbours(int array[][M], int cell_y, int cell_x)
 {
    int amout_of_lives = 0;
    amout_of_lives += live_neighbours(cell_x - 1, cell_y, array);
    amout_of_lives += live_neighbours(cell_x, cell_y - 1, array);
    amout_of_lives += live_neighbours(cell_x + 1, cell_y, array);
    amout_of_lives += live_neighbours(cell_x, cell_y + 1, array);
    amout_of_lives += live_neighbours(cell_x - 1, cell_y - 1, array);
    amout_of_lives += live_neighbours(cell_x + 1, cell_y + 1, array);
    amout_of_lives += live_neighbours(cell_x - 1, cell_y + 1, array);
    amout_of_lives += live_neighbours(cell_x + 1, cell_y - 1, array);
    return amout_of_lives;
 }

 int live_neighbours(int x, int y, int array[][M])
 {
    if (x == -1) x = M - 1;
    else if (x == M) x = 0;
    if (y == -1) y = N -1;
    else if (y == N) y = 0;
    return array[y][x];
 }