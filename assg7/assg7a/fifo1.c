#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#define FIFO_NAME_1 "./fifo_1"
#define FIFO_NAME_2 "./fifo_2"
int main()
{
    char readbuffer[1000];
    FILE *fp;
    mkfifo(FIFO_NAME_2, 0777);
    fp = fopen(FIFO_NAME_1, "w");
    printf("Enter the text (; to stop):\n");
    scanf("%[^;]s", readbuffer);
    fprintf(fp, "%s", readbuffer );
    printf("Written text to FIFO 1\n");
    fclose(fp);
    printf("Waiting to read from FIFO 2.\n");
    fp = fopen(FIFO_NAME_2, "r");
    fscanf(fp, "%[^;]s", readbuffer);
    printf("Read answer to FIFO 2\n");
    printf("%s\n",readbuffer );
    fclose(fp);

    exit(EXIT_SUCCESS);
}