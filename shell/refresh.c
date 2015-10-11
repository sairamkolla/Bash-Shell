#include "everything.h"
void start(char *bome){
	struct utsname myinfo;
	uname(&myinfo);
	printf("[");
	printf("%s@%s",getlogin(),myinfo.nodename);
	printf(" ");
	char cwd[1024];
	bzero(cwd,sizeof(cwd));
	getcwd(cwd,sizeof(cwd));
	if(strcmp(cwd,bome)==0)
		printf("~ ] ");
	else
		printf("%s ] ",cwd);
	return;
}
