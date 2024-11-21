#include "../inc/instr_handler.h"

//int32_t ALU(int32_t Op1, int32_t Op2, CPU *cpu)

void execute(CPU *cpu, Memory *memory, Instruction *instruction) 
{
    // Determine the instruction type based on the opcode
    switch (instruction->opcode) {
        case 0x33: // R-type
            instruction->type = R;
            switch (instruction->funct3) {
                case 0x0:
                    instruction->instr = (instruction->funct7 == 0x00) ? ADD : SUB;
                    if(instruction->instr == ADD) {
                        ALU(cpu, addition, cpu->GPRs[instruction->rs1], cpu->GPRs[instruction->rs2], instruction);
                    }
                    else{
                        ALU(cpu, subtraction, cpu->GPRs[instruction->rs1], cpu->GPRs[instruction->rs2], instruction);
                    }
                    break;
                case 0x4:
                    instruction->instr = XOR;
                    ALU(cpu, bitwise_xor, cpu->GPRs[instruction->rs1], cpu->GPRs[instruction->rs2], instruction);
                    break;
                case 0x6:
                    instruction->instr = OR;
                    ALU(cpu, bitwise_or, cpu->GPRs[instruction->rs1], cpu->GPRs[instruction->rs2], instruction);
                    break;
                case 0x7:
                    instruction->instr = AND;
                    ALU(cpu, bitwise_and, cpu->GPRs[instruction->rs1], cpu->GPRs[instruction->rs2], instruction);
                    break;
                case 0x1:
                    instruction->instr = SLL;
                    ALU(cpu, shift_left_logical, cpu->GPRs[instruction->rs1], cpu->GPRs[instruction->rs2], instruction);
                    break;
                case 0x5:
                    instruction->instr = (instruction->funct7 == 0x00) ? SRL : SRA;
                    if(instruction->instr == SRL) {
                        ALU(cpu, shift_right_logical, cpu->GPRs[instruction->rs1], cpu->GPRs[instruction->rs2], instruction);
                    }
                    else{
                        ALU(cpu, shift_right_arithmetic, cpu->GPRs[instruction->rs1], cpu->GPRs[instruction->rs2], instruction);
                    }
                    break;
                case 0x2:
                    instruction->instr = SLT;
                    ALU(cpu, set_less_than, cpu->GPRs[instruction->rs1], cpu->GPRs[instruction->rs2], instruction);
                    break;
                case 0x3:
                    instruction->instr = SLTU;
                    ALU(cpu, set_less_than_unsigned, cpu->GPRs[instruction->rs1], cpu->GPRs[instruction->rs2], instruction);
                    break;

                default:
                    instruction->instr = NUM_INSTRUCTIONS; // Invalid instruction
                    break;
        }
        break;            
        
        
        case 0x13: // I-type, normla
            instruction->type = I;
            switch (instruction->funct3) {
                case 0x0:
                    instruction->instr = ADDI;
                    ALU(cpu, addition, cpu->GPRs[instruction->rs1], instruction->imm, instruction);
                    break;
                case 0x4:
                    instruction->instr = XORI;
                    ALU(cpu, bitwise_xor, cpu->GPRs[instruction->rs1], instruction->imm, instruction);
                    break;
                case 0x6:
                    instruction->instr = ORI;
                    ALU(cpu, bitwise_or, cpu->GPRs[instruction->rs1], instruction->imm, instruction);
                    break;
                case 0x7:
                    instruction->instr = ANDI;
                    ALU(cpu, bitwise_and, cpu->GPRs[instruction->rs1], instruction->imm, instruction);
                    break;
                case 0x1:
                    instruction->instr = SLLI;
                    ALU(cpu, shift_left_logical, cpu->GPRs[instruction->rs1], instruction->imm, instruction);
                    break;
                case 0x5:
                    instruction->instr = (instruction->funct7 == 0x00) ? SRLI : SRAI;
                    if(instruction->instr == SRLI) {
                        ALU(cpu, shift_right_logical, cpu->GPRs[instruction->rs1], instruction->imm, instruction);
                    }
                    else{
                        ALU(cpu, shift_right_arithmetic, cpu->GPRs[instruction->rs1], instruction->imm, instruction);
                    }
                    break;
                case 0x2:
                    instruction->instr = SLTI;
                    ALU(cpu, set_less_than, cpu->GPRs[instruction->rs1], instruction->imm, instruction);
                    break;
                case 0x3:
                    instruction->instr = SLTIU;
                    ALU(cpu, set_less_than_unsigned, cpu->GPRs[instruction->rs1], instruction->imm, instruction);
                    break;
                default:
                    instruction->instr = NUM_INSTRUCTIONS; // Invalid instruction
                    break;
            }
            break;


        case 0x03: // I-type, load
            instruction->type = I;
            
            switch(instruction->funct3) {
                case 0x0:
                    instruction->instr = LB;
                    load_data_memory(cpu, load_byte, instruction, memory);
                    break;
                case 0x1:
                    instruction->instr = LH;
                    load_data_memory(cpu, load_halfword, instruction, memory);
                    break;
                case 0x2:
                    instruction->instr = LW;
                    load_data_memory(cpu, load_word, instruction, memory);
                    break;
                case 0x4:
                    instruction->instr = LBU;
                    break;
                case 0x5:
                    instruction->instr = LHU;
                    break;
                default:
                    instruction->instr = NUM_INSTRUCTIONS; // Invalid instruction
                    break;
            }
            break;

        case 0x23: // S-type
            instruction->type = S;
            switch(instruction->funct3) {
                case 0x0:
                    instruction->instr = SB;
                    break;
                case 0x1:
                    instruction->instr = SH;
                    break;
                case 0x2:
                    instruction->instr = SW;
                    break;
                default:
                    instruction->instr = NUM_INSTRUCTIONS; // Invalid instruction
                    break;
            }
            break;



        //MORE TYPES TO BE ADDED

        default:
            instruction->instr = NUM_INSTRUCTIONS; // Invalid instruction
            break;
    }

    // printf("Decoded instruction: opcode=0x%02x, rd=%d, funct3=0x%02x, rs1=%d, rs2=%d, funct7=0x%02x\n",
    //        instruction->opcode, instruction->rd, instruction->funct3, instruction->rs1, instruction->rs2, instruction->funct7);
    // printf("Instruction type: %d\n", instruction->type);

    return;
}

void ALU (CPU *cpu, Operations operand, int32_t Op1, int32_t Op2, Instruction *instruction)
{
    switch (operand)
    {
        case addition:
            cpu->GPRs[instruction->rd] = Op1 + Op2;
            break;
        case subtraction:
            cpu->GPRs[instruction->rd] = Op1 - Op2;
            break;
        case shift_left_logical:
            cpu->GPRs[instruction->rd] = Op1 << Op2;
            break;
        case shift_right_logical:
            cpu->GPRs[instruction->rd] = (int32_t)Op1 >> Op2;
            break;
        case shift_right_arithmetic:
            cpu->GPRs[instruction->rd] = Op1 >> Op2;
            break;
        case bitwise_and:
            cpu->GPRs[instruction->rd] = Op1 & Op2;
            break;
        case bitwise_or:
            cpu->GPRs[instruction->rd] = Op1 | Op2;
            break;
        case bitwise_xor:
            cpu->GPRs[instruction->rd] = Op1 ^ Op2;
            break;
        case set_less_than:
            cpu->GPRs[instruction->rd] = (Op1 < Op2) ? 1 : 0;
            break;
        case set_less_than_unsigned:
            cpu->GPRs[instruction->rd] = ((uint32_t)Op1 < (uint32_t)Op2) ? 1 : 0;
            break;
        default:
            break;
    }

}



void load_data_memory(CPU *cpu, Operations operand, Instruction *instruction, Memory *memory) {
    int32_t byte; 
    int32_t halfword; 
    instruction->imm = 4; // For testing purposes

    int32_t offset = instruction->imm / 4;
    int32_t effective_adress = ((cpu->GPRs[instruction->rs1])  + offset);
    int32_t mem_word = memory->memory[effective_adress];

    switch (operand) {
        case load_word:
            cpu->GPRs[instruction->rd] = mem_word;
            break;
        case load_halfword:
            halfword = (int32_t)(mem_word >> 16); // Get the upper halfword
            cpu->GPRs[instruction->rd] = halfword;
            break;
        case load_byte:
            byte = (int32_t)(mem_word >> 24); // Get the upper byte
            cpu->GPRs[instruction->rd] = byte;
            break;
        default:
            break;
    }
}




