#ifndef FOOD_H
#define FOOD_H

#include "snake.h"

enum FoodTypes
{
    STRAWBERRY,
    BANANNA
};

typedef struct
{
    int x;
    int y;
    int flag;
    enum FoodTypes type;
} Food;

int num_of_active_foods (Food *foods);
void erase_food (Food *foods);
void check_snake_food_collision (Food *foods, Snake *snake, int *length);
void draw_food (Food *foods);
void init_foods (Food *foods);
void food_logic (Food *foods, Snake *snake, int *length, int map_x, int map_y, int map_width, int map_height);

#endif // FOOD_H