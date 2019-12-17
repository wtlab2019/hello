#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX 10
int number=0;
pthread_mutex_t mu=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t sc=PTHREAD_COND_INITIALIZER;
pthread_cond_t sp=PTHREAD_COND_INITIALIZER;
void *consumer()
{
        printf("\nHello consumer:");
        while(1)
        {
        pthread_mutex_lock(&mu);
        pthread_cond_signal(&sp);
        pthread_cond_wait(&sc,&mu);
        printf("consumer %d\n",number);
        pthread_mutex_unlock(&mu);
        if(number==MAX)
        {       
                printf("\n consumer done\n");
                break;
        }
        }
}
void *producer()
{
        printf("\nHello producer\n");
        while(1)
        {
        pthread_mutex_lock(&mu);
        number++;
        printf("producer=%d\n",number);
        pthread_cond_signal(&sc);
        if(number!=MAX)
                pthread_cond_wait(&sp,&mu);
        pthread_mutex_unlock(&mu);
        if(number==MAX)
        {
                printf("producer done\n");
                break;
        }
        }
}       
int main()
{
        int i,rc;
        pthread_t t[2];
        if(rc==pthread_create(&t[0],NULL,consumer,NULL))
        printf("error");
        if(rc==pthread_create(&t[1],NULL,producer,NULL))
        printf("error");
        for(i=0;i<2;i++)
        pthread_join(t[i],NULL);
}