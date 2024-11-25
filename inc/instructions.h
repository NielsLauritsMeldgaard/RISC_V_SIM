#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H


typedef enum {
    ADD,
    SUB,
    XOR,
    OR,
    AND,
    SLL,
    SRL,
    SRA,
    SLT,
    SLTU,
    ADDI,
    XORI,
    ORI,
    ANDI,
    SLLI,
    SRLI,
    SRAI,
    SLTI,
    SLTIU,
    LB,
    LH,
    LW,
    LBU,
    LHU,
    SB,
    SH,
    SW,
    LUI,
    AUIPC,
    BEQ,
    BNE,
    BLT,
    BGE,
    BLTU,
    BGEU,
    NUM_INSTRUCTIONS
} Instructions;

#include "../inc/processor.h"




#endif // INSTRUCTIONS_H