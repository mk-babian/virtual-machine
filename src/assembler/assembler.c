#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../definitions.h"

int main(int argc, const char* argv[]){
    if (argc != 3){
        printf("Insufficient arguments. Use - ./assembler <file to read from> <file to output to>\n");
        return 3; 
    }

    FILE* read_file = fopen(argv[1], "r");
    if (!read_file){
        fprintf(stderr, "Failed to open read file\n");
        return 1;
    }

    FILE* write_file = fopen(argv[2], "wb");
    if (!write_file){
        fprintf(stderr, "Failed to open write file\n");
        fclose(read_file);
        return 1;
    }

    // get read_file file size
    fseek(read_file, 0, SEEK_END);
    long file_size = ftell(read_file);
    if (file_size == -1L){
        fprintf(stderr, "ftell failure\n");
        fclose(write_file);
        fclose(read_file);
        return 2;
    }
    fseek(read_file, 0, SEEK_SET);

    char line[LINE_LENGTH];
    const char* delimiters = " \n\t\r";

    char* instruction;
    char* operand;

    uint8_t opcode;
    int has_operand = 0;

    while (fgets(line, LINE_LENGTH, read_file) != NULL){
        instruction = strtok(line, delimiters);
        if (!instruction) continue;             // skip empty lines

        operand = strtok(NULL, delimiters);
        has_operand = 0;

        if (strcmp(instruction, "PUSH") == 0){
            opcode = PUSH;
            has_operand = 1;
        }
        else if (strcmp(instruction, "ADD") == 0){
            opcode = ADD;
            has_operand = 0;
        }
        else if (strcmp(instruction, "SUB") == 0){
            opcode = SUB;
            has_operand = 0;
        }
        else if (strcmp(instruction, "MUL") == 0){
            opcode = MUL;
            has_operand = 0;
        }
        else if (strcmp(instruction, "DIV") == 0){
            opcode = DIV;
            has_operand = 0;
        }
        else if (strcmp(instruction, "EQ") == 0){
            opcode = EQ;
            has_operand = 0;
        }
        else if (strcmp(instruction, "JZ") == 0){
            opcode = JZ;
            has_operand = 1;
        }
        else if (strcmp(instruction, "PRINT") == 0){
            opcode = PRINT;
            has_operand = 0;
        }
        else if (strcmp(instruction, "HALT") == 0){
            opcode = HALT;
            has_operand = 0;
        }
        else{
            fprintf(stderr, "unknown instruction: %s\n", instruction);
            fclose(write_file);
            fclose(read_file);
            return 3;
        }

        // write to binary file
        fwrite(&opcode, sizeof(uint8_t), 1, write_file);

        // handles writing operands
        if (has_operand && operand != NULL){
            uint8_t op = atoi(operand);
            fwrite(&op, sizeof(uint8_t), 1, write_file);
        }
    }

    fclose(write_file);
    fclose(read_file);
    return 0;
}
