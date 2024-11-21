#include "../inc/processor.h"
#include "../inc/instr_handler.h"
#include "../inc/GUI.h"


void RISC_V(char *filename) {
    CPU cpu = { .pc = 0, .GPRs = {0} };
    //Memory memory = { .memory = {0}, .instr_count = 0 };
    Memory memory;
    Instruction instruction = { 0 };

    allocate_memory(&memory);

    //int adress = &memory.memory;
    memory.memory[DATA_BASE_ADDRESS + 1] = (int32_t)0x0a0a0a0a;
    cpu.GPRs[5] = DATA_BASE_ADDRESS;

    // Load program into memory
    load_program(filename, &memory);
    while(cpu.pc <= (int)(memory.instr_count * 4)) {
        fetch(&cpu, &memory, &instruction);
        decode(&instruction);
        execute(&cpu, &memory, &instruction);
        write_information(&cpu, &instruction);

        // Wait for space key press
        int ch;
        do {
            ch = _getch();
        } while (ch != ' ');

        cpu.pc += 4;

    }
    
    free(memory.memory);

    return;
}

void allocate_memory(Memory *memory) {
    memory->memory = (int *)malloc(MEMORY_SIZE * sizeof(int));
    if (memory->memory == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    return;
}


void fetch(CPU *cpu, Memory *memory, Instruction *instruction) {
    // Fetch instruction from memory
    instruction->raw_instr = memory->memory[cpu->pc / 4];
    //printf("Raw instruction fetched: 0x%08x\n", instruction->raw_instr);
    return;
}


void load_program(const char *filename, Memory *memory) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return;
    }

    // Read the file into memory
    size_t instructions_read = fread(memory->memory, sizeof(uint32_t), MEMORY_SIZE, file);
    fclose(file);
    printf("Program loaded into memory\n");
    printf("Instructions read: %zu\n", instructions_read);
    memory->instr_count = instructions_read;
    // printf("Instruction: 0x%08x\n", memory->instr_memory[1]);

    //Print instructions to verify content
    // for (int i = 0; i < (int)instructions_read; i++) {
    //     printf("Instruction %d: 0x%08x\n", i, memory->memory[i]);
    // }
    return;
}

void decode(Instruction *instruction) {
    instruction->opcode = instruction->raw_instr & 0x7F;
    instruction->rd = (instruction->raw_instr >> 7) & 0x1F;
    instruction->funct3 = (instruction->raw_instr >> 12) & 0x7;
    instruction->rs1 = (instruction->raw_instr >> 15) & 0x1F;
    instruction->rs2 = (instruction->raw_instr >> 20) & 0x1F;
    instruction->funct7 = (instruction->raw_instr >> 25) & 0x7F;
    instruction->imm = (instruction->raw_instr >> 20);
    return;
}
