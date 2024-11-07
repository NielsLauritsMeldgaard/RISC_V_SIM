#ifndef SNAKE_H
#define SNAKE_H

#include "game.h"

typedef struct
{
    int length;

    struct Head
    {
        int x;
        int y;
        int vx;
        int vy;
        enum Direction dir;
    } head;

    struct Segments 
    {
        int x;
        int y;
        int vx;
        int vy;
        enum Direction dir;
    } segment[1000];
} Snake;

void init_snake (Snake *snake, int x, int y, int length);
void draw_snake (Snake *snake, int *init_draw_flag);
void erase_snake (Snake *snake);
void move_snake (Snake *snake, int dx, int dy, enum Direction direction, int velocity);
void increase_snake (Snake *snake, int length);

#endif // SNAKE_H