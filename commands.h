#include <stdio.h>

char *MYPATH;
char *MYPS1;
char *caminho;
char *args[16];
char **ptrPath[32];

int exists(const char *path);
char* splitPath(char *comando);
void splitInput(char* input);
void myps1();	
void pwd();
void create_process (char* string);
void executar(char* string);
void mypath();
void edit_var(char* var, char* string);
void init_myps1();
void set_myps1(char* string);