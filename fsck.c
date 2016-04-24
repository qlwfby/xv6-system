#include "types.h"
#include "stat.h"
#include "user.h"


int
main(int argc, char *argv[])
{
	  if(argc < 2){
	    printf(2, "Usage: fsck [a|b|c]...\n");
	    exit();
	  }
	  if(!strcmp(argv[1],"a")){
		  fsck();
	}else if(!strcmp(argv[1],"b")){

	}
  return 0;
}
