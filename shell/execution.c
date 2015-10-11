#include "everything.h"
#include<fcntl.h>
#include "tokenize.h"
//char home11[100]="/home/";
void free_shit(char **a){
	int i;
	for(i=0;a[i]!=NULL;i++){
		free(a[i]);
		a[i]=NULL;
	}
	return ;
}
int count_args(char **a){
	int i,count=0;
	for(i=0;a[i]!=NULL;i++)
		count++;
	return count;
}
void final(char **command,char *home11,int no_of_args);
void spawn_proc (int in, int out, char *singlepipe,char *home){//struct command *cmd)
	pid_t pid;
	char space[2]=" ";
	pid=fork();
	if(pid== 0){
		if (in != 0){
			dup2(in, 0);
			close(in);
		}
		if (out != 1){
			dup2 (out, 1);
			close (out);
		}
		char **args;
		tokenize(singlepipe,&args,space);
		int no_of_args=count_args(args);
		final(args,home,no_of_args);
		//int status=0;
		//execvp(args[0],(args));
		free_shit(args);
		_exit(0);
	}
	else{
		wait(0);
	}
	return ;
}
void fork_pipes (char **command,char *home)
{
	int i;
	pid_t pid;
	int ino=dup(0);
	int outo=dup(1);
	int in, fd [2];
	char **args;
	char space[2]=" ";
	in = 0;
	for (i = 0; command[i+1]!=NULL; i++){
		if(pipe(fd)==-1)
			printf("pipe error\n");
		spawn_proc(in,fd[1],command[i],home);

		close(fd[1]);
		//printf("%s is sucessfully executed\n",command[i]);
		in=fd[0];
	}
	if (in != 0)
		dup2(in, 0);
	tokenize(command[i],&args,space);
	int no_of_args=count_args(args);
	final(args,home,no_of_args);
	free_shit(args);
	/*pid=fork();
	  if(pid==0){
	  tokenize(command[i],&args,space);
//execvp(args[0],(args));
free_shit(args);
_exit(0);
}*/
	dup2(ino,0);
	dup2(outo,1);
	close(ino);
	close(outo);
	return;
	}
void present_direc(){
	char cwd[100];
	printf("%s\n",getcwd(cwd,sizeof(cwd)));
	return;
}
void final(char **command,char *home11,int no_of_args){
	//printf("aaa\n");
	char pwd[4]="pwd";
	char cd[3]="cd";
	char echo[5]="echo";
	int arg_i=1;
	int is_background=0;
	char andand[2]="&";
	int is_gthan=0;
	int is_lthan=0;
	char greaterthan[2]=">";
	char lessthan[2]="<";
	char append[3]=">>";
	char outputfile[50];
	int append1=0;
	int ino,outo;
	ino=dup(0);
	outo=dup(1);
	char inputfile[50];
	if(strcmp(command[no_of_args-1],andand)==0){
		is_background=1;//printf("Background\n");
		command[no_of_args-1]=NULL;
		no_of_args--;
	}
	//redirecting output
	if(no_of_args>=3)
		if(strcmp(command[no_of_args-2],greaterthan)==0){
			strcpy(outputfile,command[no_of_args-1]);
			is_gthan=1;
			command[no_of_args-1]=NULL;
			command[no_of_args-2]=NULL;
			no_of_args-=2;
			int outputfp = open(outputfile, O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);	
			dup2(outputfp,1);
			close(outputfp);
		}
	if(no_of_args>=3)
		if(strcmp(command[no_of_args-2],append)==0){
			strcpy(outputfile,command[no_of_args-1]);
			append1=1;
			command[no_of_args-1]=NULL;
			command[no_of_args-2]=NULL;
			no_of_args-=2;
			int outputfp = open(outputfile, O_RDWR|O_CREAT|O_APPEND, 0600);	
			dup2(outputfp,1);
			close(outputfp);
		}
	//redirecting input
	if(no_of_args>=3)
		if(strcmp(command[no_of_args-2],lessthan)==0){
			strcpy(inputfile,command[no_of_args-1]);
			is_lthan=1;
			command[no_of_args-1]=NULL;
			command[no_of_args-2]=NULL;
			no_of_args-=2;
			int inputfp=open(inputfile,O_RDONLY);
			dup2(inputfp,0);
			close(inputfp);
		}
	//if(is_gthan)
	//	printf("output file is %s\n",outputfile);
	//if(is_lthan)
	//	printf("input file is %s\n",inputfile);

	//int status=0;
	if(strcmp(command[0],pwd)==0)
		present_direc();
	else if( strcmp(command[0],cd)==0){
		if(command[1]==NULL || command[1][0]=='~'){
			printf("%s\n",home11);
			command[1]=(char*)malloc((strlen(home11)+1)*sizeof(char));
			strcpy(command[1],home11);

			//printf("%s\n",home11);
		}
		//printf("%s\n",command[1]);	
		if(chdir(command[1])!=0)
			printf("The Specifed Path Doesn't exist\n");
		else
			printf("sucess\n");

	}
	else if(strcmp(command[0],echo)==0){
		while(command[arg_i]!=NULL){
			printf("%s ",command[arg_i]);
			arg_i++;
		}		
		printf("\n");
	}
	else{
		pid_t pid,wpid;
		pid=fork();
		if(pid==0){
			if(execvp(command[0],(command))==-1){
				perror("error\n");
				printf("sssssss\n");	
				exit(EXIT_FAILURE);
			}
		}
		else if (pid<0)
			perror("shit!!");
		else{
			if(!is_background){
				/*do {
				  waitpid(pid, &status, WUNTRACED);
				  } while (!WIFEXITED(status) && !WIFSIGNALED(status));*/
				wait(NULL);
			}
			is_background=1;
		}
	}
	dup2(ino,0);
	dup2(outo,1);
	close(ino);
	close(outo);
	return ;
}
