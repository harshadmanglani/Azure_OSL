#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    //fork a child process
    pid = fork();

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) { /* child process */
        printf("PID is %d\n", pid);
        execlp("/bin/ls","ls",NULL);
    }
    else { /* parent process */
    /* parent will wait for the child to complete */
        printf("Child is executing\n");
        printf("PID is %d\n", pid);
        sleep(10);
        printf("Child Complete");
    }
    return 0;

}