#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "commands.h"


void create_process (char* string){
	char *caminho;
	int tam;
	int i;
	int iStatus;
	
	
	
	pid_t pid;
	tam = strlen(string);
	
	while(string[tam-1] == 32) /*
/*MUDEI PARA AQUI EM CIMA POIS SERVE PARA TODOS OS COMANDOS */
		tam--;
	
		
	splitInput(string);  /* aqui deu ruim */
	//printf("Antes de caminho: String eh %s\n", string);
	caminho = splitPath(args[0]);
	
	/*testes*/
	//printf("argumentos: %s e %s\n", *args[0], *args[1]);
	//printf("caminho: %s\n", caminho);
	
	
	pid = fork();
	
	//printf("VALOR DE PID:%s", caminho);
	
	if(pid < 0){ /*Se der erro */
		//fprintf(stderr, "%s\n", "Error");
		exit(-1);
	}
	else if(pid == 0){ /*processo filho */
		execv(caminho, args);
		int i = 1;
		//printf("Entrei no filho %d vezes\n", i);
		i++;
	//	exit(0);
	}
	else{ /*processo pai */
		if(string[tam-1] != '&'){
			//printf("SOU FOREGROUND\n");
			wait(NULL);
		}
		else{
		//printf("SOU BACKGROUND\n");
	//	exit(0);
		}
	}
	
}






// inicio da area para teste 
void splitInput(char *input){
	int i = 0;
	int j = 0;
	int k;
	char *transicao = (char*)calloc(32,sizeof(char));

	for(k = 0; k < strlen(input) || input[k] == '\n'; k++){
		transicao[i] = input[k];

		if(input[k+1] == 32 || input[k+1] == '\0') { // se encontrar espaço, separa
			if(transicao[i] != '&'){
			args[j] = transicao;
			//printf("Argumento[%d]:%s\n", j, args[j]);
			transicao = (char*)calloc(32,sizeof(char));
			i = -1;
			j++;
			k++;
			}
		}
		i++;
	}
	
	
	

	args[j] = (char*) 0;
	free(transicao);
}




char* splitPath(char *comando){  /*Função que faz split no MYPATH ao encontrar ':' */
	int i;
	int j = 0;
	int k = 0;
	char *caminhoAtual = (char*)calloc(64,sizeof(char));
	
	
	for(i=0; i < strlen(MYPATH); i++){
		caminhoAtual[j] = MYPATH[i];
		
		if(MYPATH[i] == ':'){
			caminhoAtual[j] = '/';
			ptrPath[k] = (char**)calloc(64,sizeof(char*));	
			*ptrPath[k] = caminhoAtual;
			caminhoAtual = (char*)calloc(64,sizeof(char));
			j=-1;
			k++;
		}
		j++;
	}
	
	caminhoAtual[j] = '/';
	caminhoAtual[j+1] = '\0';
	ptrPath[k] = (char**)calloc(64,sizeof(char*));	
	ptrPath[k] = &caminhoAtual;
	
	
	for(j=0;j <= k; j++){
		strcat(*ptrPath[j], comando);
		//printf("UM CAMINHO EH:%s\n", *ptrPath[j]);
	}
	for(j = 0; j <= k; j++){
		//printf("CAMINHO[%d]\n", j);
//	execv(*ptrPath[j], args);
		if(exists(*ptrPath[j])){
			//printf("Caminho[%d] = %s\n", j, *ptrPath[j]);
			free(caminhoAtual);
			return *ptrPath[j]; 
	
		}
	}
}

/*fim da area de teste */











/**
 * Function to check whether a file exists or not using
 * stat() function. It returns 1 if file exists at 
 * given path otherwise returns 0.
 */

int exists(const char *path)
{
    struct stat sb;

    if( stat(path, &sb) == 0)
    	return 1;
    else
    	return 0;

    // Check for file existence
  //  if (stats.st_mode & F_OK)
  //      return 1;

    //return 0;
}


/*
 * Check if a file exist using fopen() function
 * return 1 if the file exist otherwise return 0
 */
/*int exists(const char * filename){
   
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
} */





void mypath(){
	char *name = "PATH";
	
	MYPATH = getenv(name);
}

void init_myps1(){
	MYPS1 = "iso$";
}

void set_myps1(char* string){
	
	MYPS1 = string;
}