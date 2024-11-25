#include "../inc/processor.h"
#include "../inc/instr_handler.h"
#include "../inc/GUI.h"

void allocate_memory(Memory *memory) {
    printf("Allocating memory\n");
    memory->byte = (uint8_t *)malloc(MEMORY_SIZE * sizeof(uint8_t));
    if (memory->byte == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void RISC_V(char *filename, int step) {
    CPU cpu = { .pc = 0, .GPRs = {0} };
    cpu.GPRs[2] = STACK_BASE_ADDRESS;
    cpu.GPRs[3] = BASE_GLOBAL_POINTER;
    cpu.step = step; 
    Memory memory;
    Instruction instruction = { 0 };

    allocate_memory(&memory);

    // Initialize memory and registers within valid range
    //memory.byte[DATA_BASE_ADDRESS]      = (uint8_t)0x0a;
    //memory.byte[DATA_BASE_ADDRESS + 1]  = (uint8_t)0x0a;
    //memory.byte[DATA_BASE_ADDRESS + 2]  = (uint8_t)0x0a;
    //memory.byte[DATA_BASE_ADDRESS + 3]  = (uint8_t)0x0a;
    //cpu.GPRs[5] = DATA_BASE_ADDRESS;

    // Load program into memory
    load_program(filename, &memory);
    init_terminal();
    while(cpu.pc <= (int)(memory.instr_count * 4)) {
        fetch(&cpu, &memory, &instruction);
        decode(&instruction);
        execute(&cpu, &memory, &instruction);
        ensure_zero_register(&cpu);

        //CAN BE USED TO STEP THROUGH THE PROGRAM
        if (cpu.step) {
            write_information(&cpu, &instruction);
            print_memory(&memory);
            while(_getch() != ' ');
        }

        cpu.cycles++;

    }
    
    free(memory.byte);
    //free(memory.word);

    return;
}


void fetch(CPU *cpu, Memory *memory, Instruction *instruction) {
    // Fetch 4 consecutive bytes and combine them to form a 32-bit instruction
    uint32_t instr = ((uint32_t)memory->byte[cpu->pc]       << 0)  |
                     ((uint32_t)memory->byte[cpu->pc + 1]   << 8)  |
                     ((uint32_t)memory->byte[cpu->pc + 2]   << 16) |
                     ((uint32_t)memory->byte[cpu->pc + 3]   << 24);

    instruction->raw_instr = instr;
    return;
}


void load_program(const char *filename, Memory *memory) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return;
    }

    // Read the file into memory bytewise
    size_t bytes_read = fread(memory->byte, sizeof(uint8_t), MEMORY_SIZE, file);
    fclose(file);
    printf("Program loaded into memory\n");
    memory->instr_count = bytes_read / 4;
    printf("Instructions read: %zu\n", memory->instr_count);

    return;
}

void decode(Instruction *instruction) {
    instruction->opcode = instruction->raw_instr & 0x7F;
    instruction->rd = (instruction->raw_instr >> 7) & 0x1F;
    instruction->funct3 = (instruction->raw_instr >> 12) & 0x7;
    instruction->rs1 = (instruction->raw_instr >> 15) & 0x1F;
    instruction->rs2 = (instruction->raw_instr >> 20) & 0x1F;
    instruction->funct7 = (instruction->raw_instr >> 25) & 0x7F;

    return;
}
