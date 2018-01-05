#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/time.h>

int buffer_size = 65536;
#define SERV_PORT 3000 
int num_thread;
char *sendbuf, *recvbuf;

struct thread_ab
{
	int sock_val;	
	struct sockaddr_in serv_addr;
};

void *udpClient(void *j)
{
	struct thread_ab * ta = (struct thread_abc *)j;
	sendbuf = (char *) malloc(buffer_size);
	recvbuf = (char *) malloc(buffer_size);
	socklen_t addrlen;
	for(int i=0; i<(100/num_thread); i++)
	{
		sendbuf = (char *)malloc(buffer_size);
		memset(sendbuf, 'a', buffer_size);
		sendto(ta->sock_val, sendbuf, buffer_size, 0, (struct sockaddr *)&(ta->serv_addr), addrlen);
		
		//int size = recvfrom(ta->sock_val, recvbuf, buffer_size,0);
		//printf("%s", recvbuf);
		
	}

 	return 0;
}

int main(int argc, char **argv)
{
	printf("Enter the number of threads");
	scanf("%d",&num_thread);
	pthread_t t1[num_thread];
	struct timeval start_t , end_t;
	float rTime , throughput, latency;	
	int sockfd;
 	struct sockaddr_in servaddr;


 	//Socket Creation
 	if ((sockfd = socket (AF_INET, SOCK_DGRAM, 0)) <0) 
	{
	  	perror("Socket creation errors");
	  	exit(2);
 	}

	//Setting the parameters
 	memset(&servaddr, 0, sizeof(servaddr));
 	servaddr.sin_family = AF_INET;
 	servaddr.sin_addr.s_addr= inet_addr(argv[1]);
 	servaddr.sin_port =  htons(SERV_PORT); 

	struct thread_ab * t_info = (struct thread_ab *)malloc(sizeof(struct 		thread_ab));
    	t_info->sock_val = sockfd;
	t_info->serv_addr = servaddr;
	
	gettimeofday(&start_t, NULL);
	for(int j=0; j<num_thread; j++)
	{
		pthread_create(&t1[j],NULL,udpClient,t_info);
		pthread_join(t1[j],NULL);
	} 
	gettimeofday(&end_t, NULL);
	unsigned long long start_usec = (unsigned long long)start_t.tv_sec * 1000000 + start_t.tv_usec; 
	unsigned long long end_usec = (unsigned long long)end_t.tv_sec * 1000000 + end_t.tv_usec;
	//printf("%f", (double)end_t);
	rTime = (double)(end_usec - start_usec)/1000;
	double thr = 100*buffer_size*8/rTime*1000;
	throughput = (double)(thr/(1024*1024));
    	latency = (double)(rTime/100.0);
    	printf("\n\nWith %d threads, the latency is %f ms and the throughput is %f Mb/S\n", num_thread, latency, throughput);
    	printf("\n"); 
	 
}
