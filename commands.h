#include <stdio.h>
#define PATH_MAX 256

char *MYPATH;
char *MYPS1;
char *caminho;/*caminho de retorno para o exec() */
char *args[32];/*argumentos passados pelo usuário */ 
char **ptrPath[32];
int qntArgs;
FILE *cmdp;
FILE *inpp;
FILE *outp;
FILE *errp;
FILE *histp;
int status;
char path[PATH_MAX];
int bgCount;/*checa se está em background */
int posOut;
int errCount;/*checa se o usuário pediu redirecionamento do erro para algum arquivo */
/* int inCount;-----> Não implementado */
int outCount;
int errPos;
int cod;/*código do histórico que fica incrementando */
int cd;/*change directory*/


int exists(const char *path);
char* splitPath(char *comando);
void splitInput(char* input);
void myps1();	
void create_process (char* caminho);
void mypath();
void edit_var(char* var, char* string);
void init_myps1();
void set_myps1(char* string);
void reorganize(int pos);
void red_out();
void manipInput(char* string);
void history(char* string);
void printHistory();
