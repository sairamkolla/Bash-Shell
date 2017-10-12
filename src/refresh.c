#include "headers/everything.h"
void start(char *bome){
    struct utsname myinfo;
    uname(&myinfo);
    printf("[");
    char *username;
    username=(char *)malloc(10*sizeof(char));
    cuserid(username);
    printf("%s@%s",username,myinfo.nodename);
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
