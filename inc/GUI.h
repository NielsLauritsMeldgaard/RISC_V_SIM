#ifndef GUI_H
#define GUI_H

#include "../inc/processor.h"
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

void write_information(CPU *cpu, Instruction *instruction);
void draw_window (int X, int Y, int WIDTH, int HEIGHT, int COLOR_BLUE);
void gotoxy(int x, int y);
void set_text_color (int color_code);
void reset_text_color ();
void print_GRPS(CPU *cpu, Instruction *instruction);
void print_decode(Instruction *instruction);
void print_memory(Memory *memory);
void init_terminal ();


#endif // GUI_H
