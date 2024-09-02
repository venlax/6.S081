#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


void find(char *path, char *name) {
    char buf[32];
    strcpy(buf,path);
    int fd = open(path, 0);
    struct stat st;
    struct dirent de;
    fstat(fd, &st);
    if (st.type == T_DIR) {
        while (read(fd, &de, sizeof(de)) == sizeof(de)) {
            // do not recurse into . & .. !!! how stupid you are 🤯
            if (de.inum == 0 || (strcmp(de.name, ".") == 0) || (strcmp(de.name, "..") == 0)) continue;
            strcpy(path,buf);
            char *ab_name = strcat(strcat(path,"/"),de.name);
            stat(ab_name, &st);
            if (st.type == T_FILE) {
                if (strcmp(name, de.name) == 0) {
                    printf("%s\n", ab_name);
                }
            } else if (st.type == T_DIR){    
                find(ab_name,name);
            }
        }
    }
}


int main(int argc, char *argv[]) {
    char buf[32];
    strcpy(buf, argv[1]);
    find(buf, argv[2]);
    
    exit(0);
}