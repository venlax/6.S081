#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"



int main(int argc, char *argv[]) {
        char buffer[320];
        char* new_argv[MAXARG];
        //for (int i = 0; i < argc;++i) printf("%s\n",argv[i]);
        for (int i = 0; i < MAXARG; ++i) {
            new_argv[i] = 0;
        }
        int num = 1;
        for (; num < argc; ++num) new_argv[num - 1] = argv[num];
        int pos = 0;
        int offset = 0;
        while(read(0, buffer + pos, 1) == 1) {
            
            if (buffer[pos] == ' ') {
                buffer[pos] = '\0';
                new_argv[(num++) - 1] = buffer + pos - offset;
                pos++;
            } else if (buffer[pos] == '\n') {
                buffer[pos] = '\0';
                new_argv[(num++) - 1] = buffer + pos - offset;
                
                if (fork() == 0) exec(new_argv[0], new_argv);   
                wait(0);
                pos = 0;
                offset = 0;
                num = argc;
            } else {
                offset++;
                pos++;
            }

        }

    exit(0);
}
