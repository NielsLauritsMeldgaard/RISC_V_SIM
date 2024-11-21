#include "../inc/GUI.h"

#define X 3
#define Y 3
#define WIDTH 55
#define HEIGHT 25

#define X_2 60
#define Y_2 3
#define WIDTH_2 20
#define HEIGHT_2 25

int window_drawn = 0;
 
void write_information(CPU *cpu, Instruction *instruction) {
    if (!window_drawn) {
        window_drawn = 1;
        draw_window (X, Y, WIDTH, HEIGHT, COLOR_BLUE);
        draw_window (X_2, Y_2, WIDTH_2, HEIGHT_2, COLOR_GREEN);
    }

    write_GRPS(cpu, instruction);
    write_decode(instruction);

    set_text_color(COLOR_YELLOW);
    gotoxy((X_2 + 32), Y_2 + 8);
    printf("PRESS 'SPACE' TO STEP");
    gotoxy((X_2 + 36), Y_2 + 10);
    printf("PC: 0x%08x", cpu->pc);
    reset_text_color();
    // printf("Instruction: %d\n", instruction->instr);
    // printf("GR[%d] = %d\n", instruction->rd, cpu->GPRs[instruction->rd]);

    // gotoxy(X_2 + WIDTH_2 + 2, Y_2);
    // printf("First ten instructions in memory:");
    // for(int i = 0; i < 10; i++) {
    //     gotoxy(X_2 + WIDTH_2 + 2, Y_2 + 1 + i);
    //     printf("0x%08x", memory->instr_memory[i]);
    // }
    //printf("Program Counter: 0x%08x", cpu->pc);

    return;
}

void write_decode(Instruction *instruction) {
    gotoxy((X_2 + 2), Y + 1);
    printf("Raw instruction:");
    gotoxy((X_2 + 2), Y_2 + 2);
    printf("0x%08x", instruction->raw_instr);
    gotoxy((X_2 + 2), Y_2 + 4);
    printf("Opcode: 0x%02x\n", instruction->opcode);
    gotoxy((X_2 + 2), Y_2 + 6);
    printf("rd: %d\n", instruction->rd);
    gotoxy((X_2 + 2), Y_2 + 8);
    printf("funct3: 0x%02x\n", instruction->funct3);
    gotoxy((X_2 + 2), Y_2 + 10);
    printf("rs1: %d\n", instruction->rs1);
    gotoxy((X_2 + 2), Y_2 + 12);
    printf("rs2: %d\n", instruction->rs2);
    gotoxy((X_2 + 2), Y_2 + 14);
    printf("funct7: 0x%02x\n", instruction->funct7);
    gotoxy((X_2 + 2), Y_2 + 16);
    if (instruction->type == R) {
        printf("FMT: R\n");
    } else if (instruction->type == I) {
        printf("FMT: I\n");
    } else if (instruction->type == S) {
        printf("FMT: S\n");
    } else if (instruction->type == B) {
        printf("FMT: B\n");
    } else if (instruction->type == U) {
        printf("FMT: U\n");
    } else if (instruction->type == J) {
        printf("FMT: J\n");
    } else {
        printf("FMT: Invalid\n");
    }

    return;
}


void write_GRPS(CPU *cpu, Instruction *instruction) {
    //First Collumn
    gotoxy(X + 2, Y + 1);
    for(int i = 0; i < 25; i++) {
        if (i == instruction->rd) {
            set_text_color(COLOR_RED);
            printf("X[%02d]    =    0x%08x\n", i, cpu->GPRs[i]);
            gotoxy(X + 2, (Y + 1) + i);
            reset_text_color();
        } else {
            printf("X[%02d]    =    0x%08x\n", i, cpu->GPRs[i]);
            gotoxy(X + 2, (Y + 1) + i);
        }

    }

    //Second Collumn
    gotoxy((X + 2) + 28, Y + 1);
    for(int i = 0; i < 7; i++) {
        if(i + 25 == instruction->rd) {
            set_text_color(COLOR_RED);
            printf("X[%02d]    =    0x%08x\n", i + 25, cpu->GPRs[i + 25]);
            gotoxy((X + 2) + 28, (Y + 1) + i);
            reset_text_color();
        } else {
            printf("X[%02d]    =    0x%08x\n", i + 25, cpu->GPRs[i + 25]);
            gotoxy((X + 2) + 28, (Y + 1) + i);
        }

    }

    return;
}

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
