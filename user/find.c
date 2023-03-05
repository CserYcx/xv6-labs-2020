#include "kernel/types.h"
#include "kernel/fs.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"

/* Simple version find: its format is find <path> <filename>*/
// The key is how to solve the file name in current directory
char buf[512];

void find(const char *path,int fd, struct stat st, struct dirent de,const char *filename){
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)){
        printf("find: the path is too long\n");
    }
    if(st.type != T_DIR){
        printf("find: can't find in %d type file\n",st.type);
        exit(0);
    }
    else{
        // read all the file under the directory
        while(read(fd,&de,sizeof(de)) == sizeof(de)){
            if(de.inum == 0)
                continue;
            if(strcmp(de.name,".") == 0 || strcmp(de.name, "..") == 0)
                continue;
            switch (fstat(fd,&st))
            {
            case T_FILE:
                if(strcmp(de.name, filename) == 0)
                    printf("%s/%s\n",de.name,filename);
                break;
            case T_DIR:
                break; 
            default:
                break;
            }
        }
    }
    close(fd);
}

int 
main(int argc, char const *argv[])
{
    /* code */
    int fd;
    struct dirent de;
    struct stat st;

    if(argc >= 3){
        printf("too much parameters!!!\n");
        exit(0);
    }

    if((fd = open(argv[1],O_RDONLY)) < 0){
        printf("find: can't open %s\n",argv[1]);
        exit(0);
    }

    // place an open file information into st
    if(fstat(fd, &st) < 0){
        printf("find: can't stat %s\n",argv[1]);
        close(fd);
        exit(0);
    }

    // find the filename from current directory to all sub-directory
    find(argv[1],fd,st,de,argv[2]);
    exit(0);


}
