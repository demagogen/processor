#include <assert.h>
#include "asm.h"

int asm_read_file(PROGRAM_CODE* programCodeInfo, FILE* file)
{
    asm_count_symbols_in_file(programCodeInfo, file);
    asm_read_commands_in_file(programCodeInfo, file);

    return 0;
}

int asm_count_symbols_in_file(PROGRAM_CODE* programCodeInfo, FILE* file)
{
    assert(file && "null pointer on file in asm_count_symbols_in_file\n");
    assert(programCodeInfo && "null pointer on programCodeInfo in asm_count_symbols_in_file\n");

    fseek(file, 0, SEEK_END);
    programCodeInfo->size = ftell(file);
    if (programCodeInfo->size < 0)
    {
        // TODO add return in log file
        return -1;
    }
    fseek(file, 0, SEEK_SET);

    return 0;
}

int asm_remove_newline_symbols(PROGRAM_CODE* programCodeInfo)
{
    assert(programCodeInfo && "null pointer on programCodeInfo in asm_remove_newline_symbols\n");

    for (ssize_t symbol_index = 0; symbol_index < programCodeInfo->size; symbol_index++)
    {
        if (programCodeInfo->program_code[symbol_index] == '\n')
        {
            programCodeInfo->program_code[symbol_index] = ' ';
        }
    }

    return 0;
}

int asm_read_commands_in_file(PROGRAM_CODE* programCodeInfo, FILE* file)
{
    assert(file && "null pointer on file in asm_read_commands_in_file\n");
    assert(programCodeInfo && "null pointer on programCodeInfo in asm_read_commands_in_file\n");

    programCodeInfo->program_code = (char*) calloc(programCodeInfo->size + 1, sizeof(char));
    if (!programCodeInfo->program_code) {
        // TODO add clever verification
        return ALLOCATION_ERROR;
    }

    fread(programCodeInfo->program_code, sizeof(char), programCodeInfo->size, file);
    fclose(file);

    return 0;
}



int asm_rewrite_program_code(PROGRAM_CODE* programCodeInfo)
{
    assert(programCodeInfo && "null pointer on programCodeInfo in asm_rewrite_program_code\n");

    ssize_t letter_index = -1;
    while (letter_index++ < programCodeInfo->size)
    {
    }

    return 0;
}
