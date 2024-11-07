#ifndef ANSI_H_
#define ANSI_H_

void clear_screen ();
void hide_cursor ();
void show_cursor (); 
void move_cursor_to_top_left ();
void set_text_color (int color_code);
void reset_text_color (); 
void gotoxy (int x, int y);
void init_terminal ();
void draw_window (int x, int y, int width, int height, int color);

// Color codes for terminal manipulation
enum 
{
    COLOR_RESET = 0,
    COLOR_RED = 31,
    COLOR_GREEN = 32,
    COLOR_YELLOW = 33,
    COLOR_BLUE = 34,
    COLOR_MAGENTA = 35,
    COLOR_CYAN = 36,
    COLOR_WHITE = 37
};

#endif // ANSI_H_