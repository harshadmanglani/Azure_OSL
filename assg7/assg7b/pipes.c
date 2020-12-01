#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// 0-read
// 1-write
int main(int argc, char const *argv[])
{
    int pipefd1[2];
    int pipefd2[2];
    pid_t cpid;
    char buf;
    char path[50];
    char readbuffer[50];
    FILE *fp;
    pipe(pipefd1);
    pipe(pipefd2);

    cpid = fork();
    if (cpid == 0)
    { //Child reads from pipe
        close(pipefd1[1]); //Close write end of pipe 1 (getting ready for reading)

        printf("Reading filename from pipe 1\n");
        path[read(pipefd1[0], path, 50)] = '\0'; //get the data into path[]
        printf("Reading contents of \"%s\"\n",path );
        fp = fopen(path, "r");
        if(fp == NULL)
        printf("File failed to open\n");
        else
        while(fgets(readbuffer, 50, fp)!= NULL);

        fclose(fp);
        close(pipefd1[0]); //close read end of pipe 1
        close(pipefd2[0]); //close read end of pipe 2 (getting ready for writing)
        printf("Writing contents of \"%s\" in pipe 2 \n", path);
        write(pipefd2[1], readbuffer, strlen(readbuffer));
        close(pipefd2[1]); //close write end of pipe 2
        _exit(EXIT_SUCCESS);
        }

    else //Parent Process
    {
        close(pipefd1[0]); //close read end of pipe 1 (getting ready for writing)
        printf("Writing filename \"%s\" to pass to child process in pipe 1\n", argv[1]);
        write(pipefd1[1], argv[1], strlen(argv[1]));
        close(pipefd1[1]); //close write end of pipe 1
        printf(".....Waiting for child to finish......\n");
        wait(NULL); /* Wait for child */
        printf(".......Child has finished........\n");

        close(pipefd2[1]); //close write end if pipe2 (getting ready for reading)
        printf("Reading the file contents from pipe 2\nContents are:\n");
        while (read(pipefd2[0], &buf, 1) > 0)
        write(STDOUT_FILENO, &buf, 1);
        write(STDOUT_FILENO, "\n", 1); //write() will directly print to console
        close(pipefd2[0]); //close read end of pipe2
        exit(EXIT_SUCCESS);
    }
return 0;
}