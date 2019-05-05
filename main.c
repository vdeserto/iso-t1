#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

//#include "commands.h"

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




int main(void)
{
	char input[MAX_INPUT];
	FILE *arquivo;

	do{
		scanf("%s", input);

		//Separar os argumentos
		i=0;
		j=0;
		contador=0;
		while(input[i] != '/n'){
            if(input[i] != '/0'){
                argumento[j] = input[i];
                i++;
                j++;
            }
            else{
                contador++;
                v[contador][0] = input[i];
                v[contador][1] = input[i+1];
                i=i+2;
                j=0;
            }
		}
        if(contador == 0)
            create_process(input);
        else if(contador == 1)
            create_process(input, v[0]);
        else if(contador == 2)
            create_process(input, v[0], v[1]);
        else if(contador == 3)
            create_process(input, v[0], v[1], v[2]);
        else if(contador == 4)
            create_process(input, v[0], v[1], v[2], v[3]);

	}while(1);

	printf("%s", $PATH);


	return 0;
}
