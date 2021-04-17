#include "../lab4_util.h"

#define EXIT 1
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19
#define SYS_GETDENTS 141

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define O_RDWR 2
#define O_RDONLY 0
#define O_WRONLY 1
#define MAX_SIZE 8192

extern int system_call(int, ...);
extern void code_start(void);
extern void code_end(void);

int main(void)
{
    int l = (&(code_end) - &(code_start));
    char *s = itoa(&(code_start));
    char *e = itoa(&(code_end));
    system_call(SYS_WRITE, STDOUT, s, strlen(s));
    system_call(SYS_WRITE, STDOUT, "\n", 1);
    system_call(SYS_WRITE, STDOUT, e, strlen(e));
    system_call(SYS_WRITE, STDOUT, "\n", 1);
    return 0;
}