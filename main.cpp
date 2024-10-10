#include "asm.h"

int main(int argc, const char* argv[])
{
    PROGRAM_CODE programCodeInfo = {};

    if (argc == 1)
    {
        printf("incorrect input\n");
    }
    if (argc == 2)
    {
        // TODO magic numbers and idiotic parsing
        programCodeInfo.file = fopen(argv[1], "rb");
    }

    return 0;
}
