#include <stdio.h>

#include "../inc/snake.h"
#include "../inc/ANSI.h"

//initialize the snake by setting the head and the segments
void init_snake (Snake *snake, int x, int y, int length)
{
    snake->head.x = x;
    snake->head.y = y;
    snake->head.vx = 1;
    snake->head.vy = 0;
    snake->head.dir = RIGHT; //HARDCODED START DIRECTION
    snake->length = length;

    for (int i = 0; i <= snake->length - 1; i++)
    {
        if(i == 0)
        {
            snake->segment[i].x = snake->head.x - 1;
            snake->segment[i].y = snake->head.y;
            snake->segment[i].vx = snake->head.vx;
            snake->segment[i].vy = snake->head.vy;
            snake->segment[i].dir = snake->head.dir;
        }
        else
        {
            snake->segment[i].x = snake->segment[i - 1].x - 1;
            snake->segment[i].y = snake->segment[i - 1].y;
            snake->segment[i].vx = snake->segment[i - 1].vx;
            snake->segment[i].vy = snake->segment[i - 1].vy;
            snake->segment[i].dir = snake->segment[i - 1].dir;
        }
        
    }

}

//draw the snake on the screen by drawing the head and the first segments
void draw_snake (Snake *snake, int *init_draw_flag)
{
    gotoxy(snake->head.x, snake->head.y);
    printf("O");

    if (*init_draw_flag == 0)
    {
        for (int i = 0; i <= snake->length - 1; i++)
        {
            gotoxy(snake->segment[i].x, snake->segment[i].y);

            if ((snake->segment[i].dir = RIGHT) || (snake->segment[i].dir = LEFT)) 
                printf("-");
            else if ((snake->segment[i].dir = DOWN) || (snake->segment[i].dir = UP)) 
                printf("|");
        }    

        *init_draw_flag = 1;
    }
    else
    {
        gotoxy(snake->segment[0].x, snake->segment[0].y);
        if ((snake->segment[0].dir == RIGHT && snake->head.dir == UP) ||
            snake->segment[0].dir == DOWN && snake->head.dir == LEFT)
        {
            printf("%c", 217); //lower right corner
        }
        else if ((snake->segment[0].dir == UP && snake->head.dir == LEFT) ||
            snake->segment[0].dir == RIGHT && snake->head.dir == DOWN)
        {
            printf("%c", 191); //upper right corner
        }
        else if ((snake->segment[0].dir == LEFT && snake->head.dir == UP) ||
            snake->segment[0].dir == DOWN && snake->head.dir == RIGHT)
        {
            printf("%c", 192); //lower left corner
        }
        else if ((snake->segment[0].dir == LEFT && snake->head.dir == DOWN) ||
            snake->segment[0].dir == UP && snake->head.dir == RIGHT)
        {
            printf("%c", 218); //upper left corner
        }
        else if ((snake->segment[0].dir == RIGHT) || (snake->segment[0].dir == LEFT))
        {
            printf("-");
        }
        else if ((snake->segment[0].dir == DOWN) || (snake->segment[0].dir == UP))
        {
            printf("|");
        }
    }
}

//erase the snake by drawing a space on the head and the last segments
void erase_snake (Snake *snake)
{
    gotoxy(snake->head.x, snake->head.y);
    printf(" ");

   
    gotoxy(snake->segment[snake->length - 1].x, snake->segment[snake->length - 1].y);
    printf(" ");
}

//move the snake by updating the head and the segments to the position of the previous segment
void move_snake (Snake *snake, int dx, int dy, enum Direction direction, int velocity)
{
    for (int i = snake->length - 1; i >= 0; i--)
    {
        if (i == 0)
        {
            snake->segment[i].vx = snake->head.vx;
            snake->segment[i].vy = snake->head.vy;
            snake->segment[i].dir = snake->head.dir;
        }
        else
        {
            snake->segment[i].vx = snake->segment[i - 1].vx;
            snake->segment[i].vy = snake->segment[i - 1].vy;
            snake->segment[i].dir = snake->segment[i - 1].dir;
        }
        
        snake->segment[i].x += (dx * snake->segment[i].vx);
        snake->segment[i].y += (dy * snake->segment[i].vy);
    }

    switch (direction)
    {
    case RIGHT:
        snake->head.vx = 1;
        snake->head.vy = 0;
        snake->head.dir = RIGHT;
        break;
    case LEFT:
        snake->head.vx = -1;
        snake->head.vy = 0;
        snake->head.dir = LEFT;
        break;
    case DOWN:
        snake->head.vx = 0;
        snake->head.vy = 1;
        snake->head.dir = DOWN;
        break;        
    case UP:
        snake->head.vx = 0;
        snake->head.vy = -1;
        snake->head.dir = UP;
        break;
    default:
        break;
    }

    snake->head.x += (dx * snake->head.vx);
    snake->head.y += (dy * snake->head.vy);
}

//increase the snake by adding a segment to the end of the snake
void increase_snake (Snake *snake, int length)
{
    if (length > snake->length) 
    {
        snake->length++;

        switch (snake->segment[snake->length - 2].dir)
        {
        case RIGHT: 
            snake->segment[snake->length - 1].x = snake->segment[snake->length - 2].x - 1; 
            snake->segment[snake->length - 1].y = snake->segment[snake->length - 2].y; 
            break;

        case LEFT: 
            snake->segment[snake->length - 1].x = snake->segment[snake->length - 2].x + 1; 
            snake->segment[snake->length - 1].y = snake->segment[snake->length - 2].y;
        break;

        case DOWN: 
            snake->segment[snake->length - 1].x = snake->segment[snake->length - 2].x; 
            snake->segment[snake->length - 1].y = snake->segment[snake->length - 2].y - 1;
        break;

        case UP: 
            snake->segment[snake->length - 1].x = snake->segment[snake->length - 2].x; 
            snake->segment[snake->length - 1].y = snake->segment[snake->length - 2].y + 1;            
        break;
        default: break; 
        }

        snake->segment[snake->length - 1].vx = snake->segment[snake->length - 2].vx;
        snake->segment[snake->length - 1].vy = snake->segment[snake->length - 2].vy;
        snake->segment[snake->length - 1].dir = snake->segment[snake->length - 2].dir;
    }
}