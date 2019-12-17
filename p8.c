#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t l1;
int b=0;

int main()
{
        pthread_t prod,con;
        void *producer(),*consumer();
        pthread_create(&prod,NULL,producer,NULL);
        pthread_create(&con,NULL,consumer,NULL);
        pthread_join(con,NULL);
}

void add_buf(int i)
{
        b=i;
}
int get_buf()
{
        return b;
}
void *producer()
{
        int i=0;
        printf("\nProducer\n");
        for(i=0;i<10;i++)
        {
                pthread_mutex_lock(&l1);
                add_buf(i);
                printf("%d sent\n",i);
                pthread_mutex_unlock(&l1);
        }
        pthread_exit(NULL);
}

void *consumer()
{
        int i,rc;
        printf("\nConsumer\n");
        for(i=0;i<10;i++)
        {
                pthread_mutex_lock(&l1);
                rc=get_buf();
                printf("%d Received\n",i);
                pthread_mutex_unlock(&l1);
        }
        pthread_exit(NULL);
}