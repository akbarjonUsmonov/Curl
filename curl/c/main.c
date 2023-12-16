#include "../h/main.h"

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        failure_statement("Too many arguments\n");
    }
    if (sockat_preparation(argv[1]) != 0)
    {
        failure_statement("Socket preperation fault\n");
    }
    return 0;
}