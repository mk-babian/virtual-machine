#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "definitions.h"

int main(int argc, const char* argv[]){
    int exit_code = 0;

    if (argc != 2){
        printf("Please specify a file to use - ./program.exe <filename>\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "rb");
    if (!file){
        exit_code = 1;
        goto cleanup;
    }

    int stack[STACK_SIZE];      
    int sp = 0;                 // stack pointer
    int pc = 0;                 // program counter
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    if (file_size == -1L){
        exit_code = 2;
        goto cleanup;
    }
    fseek(file, 0, SEEK_SET);

    uint8_t* program = malloc(sizeof(uint8_t) * file_size);
    if (!program){
        exit_code = 3;
        goto cleanup;
    }

    fread(program, sizeof(uint8_t), file_size, file);
    // need to add error checking but i don't know how

    while (1){
        int a, b, val, address, condition;
        uint8_t instruction = program[pc++];

        switch(instruction){
            case PUSH:
                if (sp >= STACK_SIZE){
                    exit_code = 5;
                    goto cleanup;
                }
                val = program[pc++];
                stack[sp++] = val;
                break;
            case ADD:
                if (sp < 2){
                    exit_code = 6;
                    goto cleanup;
                }
                b = stack[--sp];
                a = stack[--sp];
                stack[sp++] = a + b;
                break;
            case SUB:
                if (sp < 2){
                    exit_code = 6;
                    goto cleanup;
                }
                b = stack[--sp];
                a = stack[--sp];
                stack[sp++] = a - b;
                break;
            case MUL:
                if (sp < 2){
                    exit_code = 6;
                    goto cleanup;
                }
                b = stack[--sp];
                a = stack[--sp];
                stack[sp++] = a * b;
                break;
            case DIV:
                if (sp < 2){
                    exit_code = 6;
                    goto cleanup;
                }
                b = stack[--sp];
                if (b == 0){
                    exit_code = 7;
                    goto cleanup;
                }
                a = stack[--sp];
                stack[sp++] = a / b;
                break;
            case EQ:
                if (sp < 2){
                    exit_code = 6;
                    goto cleanup;
                }
                b = stack[--sp];
                a = stack[--sp];
                stack[sp++] = (a == b) ? 1 : 0;
                break;
            case JZ:
                if (sp < 1){
                    exit_code = 6;
                    goto cleanup;
                }
                address = program[pc++];
                condition = stack[--sp];
                if (condition == 0){
                    pc = address;
                }
                break;
            case PRINT:
                if (sp < 1){
                    exit_code = 6;
                    goto cleanup;
                }
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

cleanup:
    if (exit_code == 1) fprintf(stderr, "failed to open file\n");
    if (exit_code == 2) fprintf(stderr, "fseek failed\n");
    if (exit_code == 3) fprintf(stderr, "malloc failed\n");

    if (exit_code == 5) fprintf(stderr, "stack overflow\n");;
    if (exit_code == 6) fprintf(stderr, "stack underflow\n");
    if (exit_code == 7) fprintf(stderr, "undefined division by zero\n");

    if (program) free(program);
    if (file) fclose(file);
    return exit_code; 
}
