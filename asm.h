#ifndef ASM_H_
#define ASM_H_

#include <ctype.h>
#include <stdlib.h>
#include <cstdio>

enum ASM_ERROR
{
    NONE                          = 0,
    INPUT_FILE_ALLOCATION_ERROR   = 1,
    OUTPUT_FILE_ALLOCATION_ERROR  = 2,
    PROGRAM_CODE_ALLOCATION_ERROR = 3,
    STRUCT_ALLOCATION_ERROR       = 4,
    INVALID_SIZE                  = 5,
    INVALID_COMMAND               = 6
};

enum PROCESSOR_COMMANDS
{
    _error = -1,
    _start =  0,
    _hlt   =  1,
    _out   =  2,
    _push  =  3,
    _pop   =  4,
    _add   =  5,
    _sub   =  6,
    _mult  =  7,
    _div   =  8
};

struct PROGRAM_CODE
{
    FILE*   input_file;
    FILE*   output_file;
    ssize_t size;
    ssize_t words_quantity;
    char**  word_pointer;
    char*   program_code;
};

ASM_ERROR          asm_read_file              (PROGRAM_CODE* programCodeInfo, const int argc, const char* argv[]);
ASM_ERROR          asm_open_input_file        (PROGRAM_CODE* programCodeInfo, const int argc, const char* argv[]);
ASM_ERROR          asm_count_symbols_in_file  (PROGRAM_CODE* programCodeInfo);
ASM_ERROR          asm_count_words_in_file    (PROGRAM_CODE* programCodeInfo);
ASM_ERROR          asm_read_commands_in_file  (PROGRAM_CODE* programCodeInfo);
ASM_ERROR          asm_remove_newline_symbols (PROGRAM_CODE* programCodeInfo);
ASM_ERROR          asm_read_commands_in_file  (PROGRAM_CODE* programCodeInfo);
ASM_ERROR          asm_command_switch         (PROGRAM_CODE* programCodeInfo, const char* command);
ASM_ERROR          asm_create_output_file     (PROGRAM_CODE* programCodeInfo);

#endif
