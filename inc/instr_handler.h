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
    load_byte_unsigned,
    load_halfword_unsigned,
    store_word,
    store_halfword,
    store_byte,
    branch_equal,
    branch_not_equal,
    branch_less_than,
    branch_greater_than, //or eqaul
    branch_less_than_unsigned,
    branch_greater_than_unsigned, //or eqaul
    jump_and_link,
    jump_and_link_reg,
} Operations;

void execute(CPU *cpu, Memory *memory, Instruction *instruction);
void ALU (CPU *cpu, Operations operand, int32_t Op1, int32_t Op2, Instruction *instruction);
void load_memory(CPU *cpu, Operations operand, Instruction *instruction, Memory *memory);
void store_memory(CPU *cpu, Operations operand, Instruction *instruction, Memory *memory);
void branch_handler(CPU *cpu, Operations operand, Instruction *instruction);

 

#endif // INSTR_HANDLER_H