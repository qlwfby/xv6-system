// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
//#include "defs.h"

char *argv[] = { "sh", 0 };
int
getuser(char *buf, int nbuf)
{
  memset(buf, 0, nbuf);
  gets(buf, nbuf);
  if(buf[0] == 0) // EOF
    return -1;
  return 0;
}
int
getpwd(char *buf, int nbuf)
{
  memset(buf, 0, nbuf);
  gets(buf, nbuf);
  if(buf[0] == 0) // EOF
    return -1;
  return 0;
}
//int verifyuser(char *user,char *pwd){

//}
int getuserid(char *user){
 return 0;
}
int
main(void)
{
  int pid, wpid;

  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr
  static char user[100];
  static char pwd[100];
  // Set up password and create passwd file
  printf(1,"Set up root password:");
  getpwd(pwd, sizeof(pwd));
  char *path="/passwd";
  char *usr="root:123:0";
  int fd=open(path,O_CREATE);
  if(write(fd,usr,strlen(usr))<0)
	  printf(2,"create password file error\n");
  for(;;){
	printf(1, "Login:");
	getuser(user, sizeof(user));
	printf(1, "Password:");
	getpwd(pwd, sizeof(pwd));
	//int verify= verifyuser(user,pwd);
	int uid = getuserid(user);
    printf(1, "init: starting sh\n");
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      setuid(uid);
      exec("sh", argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}
