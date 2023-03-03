#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int 
main(int argc, char const *argv[])
{

    /* code */
    if(argc > 2){
        printf("provide more parameters!\n");
        exit(1);
    }
    if(argc < 2){
        printf("sleep need a parameter!\n");
        exit(1);
    }

    // get the sleep time
    int time = atoi(argv[1]);
    printf("nothing happen for a little while.\n");
    sleep(time);
    exit(0);
    
}
