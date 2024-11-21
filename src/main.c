#include "../inc/processor.h"

int main() {
    RISC_V(PROGRAM_6);
    while(_getch() != 'q');
    return 0;
}