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
    int words = 0, lines = 0;
    mkfifo(FIFO_NAME_1, 0777);
    FILE *fp;
    printf("Waiting to read from FIFO 1.\n");
    fp = fopen(FIFO_NAME_1, "r");
    fscanf(fp, "%[^;]s", readbuffer);
    printf("Read text from FIFO 1\n");
    fclose(fp);
    printf("%s\n",readbuffer );
    for (int i = 0; i < strlen(readbuffer); ++i)
    {
        if(readbuffer[i] == ' ')
        words++;
        else if(readbuffer[i] == '\n')
        lines++;
    }
    fp = fopen(FIFO_NAME_2, "w");
    fprintf( fp, "Words: %d\nLines: %d\nCharacters: %ld\n",words+lines, lines,
    strlen(readbuffer) );
    printf("Written answer to FIFO 2\n");
    printf("Words: %d\nLines: %d\nCharacters: %ld\n",words+lines, lines,
    strlen(readbuffer) );
    fclose(fp);
    exit(EXIT_SUCCESS);
}