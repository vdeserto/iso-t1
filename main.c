#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <errno.h>
#include "commands.h"

#define MAX_INPUT 512
#define MAX_MYPS1 64

int main()
{
	char *input;
	size_t inSize = MAX_INPUT;
	size_t characters;
	int i;
	mypath();
	init_myps1();

	do{

		input = (char*) calloc (64, sizeof(char));

		printf("%s", MYPS1);

		characters = getline(&input, &inSize, stdin);
		
		for(i=0;i < characters;i++);
		input[i-1] = 0;
		qntArgs = 0;
		history(input);
		
		if(strcmp(input, "history") == 0)
			printHistory();	

		if(strcmp(input,"exit") == 0)
			exit(0);
		
		else if(input[0] > 32){
			manipInput(input);
		}
		if(input[0] >= 32){
			free(input);
		}

		for(i=0;i<qntArgs;i++){
			free(args[i]);
		}
		args[i] = NULL;
	

	}while(1);


	return 0;
}
