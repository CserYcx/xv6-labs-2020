#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
/* That's a test to test some system call*/
char *buf;

int 
main(){
    int fd;
    char *p = buf;
    struct dirent de;
    struct stat st;
    close(0);
    fd = open("cat",O_RDONLY);
    // i think read function is crazy because it can put the string 
    // into the non-pointer variant
    // i'm puzzled for its powerful function 
    fstat(fd,&st);
    read(fd,&de,sizeof(de));
    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;
    printf("the buf is %s\n",buf);
    exit(0);
}