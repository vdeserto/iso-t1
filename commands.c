#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "commands.h"

/*void myps1(){
	printf("%s:", MYPS1);
	pwd();
}

void pwd(){
	char[4] string = "pwd";
	create_process(string);
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
	if(binary_search(&string))  /* inverter e fazer a busca primeiro */
//		execpl("/bin/ls", "%s", NULL);
//	else
/*		return; */
//}


void create_process (char* string){
	Pid_t pid;
	pid = fork();
	if(pid < 0){
		fprintf(stderr, "%s\n", "Error");
		exit(-1);
	}
	else if(pid == 0) /*processo filho */
		try_exec(string);
	else{/*processo pai */
		for(int i=0; string[i] == '&' || string[i] != '\0'; i++){
			wait(NULL);
		}
		
		exit(0);
	}
}

void try_exec(char* string){
	


}
