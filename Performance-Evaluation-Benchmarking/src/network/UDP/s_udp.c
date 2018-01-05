#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int buffer_size = 65536 ;
#define SERV_PORT 3000 
char *recvbuf, *sendbuf;
int num_thread;
int n;
socklen_t addrlen;

struct thread_ab
{
	int sock_accept;
	struct sockaddr_in cli_addr;
	
};


void *UdpServer(void *j)
{
   struct thread_ab * ta = (struct thread_abc *)j;
	
	recvbuf = (char *)malloc(buffer_size);
	sendbuf = (char *)malloc(buffer_size);
	addrlen = sizeof(struct sockaddr);
	for(int i=0; i<(100/num_thread); i++)
	{
		int size = recvfrom(ta->sock_accept, recvbuf, buffer_size,0, (struct sockaddr *)&(ta->cli_addr), &addrlen);
		//printf("%s", recvbuf);
		
		memset(sendbuf, 'a', buffer_size);
		//send(ta->sock_accept, sendbuf, buffer_size, 0);
	}

	

	
 
}


int main (int argc, char **argv)
{
 printf("Enter the number of threads");
 scanf("%d", &num_thread);
 pthread_t t1[num_thread];
 int sock1fd, connfd;
 socklen_t clilen;
 struct sockaddr_in cliaddr, servaddr;

 //creation of the socket
 sock1fd = socket (AF_INET, SOCK_DGRAM, 0);

 //Setting the parameters
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 servaddr.sin_port = htons(SERV_PORT);

 bind (sock1fd, (struct sockaddr *) &servaddr, sizeof(servaddr));

 printf("%s\n","Listening.");

  struct thread_ab * t_info = (struct thread_ab *)malloc(sizeof(struct 	   		thread_ab));
  t_info->sock_accept = sock1fd;
  t_info->cli_addr = cliaddr;

  for(int j=0; j<num_thread; j++)
  {
	pthread_create(&t1[j],NULL,UdpServer,t_info);
	pthread_join(t1[j],NULL);
  }

	//close(connfd);

 
 //close listening socket
 //close (sock1fd);
  
}

