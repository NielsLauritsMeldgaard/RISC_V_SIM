#include <stdio.h>
#include <conio.h> //non c-standard librarys :(

#include "../inc/game.h"

// Get the direction from the user input by checking the keyboard buffer
enum Direction get_direction (enum Direction current_direction)
{
    if (_kbhit()) 
    {
        char c = _getch();
        enum Direction new_direction = IDLE;
        switch (c) 
        {
            case 'w': new_direction = UP; break;
            case 's': new_direction = DOWN; break;
            case 'a': new_direction = LEFT; break;
            case 'd': new_direction = RIGHT; break;
            default: break;
        }

        if (new_direction != current_direction) {
            current_direction = new_direction;
        }
    }
    return current_direction;
}

int game_timer(int *game_counter, int max_game_counter)
{
    (*game_counter)++;
    if ((*game_counter) >= max_game_counter) 
    {
        (*game_counter) = 0; 
        return 1;
    }
    else
        return 0;
}