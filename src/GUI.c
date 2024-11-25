#include "../inc/GUI.h"

#define X 3
#define Y 3
#define WIDTH 55
#define HEIGHT 25

#define X_2 60
#define Y_2 3
#define WIDTH_2 20
#define HEIGHT_2 25

#define X_3 82
#define Y_3 3
#define WIDTH_3 38
#define HEIGHT_3 25

int window_drawn = 0;
 
void write_information(CPU *cpu, Instruction *instruction) {
    if (!window_drawn) {
        window_drawn = 1;
        draw_window (X, Y, WIDTH, HEIGHT, COLOR_BLUE);
        draw_window (X_2, Y_2, WIDTH_2, HEIGHT_2, COLOR_GREEN);
        draw_window (X_3, Y_3, WIDTH_3, HEIGHT_3, COLOR_YELLOW);
    }

    print_GRPS(cpu, instruction);
    print_decode(instruction);

    set_text_color(COLOR_YELLOW);
    gotoxy(X_3 + 9, Y_3);
    printf("PRESS 'SPACE' TO STEP");
    gotoxy((X_3 + 13), Y_3 + 1);
    printf("PC: 0x%08x", cpu->pc - 4);
    gotoxy((X_3 + 13), Y_3 + 2);
    printf("CYCLES: %d", cpu->cycles);
    reset_text_color();


    set_text_color(COLOR_GREEN);
    gotoxy(X_2 + 6, Y_2);
    printf("DECODE");
    reset_text_color();

    set_text_color(COLOR_BLUE);
    gotoxy(X + 6, Y);
    printf("REGISTERS");
    reset_text_color();

    return;
}


void print_memory(Memory *memory) {
    gotoxy(X_3 + 2, Y_3 + 3);
    printf(".TEXT MEMORY:");

    gotoxy(X_3 + 2, Y_3 + 10);
    printf(".DATA MEMORY:");

    gotoxy(X_3 + 2, Y_3 + 17);
    printf(".BSS MEMORY:");

    for(int i = 0; i < 5; i++) {
        gotoxy(X_3 + 7, Y_3 + 4 + i);
        printf("@0x%08x:  0x", i * 4);
        for (int j = 3; j >= 0; j--) {
            printf("%02x", memory->byte[(i * 4) + j]);
        }        
    }

    //HARDCODED ADRESS FOR NOW
    for(int i = 0; i < 5; i++) {
        gotoxy(X_3 + 7, Y_3 + 11 + i);
        printf("@0x100000%02x:  0x", i * 4);
        for (int j = 0; j < 4; j++) {
            printf("%02x", memory->byte[(i * 4) + j + DATA_BASE_ADDRESS]);
        }
    }

    //HARDCODED ADRESS FOR NOW
    for(int i = 5; i >= 0; i--) {
        gotoxy(X_3 + 7, Y_3 + 18 + i);
        printf("@0x%08x:  0x", STACK_BASE_ADDRESS - (i * 4));
        for (int j = 0; j < 4; j++) {
            printf("%02x", memory->byte[(i * 4) + j + STACK_BASE_ADDRESS]);
        }
    }

    return;
}

void print_decode(Instruction *instruction) {
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
        set_text_color(COLOR_RED);
        printf("FMT: B\n");
        reset_text_color();
    } else if (instruction->type == U) {
        printf("FMT: U\n");
    } else if (instruction->type == J) {
        printf("FMT: J\n");
    } else {
        printf("FMT: Invalid\n");
    }

    return;
}


void print_GRPS(CPU *cpu, Instruction *instruction) {
    //First Collumn
    gotoxy(X + 2, Y + 1);
    for(int i = 0; i < 25; i++) {
        if (i == instruction->rd) {
            if (instruction->type != B)
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
            if (instruction->type != B)
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
