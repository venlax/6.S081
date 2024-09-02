
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// static int primes[35];
// static int count = 0;

void prime(int r_pipe) {
    int base;
    if (read(r_pipe, &base, 4) == 0) exit(0);
    printf("prime %d\n",base);
    int p[2];
    pipe(p);
    if (fork() == 0) {
        close(p[1]);
        prime(p[0]);
        close(p[0]);

        exit(0);
    } else {
        
        close(p[0]);
        int num;
        while (read(r_pipe, &num, 4) > 0) {
            if (num % base != 0){
                write(p[1], &num, 4);
            } 
        }
        close(p[1]);
        wait((int *)0);

        exit(0);
    }
}

int main(int argc, char *argv[]) {
    int p[2];
    pipe(p);

    if (fork() == 0) {
        close(p[1]);
        prime(p[0]);
        close(p[0]);

        exit(0);
    } else {
        close(p[0]);
        for (int i = 2; i <= 35; ++i) {
            write(p[1], &i, 4);
        }
        close(p[1]);
        wait((int *)0);

        exit(0);
    }
}