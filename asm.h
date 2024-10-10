#ifndef ASM_H_
#define ASM_H_

#include <ctype.h>
#include <stdlib.h>
#include <cstdio>

enum ASM_ERROR
{
    NONE             = 0,
    ALLOCATION_ERROR = 1,
    INVALID_SIZE     = 2,
    INVALID_COMMAND  = 3
};

enum PROCESSOR_COMMANDS
{
    _start = 0,
    _hlt   = 1,
    _push  = 2,
    _pop   = 3,
    _add   = 4,
    _sub   = 5,
    _mult  = 6,
    _div   = 7
};

struct PROGRAM_CODE
{
    FILE*   file;
    ssize_t size;
    char*   program_code;
};

int asm_read_file              (FILE* file);
int asm_count_symbols_in_file  (PROGRAM_CODE* programCodeInfo, FILE* file);
int asm_read_commands_in_file  (PROGRAM_CODE* programCodeInfo, FILE* file);
int asm_remove_newline_symbols (PROGRAM_CODE* programCodeInfo);
int asm_read_commands_in_file  (PROGRAM_CODE* programCodeInfo, FILE* file);

#endif
