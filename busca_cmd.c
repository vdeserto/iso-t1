#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void){
    char *MYPATH;
    char *value = "PATH";
    char *string; /*input cmd*/
    int i = 0;
    /*int j = 0;*/
    
    MYPATH = getenv(value);
    
    for(i = 0; i < strlen(MYPATH); i++){
        if(MYPATH[i] == ':'){
            MYPATH[i] = '\n';
            
        }

    }
    printf("%s\n", MYPATH);
    
    return 0;
}
