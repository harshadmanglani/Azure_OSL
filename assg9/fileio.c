#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	char c;
	int op, rd, wr, option, len;
	char buffer[2048], name[100];
	do
	{
		printf("\n\nMENU\n1. Open a file\n2. Write file\n3. Read contents of the file\n0. Exit\n----------------------------\n");
		scanf(" %d", &option);
		switch(option)
		{
			case 1: 
				printf("Enter the name of the file: ");
				scanf("%s", name);
				op = open(name, O_CREAT);
				close(op);
				break;

			case 2: 
				wr = open(name, O_WRONLY);
				printf("Enter the content:\n");
				scanf(" %[^\n]s", buffer);
				write(wr, buffer, strlen(buffer));
				close(wr);
				break;

			case 3: 
				rd = open(name, O_RDONLY);
				read(rd, buffer, 2048);
				printf("Contents of the file are:\n%s", buffer);
				close(rd);
				break;

			default: 
			case 0: 
				break;
		}
	}while(option);
}