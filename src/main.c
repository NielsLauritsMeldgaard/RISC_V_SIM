#include "../inc/processor.h"

int main() {
    RISC_V("../instruction_memory/tests/task4/t12.bin", FALSE);
    while(_getch() != 'q');
    return 0;
}