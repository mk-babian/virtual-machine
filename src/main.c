#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "definitions.h"

int main(int argc, const char* argv[]){
    if (argc != 2){
        printf("Please specify a file to use - ./program.exe <filename>\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "rb");
    if (!file){
        fprintf(stderr, "Failed to open file\n");
        return 1;
    }

    int stack[STACK_SIZE];      
    int sp = 0;                 // stack pointer
    int pc = 0;                 // program counter
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    if (file_size == -1L){
        fprintf(stderr, "ftell failed\n");
        fclose(file);
        return 2;
    }
    fseek(file, 0, SEEK_SET);

    uint8_t* program = malloc(sizeof(uint8_t) * file_size);
    if (!program){
        fprintf(stderr, "malloc failed\n");
        fclose(file);
        return 3;
    }

    fread(program, sizeof(uint8_t), file_size, file);

    while (1){
        int a, b, val, address, condition;
        uint8_t instruction = program[pc++];

        switch(instruction){
            case PUSH:
                val = program[pc++];
                stack[sp++] = val;
                break;
            case ADD:
                b = stack[--sp];
                a = stack[--sp];
                stack[sp++] = a + b;
                break;
            case SUB:
                b = stack[--sp];
                a = stack[--sp];
                stack[sp++] = a - b;
                break;
            case MUL:
                b = stack[--sp];
                a = stack[--sp];
                stack[sp++] = a * b;
                break;
            case DIV:
                b = stack[--sp];
                if (b == 0){
                    fprintf(stderr, "undefined division by zero\n");
                    free(program);
                    fclose(file);
                    return 4;
                }
                a = stack[--sp];
                stack[sp++] = a / b;
                break;
            case EQ:
                b = stack[--sp];
                a = stack[--sp];
                stack[sp++] = (a == b) ? 1 : 0;
                break;
            case JZ:
                address = program[pc++];
                condition = stack[--sp];
                if (condition == 0){
                    pc = address;
                }
                break;
            case PRINT:
                printf("%d\n", stack[--sp]);
                break;
            case HALT:
                free(program);
                fclose(file);
                return 0;
        }
    }

    free(program);
    fclose(file);
    return 0;
}
