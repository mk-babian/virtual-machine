#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../definitions.h"

int main(int argc, const char* argv[]){
    int exit_code = 0;

    FILE* read_file = fopen(argv[1], "r");
    if (!read_file){
        exit_code = 1;
        goto cleanup;
    }

    FILE* write_file = fopen("write_file", "w");
    if (!write_file){
        exit_code = 1;
        goto cleanup;
    }

    char* instruction;
    char* argument;
    char line[LINE_LENGTH];
    size_t stack_count = 0;
    size_t line_count = 1;

    while (fgets(line, LINE_LENGTH, read_file) != NULL){
        line[strcspn(line, "\n")] = '\0';
        instruction = strtok(line, "()");
        argument = strtok(NULL, "(,)");
        
        if (strcmp(instruction, "print") == 0){
            if (argument == NULL){
                if (stack_count < 1){
                    exit_code = 2;
                    goto cleanup;
                }
                else{
                    fprintf(write_file, "PRINT\n");
                    stack_count--;
                }
            }
            else{
                fprintf(write_file, "PUSH %d\nPRINT\n", atoi(argument));
            }
        }
        else if (strcmp(instruction, "add") == 0){
            char* arg2 = strtok(NULL, ", )"); 
            fprintf(write_file, "PUSH %d\nPUSH %d\nADD\n", atoi(argument), atoi(arg2));
            stack_count++;
        }
        else if (strcmp(instruction, "sub") == 0){
            char* arg2 = strtok(NULL, ", )");
            fprintf(write_file, "PUSH %d\nPUSH %d\nSUB\n", atoi(argument), atoi(arg2));
            stack_count++;
        }
        else if (strcmp(instruction, "mul") == 0){
            char* arg2 = strtok(NULL, ", )");
            fprintf(write_file, "PUSH %d\nPUSH %d\nMUL\n", atoi(argument), atoi(arg2));
            stack_count++;
        }
        else if (strcmp(instruction, "div") == 0){
            char* arg2 = strtok(NULL, ", )");
            if (atoi(arg2) == 0){
                exit_code = 3;
                goto cleanup;
            }
            fprintf(write_file, "PUSH %d\nPUSH %d\nDIV\n", atoi(argument), atoi(arg2));
            stack_count++;
        }

        // Debug
        printf("Instruction: %s\n", instruction);
        printf("Argument: %s\n", argument); 
        
        line_count++;
    }

    fprintf(write_file, "HALT\n");

    fclose(write_file);
    fclose(read_file);
    return exit_code;

cleanup:
    if (exit_code == 1) fprintf(stderr, "Failed to open file\n");
    if (exit_code == 2) fprintf(stderr, "Stack is empty | Error at line %zu\n", line_count);
    if (exit_code == 2) fprintf(stderr, "Undefined division by zero | Error at line %zu\n", line_count);

    if (write_file) fclose(write_file);
    if (read_file) fclose(read_file);
    return exit_code;
}
