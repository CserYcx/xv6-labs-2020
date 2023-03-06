#include "kernel/types.h"
#include "kernel/fs.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"

/* Simple version find: its format is find <path> <filename>*/
// The key is how to solve the file name in current directory

void find(const char *path, int fd, struct stat st,const char *filename){
    char buf[512],*p;
    struct dirent de;
    //printf("type is %d\n", st.type);
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)){
        printf("find: the path is too long\n");
    }
    if(strcmp(de.name,".") == 0 || strcmp(de.name, "..") == 0)
        printf("%s\n",filename);
    if(st.type != T_DIR){
        printf("find: can't find in %d type file\n",st.type);
        exit(0);
    }
    else{
        // read all the file under the directory
        while(read(fd,&de,sizeof(de)) == sizeof(de)){
            if(de.inum == 0)
                continue;
            // here will be a bug, if find need to find '.'/'..', it will skip it
            if(stat(de.name,&st) < 0){
                printf("find: can't fstat %s\n",de.name);
            }
            switch (st.type)
            {
            case T_FILE :
                if(strcmp(de.name, filename) == 0)
                    printf("%s/%s\n",path,filename);
                break;
            // i need to show the complete path
            case T_DEVICE:
                if(strcmp(de.name, filename) == 0)
                    printf("%s/%s\n",path,filename);
                break;
            //! \note directory is also a file!!!!
            case T_DIR:
                printf("de.name is %s\n",de.name);
                if(strcmp(de.name,".") == 0 || strcmp(de.name, "..") == 0)
                    break;
                if(strcmp(de.name, filename) == 0)
                    printf("%s/%s\n",path,filename);
                strcpy(buf,path);
                p = buf + strlen(buf);
                *p++ = '/';
                memmove(p,de.name,DIRSIZ);
                //! \bug may be here will change the st.type 
                // recursively to find the file in each sub directory
                int newfd = open(buf,O_RDONLY);
                if(newfd < 0){
                    printf("find: can't open %s\n",buf);
                }
                find(buf,newfd,st,filename);
                close(newfd);
                break; 
            default:
                fprintf(2, "that's a error\n");
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
    struct stat st;

    if(argc > 3){
        printf("too much parameters!!!\n");
        exit(0);
    }
    
    if(argc < 3){
        printf("need more parameters!!!\n");
        exit(0);
    }

    if((fd = open(argv[1],O_RDONLY)) < 0){
        printf("find: can't open %s \n",argv[1]);
        exit(0);
    }

    // place an open file information into st
    if(fstat(fd, &st) < 0){
        printf("%s%dfind: can't stat %s\n",argv[1],__FILE__,__LINE__);
        close(fd);
        exit(0);
    }
    
    // find the filename from current directory to all sub-directory
    find(argv[1],fd,st,argv[2]);
    exit(0);


}
