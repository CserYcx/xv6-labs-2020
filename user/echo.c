#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

/* Some information about the file descriptor:
   1. file descriptor 0 means the standard in
   2. file descriptor 1 means the standard out 
   3. file descriptor 2 means the standard error
*/

int
main(int argc, char *argv[])
{
  int i;

  for(i = 1; i < argc; i++){
    write(1, argv[i], strlen(argv[i]));
    if(i + 1 < argc){
      write(1, " ", 1);
    } else {
      write(1, "\n", 1);
    }
  }
  exit(0);
}
