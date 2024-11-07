#include <stdio.h>

// Clears the terminal screen
void clear_screen () 
{
    printf("\033[2J");
}

// Hides the cursor
void hide_cursor () 
{
    printf("\033[?25l");
}

// Shows the cursor
void show_cursor () 
{
    printf("\033[?25h");
}

// Moves the cursor to the top-left corner
void move_cursor_to_top_left () 
{
    printf("\033[H");
}


// Sets text color based on the color code
void set_text_color (int color_code) 
{
    printf("\033[%dm", color_code);
}

// Resets the text color
void reset_text_color () 
{
    printf("\033[0m");
}

// Moves the cursor to the specified position
void gotoxy (int x, int y) {
    printf("\033[%d;%dH", y, x);
}

// Initializes the terminal
void init_terminal ()
{
    hide_cursor();
    clear_screen();
    reset_text_color();
}

// Draws a window with the specified position, width, height, and color
void draw_window (int x, int y, int width, int height, int color)
{
    set_text_color(color);
    //draw top left corner
    gotoxy(x, y);
    printf("%c", 201);

    //draw top
    int i;
    for (i = 1; i < width; i++)
    {
        gotoxy(x + i, y);
        printf("%c", 205);
    }

    //draw top right corner
    gotoxy(x + width, y);
    printf("%c", 187);

    //draw right side
    for (i = 1; i < height; i++)
    {
        gotoxy(x + width, y + i);
        printf("%c", 186);
    }

    //draw bottom right corner
    gotoxy(x + width, y + height);
    printf("%c", 188);

    //draw bottom
    for (i = 1; i < width; i++)
    {
        gotoxy(x + i, y + height);
        printf("%c", 205);
    }

    //draw bottom left corner
    gotoxy(x, y + height);
    printf("%c", 200);

    //draw left side
    for (i = 1; i < height; i++)
    {
        gotoxy(x, y + i);
        printf("%c", 186);
    }
    reset_text_color();
}