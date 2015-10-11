#include "everything.h"
void nullify(char **a){
	int i=0;
	for(i=0;i<10;i++)
		a[i]=NULL;
	return ;
}
void tokenize(char *reference,char ***aaa,char *delim){
	char **result;
	*aaa=(char **)malloc(10 * sizeof(char *));
	result=*aaa;
	nullify(result);
	int index=0;
	char *token;
	char *dummy=malloc(sizeof(char)*strlen(reference)+1);
	strcpy(dummy,reference);
	token=strtok(dummy,delim);
	while(token!= NULL){
		result[index]=(char*)malloc(sizeof(char)*strlen(token)+1);
		strcpy(result[index++],token);
		token=strtok(NULL,delim);
	}
	free(dummy);
	dummy=NULL;
	return;
}
