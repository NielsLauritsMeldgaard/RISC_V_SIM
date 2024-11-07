#include <stdlib.h>
#include <stdio.h>

#include "../inc/food.h"
#include "../inc/snake.h"
#include "../inc/ANSI.h"

#define NUM_FOODS 3 // Hardcoded game constant, maybe to increase or decrease at some point

//count the number of active foods
int num_of_active_foods (Food *foods)
{
    int num = 0;
    for (int i = 0; i < NUM_FOODS; i++)
    {
        if (foods[i].flag == 1) 
            num++;
    }
    return num;
}

//erase the food from the screen by printing a space
void erase_food (Food *foods)
{
    for (int i = 0; i < NUM_FOODS; i++)
    {
        if (foods[i].flag == 1)
        {
            gotoxy(foods[i].x, foods[i].y);
            printf(" ");
        }
    }
}

//check if the snake collides with the food by checking the coordinates
void check_snake_food_collision (Food *foods, Snake *snake, int *length)
{
    for (int i = 0; i < NUM_FOODS; i++)
    {
        if (foods[i].flag == 1)
        {
            if (snake->head.x == foods[i].x && snake->head.y == foods[i].y)
            {
                foods[i].flag = 0;
                (*length)++;
                erase_food(foods);
            }
        }
    }
}

//draw the food on the screen by going to the coordinates and printing the food based on the type
void draw_food (Food *foods)
{
    for (int i = 0; i < NUM_FOODS; i++)
    {
        if (foods[i].flag == 1)
        {
            gotoxy(foods[i].x, foods[i].y);

            if (foods[i].type == STRAWBERRY) 
                printf("S");
            else if (foods[i].type == BANANNA) 
                printf("B");
        }
    }
}

//initialize the foods by setting the flag to 0
void init_foods (Food *foods)
{
    for (int i = 0; i < NUM_FOODS; i++)
    {
        foods[i].flag = 0;
        foods[i].x = 0;
        foods[i].y = 0;
        foods[i].type = STRAWBERRY;
    }
}

//food logic, check if there are enough foods, if not, place them randomly on the screen
void food_logic(Food *foods, Snake *snake, int *length, int map_x, int map_y, int map_width, int map_height)
{
    // Check if there are enough foods
    if (num_of_active_foods(foods) <= NUM_FOODS)
    {
        for (int i = 0; i < NUM_FOODS; i++)
        {
            if (foods[i].flag == 0)
            {
                // Ensure food is placed within the boundaries, avoiding the borders
                foods[i].x = (rand() % (map_width - 2)) + map_x + 1;
                foods[i].y = (rand() % (map_height - 2)) + map_y + 1;
                foods[i].flag = 1;
                if (rand() % 2 == 0) 
                {
                    foods[i].type = BANANNA;
                } 
                else 
                {
                    foods[i].type = STRAWBERRY;
                }
                // gotoxy(6, i + 5);
                // printf("x %d, y %d", foods[i].x, foods[i].y);
            }
        }
    }

    // Check if the snake eats the food
    check_snake_food_collision(foods, snake, length);
    draw_food(foods);
}