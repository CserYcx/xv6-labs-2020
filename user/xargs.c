#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"

/*  Some hints:
    1.  Use the fork and exec to control each line input 
        Use the wait for child to complete  
    2.  To read individual line, read a character at a time 
        until newline '\n' show 
*/
char param[512];

// split the current string and return a position point at next string start
char *split(char *p, int *pos, char ch){
    char *ret;
    ret = (char *)malloc(sizeof(char *));
    for(int i=*pos,j=0;i<strlen(p);++i){
        if(*(p+i) == ch){
            *pos = i+1;
            return ret;
        }
        else if(*(p+i) == 0){
            return ret;
        }
        else{
            *(ret+j)= *(p+i);
            j++;
        }
    }
    //printf("ret is %s\n",ret);
    return ret;
}


int 
main(int argc, char const *argv[])
{
    /* code */
    /*! \note   Read line from the standard input
                it seems like need to read(0,...)*/

    /*! \note   And we use the former out as parameters to supply
                our command */

    /*! \todo   So we can use the fork and exec to invoke our command line
                think the current command is child, former command is parent
                parent do the command until the child finish its process*/

    /*! \note   Read a character until new line appears*/

    int status;

    // read the stdout
    /*! \attention  you need to handle the '\n' in the param*/
    read(0,param,sizeof(param));

    // xargs has no parameter
    if(argc == 1){
        write(1,param,sizeof(param));
        exit(0);
    }

    //printf("the former process output is %s\n",param);
    // xargs has command line but no '-n'
    //! \todo   how could i store the **P to the *p
    //! \note   Remember to truncate the string!!!!!
    if(argc > 1 && strcmp(argv[1],"-n") != 0){
        char *exe = (char *)argv[1];
        
        if(fork() == 0){
            /*! \note   I don't append the file path as prefix of the command
                        because i think each command file is in the current path
            */
            /*! \note   I think my method to concate the current string and former output
                        is every stupid
            */
            /*! \bug    Handling the individual line, you should skip the '\n' in the string*/
            char *p[MAXARG*2];
            for(int i=1;i<argc;++i){
                p[i-1] = (char *)argv[i];
            }
            char *temp = param;
            int pos = 0;
            for(int i=argc-1;i<MAXARG*2;++i){
                char *str = split(temp,&pos,'\n');
                p[i] = str;
                if(strlen(str) == 0){
                    break;
                }
            }
            /*
            p[argc-1] = param;
            p[argc-1][strlen(param)-1] = 0;
            p[argc] = 0;
            */
            if(strlen(*p) != 0){
                exec(exe,p);
                exit(1);
            }
            exit(0);
        }else{
            wait(&status);
            exit(0);
        }
    }

    // xargs has command line and has '-n'
    if(argc > 1 && strcmp(argv[1],"-n") == 0){
        /*! \note   1. Handle the '\n'
                    2. parameters will be excuted after current line finish*/
        char *p = param; 
        int pos = 0;
        for(int i=0;i<strlen(param);i=pos){
            char *s = split(p,&pos,'\n');
            char *exe = (char *)argv[2];
            char *arg[2];
            arg[0] = (char *)argv[3];
            arg[1] = s;
            if(fork() == 0){
                exec(exe,arg);
                exit(1);
            }else{
                wait(&status);
                continue;
            }
        }
        exit(0);
    }

    printf("xargs is wrong\n");
    exit(0);
}

