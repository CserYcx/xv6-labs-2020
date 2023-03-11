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

int 
main(){
    const int begin = 2;
    const int end = 35;
    int p[2];
    pipe(p);
    for(int i=begin;i<=end;++i){
        buf[0] = begin;
        write(p[1],buf,1);
    }
    exit(0);
}