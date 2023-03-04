#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

/* Some hints:
        1. use the pipe to create pipe
        2. use fork to create child 
        3. use read to read from the pipe, write to write the pipe
*/
char *buf1[100];
char *trans = "chat";

int 
main()
{
    /* code */
    int p[2];           // store the read/write file descriptor in p[0] and p[1]

    pipe(p);

    if(fork() == 0){
        close(0);
        dup(p[0]);
        if(read(p[0],buf1,sizeof(trans)) == sizeof(trans)){
            printf("%d: received ping\n",getpid());
        }
        close(1);
        dup(p[1]);
        write(p[1],trans,sizeof(trans));
        exit(p[1]);
    }else{
        close(0);
        dup(p[0]);
        write(p[1],trans,sizeof(trans));
        wait(0);
        if(read(p[0],buf1,sizeof(trans) == sizeof(trans))){
            printf("%d: received pong\n",getpid());
        }
        exit(p[0]);
    }
   
}
