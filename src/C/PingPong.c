#include <stdio.h>

void field(int left_rocket, int right_rocket, int ball_x, int ball_y);
int game(int* left_r, int* right_r, int* b_x, int* b_y, int* score_1, int* score_2);

int main(){
    int left_rocket = 14;
    int right_rocket = 14;
    int ball_x = 44;
    int ball_y = 14;
    int score1 = 0;
    int score2 = 0;
    game(&left_rocket, &right_rocket, &ball_x, &ball_y, &score1, &score2);
    return 0;
}

void field(int left_rocket, int right_rocket, int ball_x, int ball_y) {
    for (int y = 0; y <= 30; y++) {
        for (int x = 0; x <= 90; x++) {
            if (y == 0 || y == 30 || x == 0 || x == 90) printf("#");
            else if (ball_x == x && ball_y == y) printf("*");
            else if ((x == 1) && (left_rocket == y || left_rocket == y + 1 || left_rocket == y - 1)) printf("|");
            else if ((x == 89) && (right_rocket == y || right_rocket == y + 1 || right_rocket == y - 1)) printf("|");
            else printf(" ");
        }
        printf("\n");
    }
}

int game(int* left_r, int* right_r, int* b_x, int* b_y, int* score_1, int* score_2)
{
    int flag;
    int vector_ball_x = 1;
    int vector_ball_y = 1;
    char shift;
    field(*left_r, *right_r, *b_x, *b_y);
    while (*score_1 != 2 && *score_2 != 2)
    {
        flag = 1;
        *b_x = *b_x + vector_ball_x;
        *b_y = *b_y + vector_ball_y;
        while(flag == 1)
        {
            scanf("%c", &shift);
            if(shift == ' ' || shift == 'Q' || shift == 'A' || shift == 'P' || shift == 'L')
            {
                *left_r = *left_r - (shift == 'Q') + (shift == 'A');
                *left_r = *left_r - (*left_r > 28) + (*left_r < 2);
                *right_r = *right_r - (shift == 'P') + (shift == 'L');
                *right_r = *right_r - (*right_r > 28) + (*right_r < 2);
                flag = 0;
            }
        }
        vector_ball_x = (1 - 2 *(*b_x == 1 || *b_x == 89)) * vector_ball_x;
        vector_ball_y = (1 - 2 *(*b_y == 1 || *b_y == 29)) * vector_ball_y;
        if (*b_x == 1 && (*b_y != *left_r && *b_y != *left_r + 1 && *b_y != *left_r - 1))
        {
            *score_2 = *score_2 + 1;
            *b_x = 44;
            *b_y = 14;
            *left_r = 14;
            *right_r = 14;
        }
        if (*b_x == 89 && (*b_y != *right_r && *b_y != *right_r + 1 && *b_y != *right_r - 1))
        {
            *score_1 = *score_1 + 1;
            *b_x = 44;
            *b_y = 14;
            *right_r = 14;
            *left_r = 14;
        }
        field(*left_r, *right_r, *b_x, *b_y);
        printf("Left Player: %d\n", *score_1);
        printf("Right Player: %d\n", *score_2);
        if(*score_1 == 2 || *score_2 == 2) *score_1 > *score_2 ? printf("Left Player Won!\n") : printf("Left Player Won!\n");
    }

    return 0;
}
