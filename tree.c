#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

int
main(int argc, char *argv[])
{
	  if(argc < 2){
	    printf(2, "Usage: tree [path]...\n");
	    exit();
	  }
	  if(!isdir(argv[1])){
		  printf(2, "%d is not a directory", argv[1]);
	  }
	  int fd = open(argv[1],O_RDONLY);
	  if(fd<0)
		  return -1;
	  struct dirent dir;
	  while(read(fd,&dir,sizeof(dir))!=0){
		  printf(1,dir.name);
	  }
  return 0;
}
