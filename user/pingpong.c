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
    // write in p[1] and read p[0] 
    // you can think them have a same space but different right to use the space
    int p[2];           // store the read/write file descriptor in p[0] and p[1]


    pipe(p);

    if(fork() == 0){
        // make sure pipe[0] refer to read end of the pipe
        //close(0);
        //dup(p[0]);
        if(read(p[0],buf1,sizeof(trans)) == sizeof(trans)){
            printf("%d: received ping\n",getpid());
        }
        //close(1);
        //dup(p[1]);
        write(p[1],trans,sizeof(trans));
        close(p[0]);
        close(p[1]);
        exit(0);
    }else{
        // close std read
        //dup(p[0]);
        write(p[1],trans,sizeof(trans));
        wait(0);
        if(read(p[0],buf1,sizeof(trans) == sizeof(trans))){
            printf("%d: received pong\n",getpid());
        }
        close(p[0]);
        close(p[1]);
        exit(0);
    }
   
}
