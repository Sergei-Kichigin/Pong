#include <stdio.h>

void drawing(int score_l, int score_r, int ballX, int ballY, int r_racket, int l_racket, int x, int y, int SX,
             int SY);
int bounce_off_the_wall(int ballY, int SY);
int bounce_off_the_racket(int ballY, int ballX, int SX, int r_racket, int l_racket);
int racket_movement(char pressed_key, int racket);
void print_table(int x, int y, int l_racket, int r_racket, int ballY, int ballX);

int main() {
    int x = 25, y = 81, l_racket = 13, r_racket = 13;
    int ballY = 13, ballX = 40;
    int SX = 1, SY = 1;
    int score_r = 0, score_l = 0;
    drawing(score_l, score_r, ballX, ballY, r_racket, l_racket, x, y, SX, SY);
    return 0;
}

void print_table(int x, int y, int l_racket, int r_racket, int ballY, int ballX) {
    for (int i = -1; i <= x + 1; i++) {
        for (int j = 0; j <= y; j++) {
            if (i == -1 || i == x + 1) {
                printf("-");
            } else if ((j == 0 || j == y) && (i > -1 && i <= x)) {
                printf("|");
            } else if ((j == 1) && (i == l_racket || i == l_racket + 1 || i == l_racket - 1)) {
                printf("X");
            } else if ((j == 80) && (i == r_racket || i == r_racket + 1 || i == r_racket - 1)) {
                printf("Z");
            } else if (i == ballY && j == ballX) {
                printf("o");
            } else if (j == 40) {
                printf(":");
            } else if (i <= x && i >= 0) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void drawing(int score_l, int score_r, int ballX, int ballY, int r_racket, int l_racket, int x, int y, int SX,
             int SY) {
    char pressed_key;
    while ((score_l != 21) && (score_r != 21)) {
        if (ballX == 81) {
            score_l++;
            ballX = 40;
            ballY = 13;
        } else if (ballX <= 0) {
            score_r++;
            ballX = 40;
            ballY = 13;
        }
        printf("Player 1: %d | Player 2: %d\n", score_l, score_r);
        print_table(x, y, l_racket, r_racket, ballY, ballX);
        // if (scanf("%c", &pressed_key) != 1 || (pressed_key != ' ') || (pressed_key != 'a') || (pressed_key
        // != 'z') || (pressed_key != 'm') || (pressed_key != 'k'))
        // {
        //     printf("не та клавиша");
        // }

        scanf("%c", &pressed_key);
        if ((pressed_key == 'a') || (pressed_key == ' ') || (pressed_key == 'z') || (pressed_key == 'm') ||
            (pressed_key == 'k')) {
            SY = bounce_off_the_wall(ballY, SY);
            SX = bounce_off_the_racket(ballY, ballX, SX, r_racket, l_racket);
            ballY = ballY + SY;
            ballX = ballX + SX;
            if ((pressed_key == 'z') || (pressed_key == 'a')) {
                l_racket = racket_movement(pressed_key, l_racket);
            } else if ((pressed_key == 'k') || (pressed_key == 'm')) {
                r_racket = racket_movement(pressed_key, r_racket);
            }
        }

        fputs("\033c", stdout);
        if (score_l == 21) {
            printf("Player 1 WIN!");
        } else if (score_r == 21) {
            printf("Player 2 WIN!");
        }
    }
}

int bounce_off_the_wall(int ballY, int SY) {
    if (ballY == 0 || ballY == 25) {
        return SY * (-1);
    }
    return SY;
}

int bounce_off_the_racket(int ballY, int ballX, int SX, int r_racket, int l_racket) {
    if ((ballY == l_racket || ballY == l_racket + 1 || ballY == l_racket - 1 || ballY == r_racket ||
         ballY == r_racket + 1 || ballY == r_racket - 1) &&
        (ballX == 1 || ballX == 78)) {
        return SX;
    }
    return SX;
}

int racket_movement(char pressed_key, int racket) {
    int flag;
    int move = racket;

    if (pressed_key == 'z') {
        if (racket < 24) {
            flag = 1;
            move = racket + flag;
        }
    }
    if (pressed_key == 'a') {
        if (racket > 1) {
            flag = -1;
            move = racket + flag;
        }
    }
    if (pressed_key == 'm') {
        if (racket < 24) {
            flag = 1;
            move = racket + flag;
        }
    }
    if (pressed_key == 'k') {
        if (racket > 1) {
            flag = -1;
            move = racket + flag;
        }
    }
    return move;
}
