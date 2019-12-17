#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argc,char const *argv[])
{
        FILE *f;
        int cnt=0,tid;
        char sWord[100],filename[10]="words.txt";
        #pragma omp parallel num_threads(2) firstprivate(cnt)
private(f,sWord,tid) shared(filename)
        {
        tid=omp_get_thread_num();

        #pragma omp sections
        {
                #pragma omp section
                {
                        printf("\nHi I am thread %d in section 1\n",tid);
                        f=fopen(filename,"r");

                        if(f)
                        {
                                while(!feof(f))
                                {
                                        fscanf(f,"%s",sWord);
                                        if(feof(f))
                                                break;
                                        if(strcmp(sWord,"Jane")==0)
                                                cnt=cnt+1;
                                        printf("%s\n",sWord);
                                }
                                printf("Hi the word JANE has been repeated %d times\n",cnt);
                                fclose(f);
                        }
                }
                #pragma omp section
                {
                        printf("\nHi I am thread %d in section 2\n",tid);
                        f=fopen(filename,"r");

                        if(f)
                        {
                                while(!feof(f))
                                {
                                        fscanf(f,"%s",sWord);
                                        if(feof(f))
                                                break;
                                        if(strcmp(sWord,"Elizabeth")==0)
                                                cnt=cnt+1;
                                }
                                printf("Hi the word Elizabeth has been repeated %d times\n",cnt);

                                fclose(f);
                        }
                }
        }
        }
}