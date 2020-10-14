#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

//syscall(SYS_gettid);
typedef struct
{
    int v1;
    int v2;
    int v3;
} laStruct;



laStruct zoneCommune;	// Zone commune

void *fctThread(void *arg)
{
    laStruct *vals;
    vals = (laStruct *)arg;
    printf(" pid : [%d] tid : [%ld] dans le thread \n",getpid(), syscall(SYS_gettid));

    pthread_mutex_lock(&mutexZone);
    zoneCommune.v1=vals->v1;
    sleep(3-vals->v1);
    zoneCommune.v2=vals->v2;

    zoneCommune.v3=vals->v3;
    pthread_mutex_unlock(&mutexZone);

    pthread_exit((void *)vals->v1);
}

int main()
{
    int res;
    pthread_t threadUn;
    pthread_t threadDeux;
    pthread_t threadTrois;
    void *thread_result;

    laStruct t1,t2,t3;
   

    zoneCommune.v1=0;
    zoneCommune.v2=0;
    zoneCommune.v3=0;

    printf("v1=%d v2=%d v3=%d\n ",zoneCommune.v1,zoneCommune.v2,zoneCommune.v3);

    t1.v1=1;
    t1.v2=1;
    t1.v3=1;

    t2.v1=2;
    t2.v2=2;
    t2.v3=2;

    t3.v1=3;
    t3.v2=3;
    t3.v3=3;


    res = pthread_create(&threadUn, NULL, fctThread, (void *)&t1);
    if (res != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&threadDeux, NULL, fctThread, (void *)&t2);
    if (res != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&threadTrois, NULL, fctThread, (void *)&t3);
    if (res != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }


    res = pthread_join(threadUn, &thread_result);
    if (res != 0)
    {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    printf("OK, valeur de retour du Thread join :%d\n", (int )thread_result);
    res = pthread_join(threadDeux, &thread_result);
    if (res != 0)
    {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    printf("OK, valeur de retour du Thread join :%d\n", (int )thread_result);
    res = pthread_join(threadTrois, &thread_result);
    if (res != 0)
    {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    printf("OK, valeur de retour du Thread join :%d\n", (int )thread_result);


    printf("\n apres fin des 3 threads v1=%d v2=%d v3=%d \n",zoneCommune.v1,zoneCommune.v2,zoneCommune.v3);

    exit(EXIT_SUCCESS);
}
