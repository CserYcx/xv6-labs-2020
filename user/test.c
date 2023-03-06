#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
/* That's a test to test some system call*/

int 
main(){
    struct stat st;
    int fd = open("cat",O_RDONLY);
    fstat(fd,&st);
    stat("cat",&st);
    printf("st member is %d\n",st.type);
    exit(0);
}