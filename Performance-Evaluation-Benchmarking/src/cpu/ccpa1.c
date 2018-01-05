#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <immintrin.h>

const int no_operations = 1000000000;
int no_of_threads;
double instr = 30;					//number of instructions

void *IopsCalc(void *j)
{
	int sum = 0, val = 0;
	int x = 479, y = 784;
	for(int a=0;a<(no_operations/no_of_threads);a++)
	{
		val = x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y;
	}
}

void *FlopsCalc(void *j)
{
	double sum = 0.0, val = 0.0;
	double x = 4.79, y = 7.84;
	for(int a=0;a<(no_operations/no_of_threads);a++)
	{
		val = x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y - x + y;
	}
}

void cpu_usage(int no_thread)
{
	pthread_t thread1[no_thread];
	clock_t start_t, end_t;
	int j;
	double rTime = 0.0, rSpeed = 0.0, iops_val = 0.0, flops_val = 0.0;

	start_t = clock();
	for(j = 0; j < no_thread; j++)
	{
		pthread_create(&thread1[j], NULL, IopsCalc, (void*) j);
		pthread_join(thread1[j],NULL);
	}
	end_t = clock();
	rTime = ((double)(end_t - start_t))/CLOCKS_PER_SEC;
	rSpeed = (double)((instr*no_operations)/(rTime*1000000000.0));
	printf("Number of Giga IOPS for %d threads => %f , Time Taken : %f\n", no_thread, rSpeed , rTime);


	start_t = clock();
	for(j = 0; j < no_thread; j++)
	{
		pthread_create(&thread1[j], NULL, FlopsCalc, (void*) j);
		pthread_join(thread1[j],NULL);
	}
	end_t = clock();
	rTime = ((double)(end_t - start_t))/CLOCKS_PER_SEC;
	rSpeed = (double)((instr*no_operations)/(rTime*1000000000.0));
	printf("Number of Giga FLOPS for %d threads => %f , Time Taken : %f\n", no_thread, rSpeed , rTime);

}


int main()
{
	for(int i=1; i<16; i*=2)
	{
		no_of_threads = i;
		cpu_usage(no_of_threads);
		printf("\n");
	}
	pthread_exit(NULL);
                return 1;

	/*no_of_threads = 1;
	cpu_usage(no_of_threads);

	no_of_threads = 2;
	cpu_usage(no_of_threads);

	no_of_threads = 4;
	cpu_usage(no_of_threads);

	no_of_threads = 8;
	cpu_usage(no_of_threads);
	printf("\n\n \n\n");
	pthread_exit(NULL);
	return 1;*/
}
