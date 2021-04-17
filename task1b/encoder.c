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
#define O_RDONLY 0
#define O_WRONLY 1

int main(int argc, char **argv)
{

    int i;
    int debugMode = 0;
    int c;
    int in = STDIN;
    int out = STDOUT;
    int lowerCase;
    int check;

    for (i = 1; i < argc; i++)
    {
        if (strncmp(argv[i], "-D", 2) == 0)
        {
            debugMode = 1;
            system_call(SYS_WRITE, STDERR, "-D\n", 3);
        }

        if (strncmp(argv[i], "-o", 2) == 0)
        {
            out = system_call(SYS_OPEN, argv[i] + 2, O_WRONLY, 0777);
            if (out < 0)
                system_call(EXIT, 0x55);
        }

        if (strncmp(argv[i], "-i", 2) == 0)
        {
            in = system_call(SYS_OPEN, argv[i] + 2, O_RDONLY, 0777);
            if (in < 0)
                system_call(EXIT, 0x55);
        }
    }

    while (1)
    {
        check = system_call(SYS_READ, in, &c, 1);
        if (check == 0)
            break;
        if (check < 0)
            system_call(EXIT, 0x55);
        lowerCase = c;
        if (c >= 'A' && c <= 'Z')
            lowerCase = c + 32;

        check = system_call(SYS_WRITE, out, &lowerCase, 1);
        if (check <= 0)
            system_call(EXIT, 0x55);
    }
    if (out != STDOUT)
    {
        check = system_call(SYS_CLOSE, out);
        if (check < 0)
            system_call(EXIT, 0x55);
    }
    if (in != STDIN)
    {
        check = system_call(SYS_WRITE, out, "\n", 1);
        if (check <= 0)
            system_call(EXIT, 0x55);
        check = system_call(SYS_CLOSE, in);
        if (check < 0)
            system_call(EXIT, 0x55);
    }
    return 0;
}