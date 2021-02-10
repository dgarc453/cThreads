
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int SharedVariable = 0;
void *SimpleThread(void *index)
{

    int *threadNum;
    threadNum = index;
    int num, val = 0;
    for (num = 0; num < 20; num++)
    {
        if (random() > RAND_MAX / 2)
            usleep(10);
        val = SharedVariable;
        printf("*** thread %d sees value %d\n", *threadNum, val);
        SharedVariable = val + 1;
    }
    val = SharedVariable;
    printf("Thread %d sees final value %d\n", *threadNum, val);
    return NULL;
}
int main(int argc, char *argv[] ) {

    if (argc != 2)
    {
        printf("You enter incorrect number of arguments, to run this code use the form (./test <integer>)\n");
        exit(0);
    }

    int loops = atoi(argv[1]);
    if  (loops == 0){
        printf("You did not enter an integer value, to run this code use the form (./test <integer>)\n");
        exit(0);
    }else{
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (argv[1][i] < '0' || argv[1][i] > '9')
            {
                printf("You did not enter an integer value, to run this code use the form(./ test<integer>)\n ");
                exit(0);
            }
        }
    }
    pthread_t *myThread;
    myThread = (pthread_t *)malloc(sizeof(pthread_t) * atoi(argv[1]));
    int *j = (int *)malloc(sizeof(int) * loops);
    for (int i = 0; i < loops; i++)
        j[i] = i;

    for (int i = 0; i < loops; i++)
        pthread_create(&myThread[i], NULL, SimpleThread, &j[i]);
        
    
    for (int i = 0; i < loops; i++)
        pthread_join(myThread[i], NULL);

    return 0;
}