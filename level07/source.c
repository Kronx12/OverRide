#include <stdio.h>
#include <string.h>

unsigned int get_unum(void)
{
    unsigned int value;

    value = 0;
    fflush(stdout);
    scanf("%u", &value);
    clear_stdin();
    return value;
}

int read_number(unsigned int *param)
{
    unsigned int number;

    printf(" Index: ");
    number = get_unum();
    printf(" Number at data[%u] is %u\n", number, param[number]);
    return 0;
}

int store_number(unsigned int *param)
{
    unsigned int number;
    unsigned int index;

    printf(" Number: ");
    number = get_unum();
    printf(" Index: ");
    index = get_unum();

    // Si l'index est un multiple de 3 ou si number est entre 0xb7000000 et 0xb8000000
    if (!(index % 3) || (number >> 0x18 == 0xb7))
    {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return (1);
    }
    else
    {
        param[index] = number;
        return (0);
    }
}

int main(int param_1, char **argv, char **env)
{
    int *in_GS_OFFSET;
    unsigned int storage[100];
    int result;
    char *input;
    int canary;

    canary = in_GS_OFFSET[20]; // Setup canary

    // Init storage to 0
    for (int i = 0; i < 100; i++)
        storage[i] = 0;

    // Clear des argv
    for (int i = 0; argv[i]; i++)
        memset(argv[i], 0, strlen(argv[i]));

    // Clear des envs
    for (int i = 0; env[i]; i++)
        memset(env[i], 0, strlen(env[i]));

    puts("----------------------------------------------------\n  Welcome to wil\'s crappy number stora ge service!   \n----------------------------------------------------\n Commands:                                           \n    store - store a number into the data storage    \n    read   - read a number from the data storage     \n    quit  - exit the program                         \n----------------------------------------------------\n   wil has reserved some storage :>                  \n----------------------------------------------------\n");

    do
    {
        printf("Input command: ");
        fgets(&input, 20, stdin);

        result = 1;
        if (!strcmp(input, "store"))
            result = store_number(storage); // Commande store
        else {
            if (!strcmp(input, "read"))
                result = read_number(storage); // Commande read
            else {
                if (!strcmp(input, "quit")) {
                    if (canary == in_GS_OFFSET[20]) // Final canary check 
                        return (0);
                    __stack_chk_fail();
                }
            }
        }

        if (!result)
            printf(" Completed %s command successfully\n", &input);
        else
            printf(" Failed to do %s command\n", &input);
            
    } while (1);
}
