#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "commands.h"

#define MAX_INPUT 512
#define MAX_MYPS1 64

/*char[MAX_MYPS1] MYPS1 = "iso$";

int main(int argc, char const *argv[])
{
	char[MAX_INPUT] input;

	do{
		myps1();
		create_process(scanf("%s"));

	}while(TRUE);
	return 0;
}*/

//BUSCA E TENTAR EXEC()

int main()
{
	char *input;
	char c;
	mypath();
	init_myps1();
	do{
		
		input = (char*) malloc (MAX_INPUT* sizeof(char));
		printf("%s", MYPS1);
		scanf("%[^\n]s", input);
		c = getchar();
		if(strcmp(input, "exit") == 0)
			exit(0);
		printf("GETCHAR:%d\n", c);
		
		//if(input[0] == ' '){
			create_process(input);
			//printf("bbb: %s\n", input);
		//}
		//else{
			//continue;
		//}
			free(input);

	}while(1);


	printf("%s", MYPATH);


	return 0;
}
