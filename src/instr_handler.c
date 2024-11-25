#include "../inc/instr_handler.h"
#include "../inc/GUI.h"


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
        
        
        case 0x13: // I-type, normal
            instruction->type = I;

            // I-type Immediate
            instruction->imm_I = (int32_t)((instruction->raw_instr >> 20) & 0xFFF);
            if (instruction->imm_I & 0x800) { // Sign extension for 12-bit immediate
                instruction->imm_I |= (int32_t)0xFFFFF000;
            }


            switch (instruction->funct3) {
                case 0x0:
                    instruction->instr = ADDI;
                    ALU(cpu, addition, cpu->GPRs[instruction->rs1], instruction->imm_I, instruction);
                    break;
                case 0x4:
                    instruction->instr = XORI;
                    ALU(cpu, bitwise_xor, cpu->GPRs[instruction->rs1], instruction->imm_I, instruction);
                    break;
                case 0x6:
                    instruction->instr = ORI;
                    ALU(cpu, bitwise_or, cpu->GPRs[instruction->rs1], instruction->imm_I, instruction);
                    break;
                case 0x7:
                    instruction->instr = ANDI;
                    ALU(cpu, bitwise_and, cpu->GPRs[instruction->rs1], instruction->imm_I, instruction);
                    break;
                case 0x1:
                    instruction->instr = SLLI;
                    ALU(cpu, shift_left_logical, cpu->GPRs[instruction->rs1], instruction->imm_I, instruction);
                    break;
                case 0x5:
                    instruction->instr = (instruction->funct7 == 0x00) ? SRLI : SRAI;
                    if(instruction->instr == SRLI) {
                        ALU(cpu, shift_right_logical, cpu->GPRs[instruction->rs1], instruction->imm_I, instruction);
                    }
                    else{
                        ALU(cpu, shift_right_arithmetic, cpu->GPRs[instruction->rs1], instruction->imm_I, instruction);
                    }
                    break;
                case 0x2:
                    instruction->instr = SLTI;
                    ALU(cpu, set_less_than, cpu->GPRs[instruction->rs1], instruction->imm_I, instruction);
                    break;
                case 0x3:
                    instruction->instr = SLTIU;
                    ALU(cpu, set_less_than_unsigned, cpu->GPRs[instruction->rs1], instruction->imm_I, instruction);
                    break;
                default:
                    instruction->instr = NUM_INSTRUCTIONS; // Invalid instruction
                    break;
            }
            break;


        case 0x03: // I-type, load
            instruction->type = I;

            // I-type Immediate
            instruction->imm_I = (int32_t)(instruction->raw_instr >> 20 & 0xFFF);
            if (instruction->imm_I & 0x800) { // Sign extension for 12-bit immediate
                instruction->imm_I |= (int32_t)0xFFFFF000;
            }
            
            switch(instruction->funct3) {
                case 0x0:
                    instruction->instr = LB;
                    load_memory(cpu, load_byte, instruction, memory);
                    break;
                case 0x1:
                    instruction->instr = LH;
                    load_memory(cpu, load_halfword, instruction, memory);
                    break;
                case 0x2:
                    instruction->instr = LW;
                    load_memory(cpu, load_word, instruction, memory);
                    break;
                case 0x4:
                    instruction->instr = LBU;
                    load_memory(cpu, load_byte_unsigned, instruction, memory);
                    break;
                case 0x5:
                    instruction->instr = LHU;
                    load_memory(cpu, load_halfword_unsigned, instruction, memory);
                    break;
                default:
                    instruction->instr = NUM_INSTRUCTIONS; // Invalid instruction
                    break;
            }
            break;

        case 0x23: // S-type
            instruction->type = S;

             // S-type Immediate
            instruction->imm_S = (int32_t)(((instruction->raw_instr >> 25) << 5) | ((instruction->raw_instr >> 7) & 0x1F));
            if (instruction->imm_S & 0x800) { // Sign extension for 12-bit immediate
                instruction->imm_S |= (int32_t)0xFFFFF000;
            }


            switch(instruction->funct3) {
                case 0x0:
                    instruction->instr = SB;
                    store_memory(cpu, store_byte, instruction, memory);
                    break;
                case 0x1:
                    instruction->instr = SH; 
                    store_memory(cpu, store_halfword, instruction, memory);
                    break;
                case 0x2:
                    instruction->instr = SW;
                    store_memory(cpu, store_word, instruction, memory);
                    break;
                default:
                    instruction->instr = NUM_INSTRUCTIONS; // Invalid instruction
                    break;
            }
            break;
        
        case 0x37: // U-type
            instruction->type = U;
            instruction->instr = LUI;

            // U-type Immediate
            instruction->imm_U = (int32_t)(instruction->raw_instr >> 12 & 0xFFFFF);  // Mask to ensure it's 20 bits  

            cpu->GPRs[instruction->rd] = instruction->imm_U << 12;
            cpu->pc += 4;
            break;
        
        case 0x17: // U-type
            instruction->type = U;
            instruction->instr = AUIPC;

            // U-type Immediate
            instruction->imm_U = (int32_t)(instruction->raw_instr >> 12) & 0xFFFFF;  // Mask to ensure it's 20 bits  

            cpu->GPRs[instruction->rd] = cpu->pc + (instruction->imm_U << 12);
            cpu->pc += 4;
            break;

        case 0x63: // B-type
            instruction->type = B;

            // B-type Immediate
            instruction->imm_B = (int32_t)(((instruction->raw_instr >> 31) << 12) | // Bit 12 (sign bit)
                                ((instruction->raw_instr >> 25) & 0x3F) << 5 | // Bits 10 to 5
                                ((instruction->raw_instr >> 8) & 0xF) << 1 | // Bits 4 to 1
                                ((instruction->raw_instr >> 7) & 0x1) << 11); // Bit 11
            if (instruction->imm_B & 0x1000) { // Sign extension for 13-bit immediate
                instruction->imm_B |= (int32_t)0xFFFFE000;
            }

            switch (instruction->funct3) {
                case 0x0:
                    instruction->instr = BEQ;
                    branch_handler(cpu, branch_equal, instruction);
                    break;
                case 0x1:
                    instruction->instr = BNE;
                    branch_handler(cpu, branch_not_equal, instruction);
                    break;
                case 0x4:
                    instruction->instr = BLT;
                    branch_handler(cpu, branch_less_than, instruction);
                    break;
                case 0x5:
                    instruction->instr = BGE;
                    branch_handler(cpu, branch_greater_than, instruction);
                    break;
                case 0x6:
                    instruction->instr = BLTU;
                    branch_handler(cpu, branch_less_than_unsigned, instruction);
                    break;
                case 0x7:
                    instruction->instr = BGEU;
                    branch_handler(cpu, branch_greater_than_unsigned, instruction);
                    break;
                default:
                    instruction->instr = NUM_INSTRUCTIONS; // Invalid instruction
                    break;
            }
            break;


        case 0x6F: // J-type
            instruction->type = J;
            //instruction->instr = jump_and_link;

            // J-type Immediate
            instruction->imm_J = (int32_t)(((instruction->raw_instr >> 31) << 20) | // Bit 20 (sign bit)
                            ((instruction->raw_instr >> 21) & 0x3FF) << 1 | // Bits 10-1
                            ((instruction->raw_instr >> 20) & 0x1) << 11 | // Bit 11
                            ((instruction->raw_instr >> 12) & 0xFF) << 12); // Bits 19-12

            // Sign extension for 21-bit immediate
            if (instruction->imm_J & 0x100000) {
                instruction->imm_J |= (int32_t)0xFFE00000;
            } 


            if (instruction->rd != 0) {
                cpu->GPRs[instruction->rd] = cpu->pc + 4;
            }
            cpu->pc += instruction->imm_J;
            break;


        case 0x67: // I-type, jump and link register
            instruction->type = I;

            // I-type Immediate
            instruction->imm_I = (int32_t)(instruction->raw_instr >> 20) & 0xFFF;
            if (instruction->imm_I & 0x800) { // Sign extension for 12-bit immediate
                instruction->imm_I |= (int32_t)0xFFFFF000;
            }

            if (instruction->rd != 0) {
                cpu->GPRs[instruction->rd] = cpu->pc + 4;
            }
            cpu->pc = (cpu->GPRs[instruction->rs1] + instruction->imm_I) & ~1; // Ensure pc is aligned

            break;

        case 0x73:
        
            if(!cpu->step) {
                write_information(cpu, instruction);
                print_memory(memory);
            }

            free(memory->byte);
            while(_getch() != 'q');
            quick_exit(0);
            break;

        default:
            instruction->instr = NUM_INSTRUCTIONS; // Invalid instruction
            break;
    }

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
            cpu->GPRs[instruction->rd] = (int32_t)((uint32_t)Op1 >> (Op2 & 0x1F));
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
            fprintf(stderr, "Error: Unknown store operation\n");
            break;
    }

    cpu->pc += 4;
    return;

    
}



void load_memory(CPU *cpu, Operations operand, Instruction *instruction, Memory *memory) {
    int32_t byte; 
    int32_t halfword; 

    int32_t offset = instruction->imm_I;
    int32_t effective_address = ((cpu->GPRs[instruction->rs1])  + offset);
    int32_t mem_word =  ((uint32_t)memory->byte[effective_address]       << 0)  |
                        ((uint32_t)memory->byte[effective_address + 1]   << 8)  |
                        ((uint32_t)memory->byte[effective_address + 2]   << 16) |
                        ((uint32_t)memory->byte[effective_address + 3]   << 24);


    switch (operand) {
        int8_t bytes;
        uint8_t byte_unsigned;
        int16_t halfwords;
        uint16_t halfword_unsigned;


        case load_word:
            cpu->GPRs[instruction->rd] = mem_word; // Load full 32-bit word
            break;

        case load_halfword:
            // Extract two bytes, sign-extend to 32 bits
            halfwords = (int16_t)((memory->byte[effective_address]) |
                                         (memory->byte[effective_address + 1] << 8));
            cpu->GPRs[instruction->rd] = halfwords;
            break;

        case load_halfword_unsigned:
            // Extract two bytes, zero-extend to 32 bits
            halfword_unsigned = (uint16_t)((memory->byte[effective_address]) |
                                                    (memory->byte[effective_address + 1] << 8));
            cpu->GPRs[instruction->rd] = halfword_unsigned;
            break;

        case load_byte:
            // Load single byte and sign-extend to 32 bits
            bytes = (int8_t)memory->byte[effective_address];
            cpu->GPRs[instruction->rd] = bytes;
            break;

        case load_byte_unsigned:
            // Load single byte and zero-extend to 32 bits
            byte_unsigned = (uint8_t)memory->byte[effective_address];
            cpu->GPRs[instruction->rd] = byte_unsigned;
            break;        
        default:
            fprintf(stderr, "Error: Unknown store operation\n");
            break;
    }

    cpu->pc += 4;

    return;
}


void store_memory(CPU *cpu, Operations operand, Instruction *instruction, Memory *memory) {
    int32_t offset = instruction->imm_S;
    int32_t effective_address = cpu->GPRs[instruction->rs1] + offset;
    int32_t GPR_word = cpu->GPRs[instruction->rs2];

    switch (operand) {
        case store_word:
            // Store the word in memory
            memory->byte[effective_address] = (uint8_t)(GPR_word >> 0);
            memory->byte[effective_address + 1] = (uint8_t)(GPR_word >> 8);
            memory->byte[effective_address + 2] = (uint8_t)(GPR_word >> 16);
            memory->byte[effective_address + 3] = (uint8_t)(GPR_word >> 24);
            break;
        case store_halfword:
            // Store the halfword in memory
            memory->byte[effective_address] = (uint8_t)(GPR_word >> 0);
            memory->byte[effective_address + 1] = (uint8_t)(GPR_word >> 8);
            break;
        case store_byte:
            // Store the byte in memory
            memory->byte[effective_address] = (uint8_t)(GPR_word >> 0);
            break;
        default:
            fprintf(stderr, "Error: Unknown store operation\n");
            break;
    }

    cpu->pc += 4;

    return;
}

void branch_handler(CPU *cpu, Operations operand, Instruction *instruction) {
    int32_t offset = instruction->imm_B;
    switch (operand) {
        case branch_equal:
            if (cpu->GPRs[instruction->rs1] == cpu->GPRs[instruction->rs2]) {
                cpu->pc += offset;
            }
            else {
                cpu->pc += 4;
            }
            break;
        case branch_not_equal:
            if (cpu->GPRs[instruction->rs1] != cpu->GPRs[instruction->rs2]) {
                cpu->pc += offset;
            }
            else {
                cpu->pc += 4;
            }
            break;
        case branch_less_than:
            if (cpu->GPRs[instruction->rs1] < cpu->GPRs[instruction->rs2]) {
                cpu->pc += offset;
            }
            else {
                cpu->pc += 4;
            }
            break;
        case branch_greater_than:
            if (cpu->GPRs[instruction->rs1] >= cpu->GPRs[instruction->rs2]) {
                cpu->pc += offset;
            }
            else {
                cpu->pc += 4;
            }
            break;
        case branch_less_than_unsigned:
            if ((uint32_t)cpu->GPRs[instruction->rs1] < (uint32_t)cpu->GPRs[instruction->rs2]) {
                cpu->pc += offset;
            }
            else {
                cpu->pc += 4;
            }
            break;
        case branch_greater_than_unsigned:
            if ((uint32_t)cpu->GPRs[instruction->rs1] >= (uint32_t)cpu->GPRs[instruction->rs2]) {
                cpu->pc += offset;
            }
            else {
                cpu->pc += 4;
            }
            break;
        default:
            fprintf(stderr, "Error: Unknown branch operation\n");
            break;
    }

    return;
}






