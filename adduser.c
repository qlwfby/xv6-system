#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
    int
    main(int argc, char *argv[])
    {
        if(argc < 2){
        	printf(2,"Usage: adduser <username>");
        	exit();
        }
        int fd;
        char *name = argv[1];
        char *path = "/passwd";
        if((fd = open(path, O_RDWR)) < 0) {
            printf(2, "error: cannot open %s\n", path);
            exit();
        }
        write(fd, name, strlen(name));
        close(fd);
        exit();
    }
