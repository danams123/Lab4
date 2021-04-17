#include "../lab4_util.h"
extern int system_call(int, ...);

#define EXIT 1
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define O_RDWR 2

int main(int argc, char **argv)
{

    int i;
    int debugMode = 0;
    int c;
    int lowerCase;
    int check;

    for (i = 1; i < argc; i++)
    {
        if (strncmp(argv[i], "-D", 2) == 0)
        {
            debugMode = 1;
            check = system_call(SYS_WRITE, STDERR, "-D\n", 3);
            if (check <= 0)
                system_call(EXIT, 0x55);
        }
    }

    while (1)
    {
        check = system_call(SYS_READ, STDIN, &c, 1);
        if (check == 0)
            break;
        if (check < 0)
            system_call(EXIT, 0x55);
        lowerCase = c;
        if (c >= 'A' && c <= 'Z')
            lowerCase = c + 32;

        check = system_call(SYS_WRITE, STDOUT, &lowerCase, 1);
        if (check <= 0)
            system_call(EXIT, 0x55);
    }

    return 0;
}