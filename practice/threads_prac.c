#include <pthread.h>
#include <stdio.h>

void *func(void *param);

int main()
{
    pthread_t tid;
    printf("Creating and passing the thread\n");
    pthread_create(&tid, NULL, func, "in the thread func");
    pthread_join(tid, NULL);
    printf("The thread is executing\n");
    printf("The thread func is done with its execution\n");
    printf("Done with main\n");
}

void *func(void *param)
{
    printf("\n\n");
    printf("first thread func statement\n");
    char *str = (char*)param;
    printf("%s\n", str);
    printf("\n\n");
    pthread_exit(0);
}

/*
INTERVIEW EXPERIENCE - Credit Suisse Internship for June 2021
The entire process was online, and the interviews took place on Zoom video calls.
There were two rounds in the interview - a technical round and an HR round.
These are the questions I was asked in the technical round:
1. Introduce yourself - I mentioned my internship as an app dev and the student ambassador program, so he asked follow up questions wrt both of these.
2. Explain OOP to me if I have no CS background - Tubelight - switchboard is the interface.
3. Name a few Data Structures and their real life use cases - Stacks in recursion, Queues in CPU scheduling, etc.
4. He asked if I knew about deadlocks, and I said yes. He then asked if I knew about the OS ones or DBMS ones, I said that I knew about the OS ones. He asked me to explain deadlocks, ways to deal with them.
5. Differentiate between SQL and NoSQL - I gave a standard answer from the 1st DBMS lecture.
6. Finally, he asked if I had any questions for him.
For others the interviewers grilled candidates a little about stuff they'd put on their resume, too. But for the most part, the interview was governed by words that candidates said while answering another question, i.e. you kind of drive the interview.

After a couple of hours, I was asked to join the Zoom lobby for the HR round.
I was just asked a couple of typical HR questions, but otherwise it was more like a conversation.
1. What are the challenges you faced while working on this project?
2. What is the unique thing that you would bring to the table if you're hired?

The HR round was mostly just about assessing communication skills.
*/