#include <assert.h>
#include <string.h>
#include "asm.h"

ASM_ERROR asm_read_file(PROGRAM_CODE* programCodeInfo, const int argc, const char* argv[])
{
    asm_open_input_file      (programCodeInfo, argc, argv);
    asm_count_symbols_in_file(programCodeInfo);
    asm_read_commands_in_file(programCodeInfo);
    asm_create_output_file   (programCodeInfo);

    return NONE;
}

ASM_ERROR asm_open_input_file(PROGRAM_CODE* programCodeInfo, const int argc, const char* argv[])
{
    if (argc < 2)
    {
        return INPUT_FILE_ALLOCATION_ERROR;
    }
    programCodeInfo->input_file = fopen(argv[1], "rb");
    if (!programCodeInfo->input_file)
    {
        return INPUT_FILE_ALLOCATION_ERROR;
    }

    return NONE;
}

ASM_ERROR asm_count_symbols_in_file(PROGRAM_CODE* programCodeInfo)
{
    assert(programCodeInfo && "null pointer on programCodeInfo in asm_count_symbols_in_file\n");

    fseek(programCodeInfo->input_file, 0, SEEK_END);
    programCodeInfo->size = ftell(programCodeInfo->input_file);
    fseek(programCodeInfo->input_file, 0, SEEK_SET);
    if (!programCodeInfo->input_file)
    {
        // TODO I WILL MAKE IT BRIGHT!!!
        return INPUT_FILE_ALLOCATION_ERROR;
    }
    if (programCodeInfo->size < 0)
    {
        // TODO add return in log file
        return INVALID_SIZE;
    }

    return NONE;
}

ASM_ERROR asm_remove_newline_symbols(PROGRAM_CODE* programCodeInfo)
{
    assert(programCodeInfo && "null pointer on programCodeInfo in asm_remove_newline_symbols\n");

    programCodeInfo->words_quantity = 0;
    for (ssize_t symbol_index = 0; symbol_index < programCodeInfo->size; symbol_index++)
    {
        if (programCodeInfo->program_code[symbol_index] == '\n' ||
            programCodeInfo->program_code[symbol_index] == ' ')
        {
            programCodeInfo->words_quantity++;
            programCodeInfo->program_code[symbol_index] = '\0';
        }
    }

    return NONE;
}

ASM_ERROR asm_count_words_in_file(PROGRAM_CODE* programCodeInfo)
{
    assert(programCodeInfo && "null pointer on programCodeInfo in asm_count_words_in_file\n");

    programCodeInfo->word_pointer = (char** ) calloc(programCodeInfo->words_quantity + 1, sizeof(char*));
    ssize_t word_pointer_index = 0;
    programCodeInfo->word_pointer[word_pointer_index++] = programCodeInfo->program_code;
    for (ssize_t symbol_index = 0; symbol_index < programCodeInfo->size - 1; symbol_index++)
    {
        if (programCodeInfo->program_code[symbol_index] == '\0')
        {
            programCodeInfo->word_pointer[word_pointer_index++] = &programCodeInfo->program_code[symbol_index + 1];
        }
    }

    return NONE;
}

ASM_ERROR asm_read_commands_in_file(PROGRAM_CODE* programCodeInfo)
{
    assert(programCodeInfo && "null pointer on programCodeInfo in asm_read_commands_in_file\n");

    programCodeInfo->program_code = (char*) calloc(programCodeInfo->size + 1, sizeof(char));
    if (!programCodeInfo->program_code) {
        // TODO add clever verification
        return PROGRAM_CODE_ALLOCATION_ERROR;
    }

    fread(programCodeInfo->program_code, sizeof(char), programCodeInfo->size, programCodeInfo->input_file);
    asm_remove_newline_symbols(programCodeInfo);
    asm_count_words_in_file   (programCodeInfo);

    return NONE;
}

ASM_ERROR asm_command_switch(PROGRAM_CODE* programCodeInfo, const char* command)
{
    if (!programCodeInfo)
    {
        return STRUCT_ALLOCATION_ERROR;
    }
    if (strcmp(command, "start") == 0) {fprintf(programCodeInfo->output_file, "%d ", _start); return NONE;}
    if (strcmp(command, "hlt"  ) == 0) {fprintf(programCodeInfo->output_file, "%d ", _hlt  ); return NONE;}
    if (strcmp(command, "out"  ) == 0) {fprintf(programCodeInfo->output_file, "%d ", _out  ); return NONE;}
    if (strcmp(command, "push" ) == 0) {fprintf(programCodeInfo->output_file, "%d ", _push ); return NONE;}
    if (strcmp(command, "pop"  ) == 0) {fprintf(programCodeInfo->output_file, "%d ", _pop  ); return NONE;}
    if (strcmp(command, "add"  ) == 0) {fprintf(programCodeInfo->output_file, "%d ", _add  ); return NONE;}
    if (strcmp(command, "sub"  ) == 0) {fprintf(programCodeInfo->output_file, "%d ", _sub  ); return NONE;}
    if (strcmp(command, "mult" ) == 0) {fprintf(programCodeInfo->output_file, "%d ", _mult ); return NONE;}
    if (strcmp(command, "div"  ) == 0) {fprintf(programCodeInfo->output_file, "%d ", _div  ); return NONE;}
    else
    {
        fprintf(programCodeInfo->output_file, "%s ", command);
    }

    return NONE;
}

ASM_ERROR asm_create_output_file(PROGRAM_CODE* programCodeInfo)
{
    assert(programCodeInfo && "null pointer on programCodeInfo in asm_create_output_file\n");

    programCodeInfo->output_file = fopen("a.asm", "w");
    if (!programCodeInfo->output_file)
    {
        printf("null pointer on output_file in asm_create_output_file\n");
        return OUTPUT_FILE_ALLOCATION_ERROR;
    }
    for (ssize_t string_index = 0; string_index < programCodeInfo->words_quantity; string_index++)
    {
        asm_command_switch(programCodeInfo, programCodeInfo->word_pointer[string_index]);
    }
    fclose(programCodeInfo->output_file);

    return NONE;
}
