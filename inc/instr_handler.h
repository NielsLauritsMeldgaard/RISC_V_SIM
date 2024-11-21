#ifndef INSTR_HANDLER_H
#define INSTR_HANDLER_H

#include "../inc/processor.h"

typedef enum {
    addition,
    subtraction,
    shift_left_logical,
    shift_right_logical,
    shift_right_arithmetic,
    bitwise_and,
    bitwise_or,
    bitwise_xor,
    set_less_than,
    set_less_than_unsigned,
    load_word,
    load_halfword,
    load_byte,
} Operations;

void execute(CPU *cpu, Memory *memory, Instruction *instruction);
void ALU (CPU *cpu, Operations operand, int32_t Op1, int32_t Op2, Instruction *instruction);
void load_data_memory(CPU *cpu, Operations operand, Instruction *instruction, Memory *memory);

 

#endif // INSTR_HANDLER_H