#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "commands.h"

#define MAX_INPUT 512
#define MAX_MYPS1 64

char[MAX_MYPS1] MYPS1 = "iso$";

int main(int argc, char const *argv[])
{
	char[MAX_INPUT] input;
	
	do{
		myps1();
		create_process(scanf("%s"));

	}while(TRUE);
	return 0;
}