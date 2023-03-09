#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
/* That's a test to test some system call*/

int 
main(){
    char *arg[3] = {"echo","sss",0};
    for(int i=0;i<2;++i){
        exec("echo",arg);
    }
    exit(0);
}