#ifndef PROCESSOR_H
#define PROCESSOR_H

// Include necessary standard libraries
#include <stdint.h>
#include <stdio.h>
#include <conio.h>

#include "../inc/utils.h"
#include "../inc/instructions.h"
//#include "../inc/instr_handler.h"

#define MEMORY_SIZE 0x0FFFFFFF // 512 MB for full addressable space

#define TEXT_BASE_ADDRESS 0x00000000

#define DATA_BASE_ADDRESS 0x10000000

#define STACK_BASE_ADDRESS 0x11000000


#define PROGRAM_1 "../instruction_memory/addlarge.bin"
#define PROGRAM_2 "../instruction_memory/test2.bin"
#define PROGRAM_3 "../instruction_memory/test3.bin"
#define PROGRAM_4 "../instruction_memory/i_types.bin"
#define PROGRAM_5 "../instruction_memory/I_R_types.bin"
#define PROGRAM_6 "../instruction_memory/memory_load.bin"
#define PROGRAM_7 "../instruction_memory/negatives_I_R.bin"

#define R_TYPE(opcode) ((opcode) == 0x33)
#define I_TYPE(opcode) ((opcode) == 0x13 || (opcode) == 0x3 || (opcode) == 0x23)
#define S_TYPE(opcode) ((opcode) == 0x23)
#define B_TYPE(opcode) ((opcode) == 0x63)
#define U_TYPE(opcode) ((opcode) == 0x37 || (opcode) == 0x17)
#define J_TYPE(opcode) ((opcode) == 0x6F)


typedef struct {
    int32_t pc;              // Program Counter
    int GPRs[32];         // 32 general-purpose registers
} CPU;

static inline void ensure_zero_register(CPU *cpu) {
    cpu->GPRs[0] = 0;
}

typedef struct {
    //int instr_memory[MEMORY_SIZE];     // Simplified memory (e.g., 4 KB)
    //int data_memory[MEMORY_SIZE];      // Simplified memory (e.g., 4 KB)
    //int memory[MEMORY_SIZE];      // Simplified memory (e.g., 4 KB)
    int *memory;
    size_t instr_count;             // Number of instructions in memory
} Memory;

typedef enum {
    R,
    I,
    S,
    B,
    U,
    J
} InstructionType;

typedef struct {
    int32_t raw_instr;
    int32_t opcode;    // Opcode (7 bits in RISC-V)
    int32_t rd;        // Destination register (5 bits)
    int32_t funct3;    // Function3 field (3 bits)
    int32_t rs1;       // Source register 1 (5 bits)
    int32_t rs2;       // Source register 2 (5 bits, if applicable)
    int32_t funct7;    // Function7 field (7 bits, if applicable)
    int32_t imm;        // Immediate value, if applicable
    InstructionType type;
    Instructions instr; //Actual instruction
} Instruction;


void RISC_V (char *filename);
void load_program(const char *filename, Memory *memory);
void fetch(CPU *cpu, Memory *memory, Instruction *instruction);
void decode(Instruction *instruction);
void write_information(CPU *cpu, Instruction *instruction);
void allocate_memory(Memory *memory);


#endif // PROCESSOR_H