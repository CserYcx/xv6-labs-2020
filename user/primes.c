#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

/*! \note   1.read return zero when the write-side of a pipe closed
            2.Directly wirte the 32-bit ints pips rather than using formatted ASCII
*/

/*! \brief  1.set up a process for each number
            2.if the current number can't be modular, and less than the number, 
            plus it and put it on new pipe
*/
int status ;
char buf[1] = {0};
int p[2];

int 
main(){
    const int begin = 2;
    const int end = 35;
    for(int i=begin;i<=end;++i){
        *buf = begin;
        if(i == begin){
            printf("prime %d\n",i);
            continue;
        }
        if(i % (*buf) == 0){
            continue;
        }
        else{
            pipe(p);
            write(p[1],buf,1);
            if(fork() == 0){
                read(p[0],buf,1);
                if(*buf < i && i%(*buf) == 0){
                    close(p[0]);
                    close(p[1]);
                    exit(1);
                }
                else if((*buf) == i){
                    printf("i is %d\n",i);
                    close(p[0]);
                    close(p[1]);
                    exit(0);
                }
                else{
                    (*buf) += 1;
                    fork();
                    exit(0);
                }
            }else{
                wait(&status);
                if(!status){
                    printf("status %d\n",status);
                    printf("prime %d\n",i);
                    close(p[0]);
                    close(p[1]);
                }else{
                    close(p[0]);
                    close(p[1]);
                }
            }
        }
    }
    exit(0);
}