/**
 * tinycalc.c
 *
 * TinyCalc - A simple, terminal-based calculator application.
 *
 * This file implements the behaviors defined in the interface
 * specified in tinycalc.h.
 *
 * Written by Carlos Garcia Moran
 */

#include "tinycalc.h"
#include <stdlib.h>
#include <string.h>


int check_command(char command)
{
    if (command == '+' || command == '-' || command == '*' || command == '/' || command == '^'
        || command == 'm' || command == 'M' || command == 'q' || command == 'Q')
        return TC_COMMAND_OK;

    return TC_COMMAND_INVALID;
}

int read_command(char *command, double *operand)
{
    if (*command == 'q' || *command == 'Q')
        return TC_COMMAND_QUIT;

    char raw_operand[9];

    memset(raw_operand, '\0', 9);
    strncpy(raw_operand, command+1, 9);
    *operand = strtod(raw_operand, NULL);

    return TC_COMMAND_OK;
}

void execute_calculation(char operator, double operand2, double *operand1)
{
    if      (operator == '+')   *operand1 += operand2;
    else if (operator == '-')   *operand1 -= operand2;
    else if (operator == '*')   *operand1 *= operand2;
    else if (operator == '/')   *operand1 /= operand2;
    else
    {
        double x = *operand1;   *operand1 = 1;

        for (int i = 0; i < operand2; i++)
            *operand1 *= x;
    }
}

double mem_read(tc_memory_t memory, int n)
{
    if (n < TC_MEM_SZ)  return memory.vals[n];
    else                return memory.most_recent;
}

void mem_save(tc_memory_t *memory, double value)
{
    for (int i = TC_MEM_SZ-1; i >= 0; i--)
        memory->vals[i] = memory->vals[i-1];

    memory->vals[0] = value;
    memory->most_recent = value;  // implicit casting to int
}
