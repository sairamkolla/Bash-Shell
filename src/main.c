#include "headers/everything.h"
#include "headers/refresh.h"
#include "headers/tokenize.h"
#include "headers/execution.h"
char home[100];
void describe(char **a){
	int i;
	for(i=0;a[i]!=NULL;i++)
		printf("%d--> %s\n",i,a[i]);
	return ;
}
void handle_signal(int signo){
	//printf("%d\n",signo);
	printf("\n");
	start(home);
	fflush(stdout);
	return ;

}
void free_shit1(char **a){
	int i=0;
	for(i=0;a[i]!=NULL;i++){
		free(a[i]);
		a[i]=NULL;
	}
	return ;
}
int main(){
	//strcat(home,getlogin());
	getcwd(home,sizeof(home));
	signal(SIGINT, SIG_IGN);
	signal(SIGINT,handle_signal);


	char line[100];
	bzero(line,sizeof(line));
	int index=0,i;

	//**************** Delimiters
	char collen[2]=";";
	char space[2]=" ";
	char pipesymbol[2]="|";
	//******************* End of Delimiters

	//********** pipes,arguments,multiplecommands
	char **mult;
	char **args;
	char **pipe_parts;
	//***********
	int no_of_args;
	start(home);
	char c='\0';
	char exitcommand[5]="exit";
	while(c!=EOF){
		c=getchar();
		switch(c){
			case '\n':
				if(!line[0]=='\0'){
					tokenize(line,&mult,collen);

					for(i=0;mult[i]!=NULL;i++){
						if(strcmp(mult[i],exitcommand)==0)
							goto bye;

						//Assignment phase 2

						tokenize(mult[i],&pipe_parts,pipesymbol);
						//describe(pipe_parts);
						fork_pipes(pipe_parts,home);
						free_shit1(pipe_parts);

						//Assignment Phase 1
				
						//tokenize(mult[i],&args,space);
						//no_of_args=count_args(args);
						//final(args,home);
						
					}
					free_shit1(mult);

					index=0;
					bzero(line,sizeof(line));
				}
				start(home);
				break;
			default:
				line[index++]=c;	
		}


	}
	printf("\n");
bye:
	printf("Bye Bye!!\n");
	return 0;
}
