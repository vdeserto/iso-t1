#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "commands.h"

void myps1(){
	printf("%s\n", MYPS1);
}

void create_process(char* string){
	Pid_t pid;
	pid = fork();
	if(pid < 0){
		fprintf(stderr, "%s\n", "Error");
		exit(-1);
	}
	else if(pid == 0){
		try_exec(&string);
	}
	else{
		wait(NULL);
		printf("%s\n", child exec has finished);
		exit(0);

	}
}

void try_exec(char* string){
	if(binary_search(&string)){  /*inverter e fazer a busca primeiro */
		execpl("/bin/%s", "%s", NULL);
	else
		return;
	}

}
