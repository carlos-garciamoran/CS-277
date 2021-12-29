/**
 * driver.c
 *
 * TinyCalc - A simple, terminal-based calculator application.
 *
 * This is the driver part of the application.
 *
 * Build: cc -std=c99 driver.c tinycalc.c -o tinycalc
 * Run:   ./tinycalc
 *
 * Written by Carlos Garcia Moran
 */

#include <stdio.h>
#include "tinycalc.h"


void init_mem(tc_memory_t *memory)
{
    for (int i = 0; i < TC_MEM_SZ; i++)
        memory->vals[i] = 0.0;

    memory->most_recent = 0;
}

int main()
{
    char input[10];
    char command;
    double input_operand;
    double main_operand = 0.0;

    tc_memory_t memory;
    init_mem(&memory);

    printf("\nWelcome to TinyCalc!\n\n Enter an operation <+, - , *, /, ^>");
    printf(" followed by a real number.\n\n Enter 'q' or 'Q' to quit.\n\n");
    printf(" Enter 'm' or 'M' followed by a location (0-4) to load a previous\n");
    printf(" result from memory.\n");
    
    while (1)
    {
        printf("\n> ");
        fgets(input, 10, stdin);

        command = input[0];

        if (check_command(command) == 0)                continue;
        if (read_command(input, &input_operand) == 0)   break;

        // Only execute a calculation for arithmetic operators
        if (command == '+' || command == '-' || command == '*' || command == '/' || command == '^')
        {
            execute_calculation(command, input_operand, &main_operand);
            mem_save(&memory, main_operand);
        }
        // Retrieve data from memory
        else
        {
            // Check for bad input (e.g., m-2.5)
            if (input_operand >= 0)
                main_operand = mem_read(memory, (int) input_operand);
        }

        printf("%lf\n", main_operand);
    }

    return 0;
}
