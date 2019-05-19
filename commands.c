#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "commands.h"


void manipInput(char *string){
	int tam = strlen(string);
	int j = 0;
	int inPos = 0;
	bgCount = 0;
	/*inCount = 0; Não implementado*/
	outCount = 0;
	cd = 0;
	
	errCount = 0;
	
	while(string[tam-1] == 32)/*Se houver 'space', o tamanho da string eh reduzida*/
		tam--;
	
	splitInput(string); /*args*/	
	
	if(qntArgs == 2){/*Casos onde geralmente tem 2 argumentos*/
		if(strcmp(args[1], "&") == 0){
			bgCount++;
			args[1] = (char*)0; 
			qntArgs--;
		}
		
		if(strcmp(args[j],"cd") == 0){
				cd++;
				if(args[j+1] <= " " && (strcmp(args[j+1], ">") == 0 || strcmp(args[j+1], "<") == 0 ) )	{
					cd++;
				}
				else{
					chdir(args[j+1]);/*SYSTEM CALL DO CD = CHANGE DIRECTORY*/
					return;
				}
		}
		if(strcmp(args[j], ">") == 0){
				outCount++;
				if(args[j+1] <= " " && (strcmp(args[j+1], ">") == 0 || strcmp(args[j+1], "<") == 0 ) )
					outCount++;
		}
	}
		
	
	else if(qntArgs > 2){/*Casos onde tem mais de 2 argumentos*/
		for(j=0;j<qntArgs;j++){
			
			/*if(strcmp(args[j], "<") == 0){
			 *	inCount++;
			 *	if(args[j+1] <= " " && (strcmp(args[j+1], ">") == 0 || strcmp(args[j+1], "<") == 0 ) )
			 *		inCount++;
			 *	else
			 *		inPos = j+1;
			}*
			 * Não implementado
			 */
		
					
			if(strcmp(args[j], "2>") == 0){
				errCount++;
				if(args[j+1] <= " " && (strcmp(args[j+1], ">") == 0 || strcmp(args[j+1], "<") == 0 ) )
					errCount++;
				else
					errPos = j+1;
			}
			
			
			if(strcmp(args[j], ">") == 0){
				outCount++;
				if(args[j+1] <= " " && (strcmp(args[j+1], ">") == 0 || strcmp(args[j+1], "<") == 0 ) )
					outCount++;
				else
					posOut = j+1;
			}
			
			if(strcmp(args[j], "&") == 0){
				bgCount++;
				reorganize(j);
			}
		}/*fim do for*/
	}/*fim do if */
	
	if(errCount == 1)
		errp = fopen(args[errPos], "w+");

	
	caminho = splitPath(args[0]);/*separando caminhos*/
	
	
	if((outCount == 0 && errCount == 0) /*&& inCount == 0*/){
		create_process(caminho);
		return;
	}	
	
	
	if(outCount > 1 && errCount == 1)
		fprintf(errp, "%s\n", strerror(errno));
	else if(outCount > 1 && errCount != 1)
		fprintf(stderr, "%s\n", strerror(errno));
	else if(outCount == 1)
		red_out();
	/**
	if(inCount > 1 && errCount == 1)
	 *	fprintf(errp, "%s\n", strerror(errno));
	else if(inCount > 1 && errCount != 1)
	 *	fprintf(stderr, "%s\n", strerror(errno));
	else if(inCount == 1)
	 *	red_in(inPos,caminho);
	 *
	 * 	Não implementado	 
	 */	

	if(errCount == 1)
		fclose(errp);

}

/** Armazenamento persistente do histórico de processos,
 * não foi implementado os 50 últimos
 */
void history(char* string){
	int cod;
	FILE* escrita;
	char lixo;
	
	if(string[0] > 32){
		histp = fopen("history.txt", "r");
		if(histp == NULL){
			histp = fopen("history.txt", "w+");
			if(histp == NULL){
				fprintf(stderr, "%s\n", strerror(errno));
			}
			else{
				cod = 1;
				fprintf(histp,"   %d   %s\n", cod, string);
				fclose(histp);
			}/*fim do modo de primeira escrita */
		}
		else{
			int x;
			do{
				x = fscanf(histp, " %d", &cod);
				while(fgetc(histp) != '\n');
				if(x != EOF)
					 x = fgetc(histp);
				
			}while(x != EOF);
			cod++;
			fclose(histp);
			histp = fopen("history.txt", "a");
			fprintf(histp,"   %d   %s\n", cod, string);
			fclose(histp);
			
		}
	
	}
		
}

/** Acesso ao histórico de processos, 
 *  imprimindo o arquivo armazenado
 */ 
void printHistory(){
	FILE *entrada;
	
	entrada = fopen("history.txt", "r");
	
	if(entrada == NULL)
		fprintf(stderr, "%s\n", strerror(errno));
	else{
		char a;
		do{
		a = fgetc(entrada);
			if(a != EOF)
				fprintf(stdout,"%c", a);
		}while(a != EOF);
	}
	fclose(entrada);
	
	
	
}



/** Criação de processos
 *  após separação de argumentos e diretórios
 */
void create_process (char* caminho){
		
	int i;
	pid_t pid;
	

	pid = fork();
	
	if(pid < 0){ /*Se der erro */
		fprintf(stderr, "%s\n", strerror(errno));
		exit(-1);
	}
	else if(pid == 0){ /*processo filho */
		execv(caminho, args);
	}
	else{ /*processo pai */
		if(bgCount == 0){
			wait(NULL);
			
		}
		else if(bgCount == 1){
		fprintf(stdout, "%d\n", getpid());

		}
	return;
	}
	
}

/** Eu realmente não consegui implementar a
 * entrada para comandos e/ou programas
 * por isso vou deixar comentado 
 *
 *	void red_in(int inPos, char* caminho){
 *		int x;
 *		char string[1024];
 *		char pointer[1024];
 *		inpp = fopen(args[inPos], "r");
 *		FILE* cmd;
 *	
 *	
 *		execvp(caminho,args);
 *	
 *	}
 */




void red_out(){/*Redirecionamento output*/
	int k = 1;
	int pos;
	char c;
	char exec[64];
	FILE* create;
	
	strcpy(exec, args[0]);
	
	if(strcmp(args[0], ">") == 0 && args[1] > " "){
		create = fopen(args[1], "w");
		fclose(create);
		return;
	}
	
	while(args[k] != ">" && args[k] != NULL){/*unindo os argumentos para execução*/
		strcat(exec, " ");
		strcat(exec, args[k]);
		k++;
	}
	cmdp = popen(exec, "r");
	
	if(cmdp == NULL)
		fprintf(stderr, "%s\n", strerror(errno));
	

	for(k = 0; k < qntArgs; k++){/*encontrar a posicao do argumento '>' */
		if(strcmp(args[k],">") == 0){
			pos = k; 
			reorganize(pos);
		}
	}

		outp = fopen(args[pos], "w+");
		if(outp != NULL)
		c = fgetc(cmdp);
            while (c != EOF) {    /*EOF - caracter de final de arquivo*/
                
                fputc(c, outp);
                
                c = fgetc(cmdp);
            }
	status = pclose(cmdp);			
	fclose(outp);
	if(status == -1)
		fprintf(stderr, "%s\n", strerror(errno));

}	


void reorganize(int pos){
	int count;
	
		for(;pos < qntArgs-1; pos++){ 
			strcpy(args[pos],args[pos+1]);
		}
		args[pos] = (char*) 0;

	qntArgs--;
	
}


void splitInput(char *input){
	int i = 0;
	int j = 0;
	int k;
	char *transicao = (char*)calloc(32,sizeof(char));

	for(k = 0; k < strlen(input) || input[k] == '\n'; k++){
		transicao[i] = input[k];

		if(input[k+1] == 32 || input[k+1] == '\0') { /* se encontrar espaço ou NULL, separa*/
			
			args[j] = transicao;
			transicao = (char*)calloc(32,sizeof(char));
			i = -1;	/* pelo incremento fora do if */
			j++;
			k++;
			
		}
		i++;
	}
	
	
	

	args[j] = (char*) 0; /* o ultimo argumento necessariamente deve ser null */
	free(transicao); /* libera espaço em memoria */
	qntArgs = j; /*quantidade de argumentos visiveis atribuindo a posicao do ultimo argumento*/
}



/** Função que faz split no MYPATH ao encontrar ':'
 * direto da variável de ambiente PATH
 */
char* splitPath(char *comando){  
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
	}
	for(j = 0; j <= k; j++){

		if(exists(*ptrPath[j])){
			free(caminhoAtual);
			return *ptrPath[j]; 
	
		}
		else if (j == k && exists(*ptrPath[j]) == 0 ){
			if(errCount == 1){
				fprintf(errp, "%s\n", strerror(errno));
			}
			else
				fprintf(stderr, "%s\n", strerror(errno));
			return (char*) 0;
		}
	}
}


/**
 * Função para checar se um arquivo existe ou não usando
 * a função stat(). O retorno é 1 se o arquivo existe
 * ao diretório indicado, caso contrário, retorno 0.
 */

int exists(const char *path)
{
    struct stat sb;

    if( stat(path, &sb) == 0)
    	return 1;
    else
    	return 0; 
}




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
