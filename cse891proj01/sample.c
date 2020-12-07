#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main () {
	FILE *file_pointer = fopen("./web/index.html", "rb");
	if (!file_pointer){
			perror("The file was not opened");
			exit(1);
			
			}
		printf("The file was opened");
		fseek(file_pointer, 0, SEEK_END);
		long file_length = ftell(file_pointer);
		fseek(file_pointer, 0, SEEK_SET);
		printf("The file size is: %d", file_length);
		char buffer[file_length];
		fread(buffer, sizeof(buffer), 1, file_pointer);
		printf("%s", buffer);
   return 0;
   }
