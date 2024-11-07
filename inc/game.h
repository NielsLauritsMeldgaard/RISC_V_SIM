#ifndef GAME_H
#define GAME_H

enum Direction
{
    IDLE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum Direction get_direction(enum Direction current_direction);
int game_timer (int *game_counter, int max_game_counter);

#endif // GAME_H