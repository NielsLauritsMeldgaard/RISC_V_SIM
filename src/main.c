#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../inc/ANSI.h"
#include "../inc/game.h"
#include "../inc/snake.h"
#include "../inc/food.h"

#define MAP_X 5
#define MAP_Y 3
#define MAP_WIDTH 115
#define MAP_HEIGHT 25
#define MAX_GAME_COUNTER 1000
#define DEFAULT_SNAKE_LENGTH 5
#define VELOCITY 1

int main()
{
    //set structs
    Snake snake;
    Food foods[3];
    enum Direction current_direction = IDLE;

    //set variables
    int length = DEFAULT_SNAKE_LENGTH;
    int init_draw_flag = 0;
    int game_counter = 0;
    int game_time = 0;

    init_terminal();
    init_snake(&snake, MAP_X + 20, MAP_Y + 5, DEFAULT_SNAKE_LENGTH);
    init_foods(foods);
    draw_window(MAP_X, MAP_Y, MAP_WIDTH, MAP_HEIGHT, COLOR_GREEN);
    draw_snake(&snake, &init_draw_flag);

    //fast game loop
    while(1)
    {
        current_direction = get_direction(current_direction);

        //main game loop, slowed down
        while (game_timer(&game_counter, MAX_GAME_COUNTER))
        {
            game_time++;

            erase_snake(&snake);
            move_snake(&snake, 1, 1, current_direction, VELOCITY);
            increase_snake(&snake, length);
            draw_snake(&snake, &init_draw_flag);
            food_logic(foods, &snake, &length, MAP_X, MAP_Y, MAP_WIDTH, MAP_HEIGHT);
            
            //TO DEBUG, show the length of the snake
            gotoxy(0, 0);
            printf("%d", length);

        }
    }
    return 0;
}