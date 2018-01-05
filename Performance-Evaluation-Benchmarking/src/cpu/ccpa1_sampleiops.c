#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <immintrin.h>
//void *IopsCalc(void *counter);

const int no_operations = 1000000000;
double instr = 30;                                      //number of instructions
double No_op[8] ;
int count=0;

void * IopsCalc(void *j);
void cpu_usage(int no_thread);

void *IopsCalc(void *j) {
    int a= *(int *)j;

    int x=479;
    int y = 784;
    int val = 0;

    while(1)
    {

        val = x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y;

        No_op[a]+=instr;
    }

}



void cpu_usage(int no_thread) {
    pthread_t thread1[no_thread];
    double No_ops = 0;
    clock_t start_t, end_t;
    int timer=0;
    int j=0;
    double rTime;

    start_t = clock();

    for( j = 0; j < no_thread; j++)
    {

        pthread_create(&thread1[j], NULL, IopsCalc, &j);

    }

    do{
        end_t = clock();
        rTime = ((double)(end_t - start_t))/CLOCKS_PER_SEC;

        if (rTime >=1) {
            for (int op = 0; no_thread > op; op++) {
                No_ops = No_ops + No_op[op];
            }
            //No_ops = No_op[0]+No_op[1]+No_op[2]+No_op[3]+No_op[4]+No_op[5]+No_op[6]+No_op[7];

            count++;
            //      printf("\nCount: %d \n",count);
            printf(" \n =>\t %d) \t GIOPS : %f \n", count,No_ops / (double)1000000000);
            No_ops=0;

            for (int op = 0; op < no_thread; op++) {
                No_op[op] = 0;
            }

            timer = timer + 1;
            start_t = clock();
        }
    } while( timer < 600 );
/*
    for( j = 0; j < no_thread; j++)
    {

        pthread_cancel(thread1[j]);

    }
*/

    exit(0);
}


int main() {
    cpu_usage(8);

    printf("END of IOPS calculatiion");
    pthread_exit(NULL);
    return 0;

}
