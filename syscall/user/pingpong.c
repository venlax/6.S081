#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"



int main(int argc, char *argv[]) {
    int p[2];

    pipe(p);

    if (fork() == 0) {
        char buf[10];
        read(p[0], buf, 1);
        printf("%d: received ping\n", getpid());
        write(p[1], "1",1);
        close(p[0]);
        close(p[1]);
        exit(0);
    } else {
        write(p[1],"1",1);
        wait((int *)0);
        char buf[10];
        read(p[0], buf, 1);
        printf("%d: received pong\n", getpid());
        close(p[0]);
        close(p[1]);
        exit(0);
    }
}