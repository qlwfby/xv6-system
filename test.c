#include "types.h"
#include "user.h"
#include "date.h"
#include "types.h"
#include "user.h"
#include "fcntl.h"

#define N 100
#define MAXNAME 32
#define MAXPSW  32
struct psw {
	char username[MAXNAME];
	uint uid;
	char password[MAXNAME];
};

void save(char *username, char *password) {
	int fd;
	struct psw t;
	strcpy(t.username,username);
	strcpy(t.password,password);
	t.uid = 0;
	fd = open("psw", O_CREATE | O_RDWR);
	if (fd >= 0) {
		printf(1, "ok: create psw file succeed\n");
	} else {
		printf(1, "error: create psw file failed\n");
		exit();
	}

	int size = sizeof(t);
	if (write(fd, &t, size) != size) {
		printf(1, "error: write to psw file failed\n");
		exit();
	}
	printf(1, "write %s ok\n", username);
	close(fd);
}

void load(char *username, char *password) {
	int fd;
	struct psw t;

	fd = open("psw", O_RDONLY);
	if (fd >= 0) {
		printf(1, "ok: read psw file succeed\n");
	} else {
		printf(1, "error: read psw file failed\n");
		exit();
	}
	int size = sizeof(t);
	if (read(fd, &t, size) != size) {
		printf(1, "error: read from psw file failed\n");
		exit();
	}
	username = t.username;
	password = t.password;
	printf(1, "file contents name %s and psw %s\n", username, password);
	printf(1, "read ok\n");
	close(fd);
}

int main(void) {
	struct psw t;
	char username[MAXNAME];
	char password[MAXPSW];
	int fd = open("psw", O_RDONLY);
	if (fd == -1) {
		printf(1, "please enter a create user name:\n");
		gets(username, MAXPSW);
		username[strlen(username) - 1] = '\0';
		printf(1, "please enter a new password:\n");
		gets(password, MAXPSW);
		password[strlen(password) - 1] = '\0';
		save(username, password);
	} else {
		int size = sizeof(t);
		if (read(fd, &t, size) != size) {
			printf(1, "error: read from psw file failed\n");
			exit();
		}
		printf(1, "file contents name %s and psw %s\n",t.username, t.password);
		printf(1, "read ok\n");
	}
	close(fd);
	exit();
}
