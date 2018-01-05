
CS553 :  Cloud Computing
Programming Assignment 1 : Performance Benchmarking

Author : Vaishnavi  Gudur

This project aims to benchmark performance of different parts of a commputer system from CPU,memory,disk and network.
For CPU, processor speed is measured in terms of floating point operations per second and integer operations per second.
Processor speed is measured at varying levels of concurrency (1,2,4,8 threads). Efficiency is also calculated. As a separate experiment,
Benchmark on double precision floating point and integer instructions and 8 threads for	a 10-minute period for	each one are run, and 
samples every second are taken on how many instructions per second were achieved.Linpack benchmark is run and best performance achieved is reported.

For memory, speed is measured by performing read+write operations, sequential read access, random read access varying block sizes (1B,1KB,1MB,10MB) 
and  varying the concurrency(1,2,4,8 threads).Metrics measured are throughput(Megabytes per second,MB/sec) and latency (milliseconds,	ms).

For Disk, speed is measured by performing read+write operations, sequential read access, random read access varying block sizes (1B,1KB,1MB,10MB) 
and  varying the concurrency(1,2,4,8 threads).Metrics measured are throughput(Megabytes per second,MB/sec) and latency (milliseconds,	ms).	
Optimal	number	of concurrency	to get the best performance is then identified.

For network, network speed over the loopback interface card (1 node, between 2 processes on the same node), and	then network speed between two	nodes
is measured. Parameters include TCP protocol stack, UDP,fixed packet/buffer size (64KB),and varying the	concurrency (1	thread, 2 threads, 4 threads, 8	threads)
The metrics measured are throughput(Megabits	per	second,	Mb/sec)	and latency(ms).

The repository contains following documents and folders:
1. src folder
- This folder contains furthermore folders which contain executables and source files to run the benchmarking code.
  -> cpu folder
  -> memory
  -> disk
  -> network
2. Performance_report.pdf
3. readme.txt

*******************************************************************************************************************************************
					BENCHMARKING
*******************************************************************************************************************************************

There are four sections to the assignment:
1) CPU
2) MEMORY
3) DISK
4) NETWORK
**************************************************

*****************************************************************************************
					To compile all the codes run:  make 
					
To clear all the output files: make clean


*******************************************************************************************************************************************
					   CPU
*******************************************************************************************************************************************

There are 3 codes to be run in this section:
1. ccpa1.c
2. ccpa1_sampleiops.c
3. ccpa1_sampleflops.c

To run the main code(ccpa1.c)
-> compile 
	$ gcc -std=c99 -pthread -o ccpa1 ccpa1.c
-> run
	$ ./ccpa1

For 600 samples code, there are 2 codes written separately for FLOPS and IOPS.
To run IOPS code (ccpa1_sampleiops.c)
-> compile 
	$ gcc -std=c99 -pthread -o ccpa1_iops ccpa1_sampleiops.c
-> run
	$ ./ccpa1_iops
-> To generate the samples in a separate text file
	$ ./ccpa1_iops > ccpa1_iops.txt

To run FLOPS code (ccpa1_sampleflops.c)
-> compile 
	$ gcc -std=c99 -pthread -o ccpa1_flops ccpa1_sampleflops.c
-> run
	$ ./ccpa1_flops
-> to generate the samples in a separate text file
	$ ./ccpa1_flops > ccpa1_flops.txt

*******************************************************************************************************************************************
					MEMORY
*******************************************************************************************************************************************

There is 1 code to be run in this experiment:
1. memory.c

-> The throughput and latency values can be obtained across varying block sizes 
   (8 B, 8 KB, 8 MB, 80 MB) and across varying levels of concurrency (1,2,4,8 threads).
-> compile 
	$ gcc -std=c99 -pthread -o mem memory.c
-> run
	$ ./mem
	Enter block size
	Enter number of threads

*******************************************************************************************************************************************
					DISK
*******************************************************************************************************************************************

There is 1 code to be run in this experiment:
1. disk.c

-> The throughput and latency values can be obtained across varying block sizes 
   (8 B, 8 KB, 8 MB, 80 MB) and across varying levels of concurrency (1,2,4,8 threads).
-> compile 
	$ gcc -std=c99 -pthread -o disk disk.c
-> run
	$ ./disk
(NOTE: Wait for the 10GB file to be created)
	Enter block size
	Enter number of threads



*******************************************************************************************************************************************
				      NETWORK
*******************************************************************************************************************************************
There are 4 codes to be run in this section:
1. c_tcp.c
2. s_tcp.c
3. c_udp.c
4. s_ucp.c

There are 2 methods of data transfer implemented in this section: TCP/UDP
For implementing TCP on 1 node, on two separate terminals of the same instance,
compile c_tcp.c on one terminal and s_tcp.c on another terminal.

TCP :

-> compile
	gcc -std=c99 -pthread -o s_tcp s_tcp.c (terminal 1)
	gcc -std=c99 -pthread -o c_tcp c_tcp.c (terminal 2)
-> run 
	./s_tcp
	Enter the number of threads	(terminal 1)
	./c_tcp ipaddress
	Enter the number of threads 	(terminal 2)
Note that number of threads on client and server should be the same.
-> Example
	./s_tcp 
	  2
	./c_tcp 127.0.0.1
	  2

UDP :

-> compile
	gcc -std=c99 -pthread -o s_udp s_udp.c (terminal 1)
	gcc -std=c99 -pthread -o c_udp c_udp.c (terminal 2)
-> run 
	./s_udp
	Enter the number of threads	(terminal 1)
	./c_udp ipaddress
	Enter the number of threads 	(terminal 2)
Note that number of threads on client and server should be the same.
-> Example
	./s_udp 
	  2
	./c_udp 127.0.0.1
	  2


**********************************************************************************************************************************************
					END
**********************************************************************************************************************************************


	