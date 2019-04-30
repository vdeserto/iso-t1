#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	char *ptr;
	
	char *name = "PATH";	

	ptr = getenv(name);

	printf("%s", ptr);

	return 0;
}
