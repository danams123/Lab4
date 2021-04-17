#include "../lab4_util.h"
#include <fcntl.h>

#define EXIT 1
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19

#define _O_RDWR 0x0002
#define SEEK_CURR 0x291

extern int system_call(int, ...);

int main(int argc, char *argv[])
{
    char *path_name = argv[1];
    char *x_name = strcat(argv[2], ".\n");
    int check;
    int fd = system_call(SYS_OPEN, path_name, O_RDWR, 0777);
    if (fd >= 0)
    {
        check = system_call(SYS_LSEEK, fd, SEEK_CURR, 0);
        if (check > 0)
        {
            check = system_call(SYS_WRITE, fd, x_name, 7);
            if (check > 0)
            {
                check = system_call(SYS_CLOSE, fd);
                if (check > 0)
                {
                    return 0;
                }
            }
        }
    }
    system_call(EXIT, 0x55);
}