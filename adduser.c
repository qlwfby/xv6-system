#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "psw.h"

    int
    main(int argc, char *argv[])
    {
        if(argc < 3){
        	printf(2,"Usage: adduser <username> <password>");
        	exit();
        }
        char* user =argv[1];
        char* pwd =argv[2];
        struct psw t;
    	strcpy(t.username,user);
    	strcpy(t.password,pwd);
        char *path = "/psw";
        int uid=0;
        int fd =open(path, O_RDWR);
        struct psw tmp;
        int bytes;
        while((bytes=read(fd, &tmp, sizeof(tmp))) != 0){
        	uid++;
        }
        t.uid=uid;
        if((bytes=write(fd, &t, sizeof(t))!=sizeof(t))){
        	printf(2,"error: adduser fail");
        	return -1;
        }
        close(fd);
        exit();
    }
