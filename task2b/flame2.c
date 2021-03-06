#include "lab4_util.h"

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

enum
{
    DT_UNKNOWN = 0,
#define DT_UNKNOWN DT_UNKNOWN
    DT_FIFO = 1,
#define DT_FIFO DT_FIFO
    DT_CHR = 2,
#define DT_CHR DT_CHR
    DT_DIR = 4,
#define DT_DIR DT_DIR
    DT_BLK = 6,
#define DT_BLK DT_BLK
    DT_REG = 8,
#define DT_REG DT_REG
    DT_LNK = 10,
#define DT_LNK DT_LNK
    DT_SOCK = 12,
#define DT_SOCK DT_SOCK
    DT_WHT = 14
#define DT_WHT DT_WHT
};

extern int system_call(int, ...);

typedef struct ent
{
    int inode;
    int offset;
    short len;
    char d_name[];
} ent;

void e_gracefully(int fd)
{
    system_call(SYS_CLOSE, fd);
    system_call(EXIT, 0x55);
}

int main(int argc, char *argv[])
{
    int fd;
    int check;
    long nread;
    long bpos;
    char buf[MAX_SIZE];
    struct ent *entp;
    char d_type;
    char *type;
    int i;
    char prefix = 0;
    for (i = 1; i < argc; i++)
    {
        if (strncmp(argv[i], "-p", 2) == 0)
        {
            prefix = *(argv[i] + 2);
        }
    }

    fd = system_call(SYS_OPEN, ".", O_RDONLY, 0777);
    if (fd < 0)
        system_call(EXIT, 0x55);

    nread = system_call(SYS_GETDENTS, fd, buf, MAX_SIZE);
    if (nread < 0)
        system_call(EXIT, 0x55);

    for (bpos = 32; bpos < nread;)
    {
        entp = (struct ent *)(buf + bpos);
        d_type = *(buf + bpos + entp->len - 1);
        type = (d_type == DT_REG) ? "regular" : (d_type == DT_DIR) ? "directory"
                                            : (d_type == DT_FIFO)  ? "FIFO"
                                            : (d_type == DT_SOCK)  ? "socket"
                                            : (d_type == DT_LNK)   ? "symlink"
                                            : (d_type == DT_BLK)   ? "block dev"
                                            : (d_type == DT_CHR)   ? "char dev"
                                            : (d_type == DT_WHT)   ? "wht"
                                                                   : "???";
        if (prefix == 0 || prefix == entp->d_name[0])
        {
            check = system_call(SYS_WRITE, STDOUT, entp->d_name, strlen(entp->d_name));
            if (check < 0)
                e_gracefully(fd);
            check = system_call(SYS_WRITE, STDOUT, "\n", 1);
            if (check < 0)
                e_gracefully(fd);
            check = system_call(SYS_WRITE, STDOUT, type, strlen(type));
            if (check < 0)
                e_gracefully(fd);
            check = system_call(SYS_WRITE, STDOUT, "\n", 1);
            if (check < 0)
                e_gracefully(fd);
        }
        bpos += entp->len;
    }
    system_call(SYS_CLOSE, fd);
    return 0;
}