#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include <string.h>

// chosen such that each block operation occupies 1GB memory space.
int B_max = 1024 * 1024;
int kB_max = 80000;//
int MB_max = 128; //(1024/8)
int TMB_max = 8; //(1024/80) <= GB/TMB


//varying block sizes (8B, 8KB, 8MB, 80MB)
int B = 8; //8 byte
int kB = 8 * 1024; //8KB
int MB = 8 * 1024 * 1024; //8MB
int TMB = 80 * 1024 * 1024; //80MB

const int mb = 1024 * 1024; //1MB //created for properly randomizing the write operations

int noThread; // to keep track of the threads required for the purpose of strong scaling
const int GB = 1024 * 1024 * 1024; //max size of each buffer: srcBuffer and destBuffer


//Read and Write Byte Block Size
void *seq_read_write_byte() {
    int a;//1 byte
    char *destBuffer = (char *) malloc(GB);//reserving destination buffer space in the memory
    char *srcBuffer = (char *) malloc(GB);//reserving source buffer space in the memory
    for (a = 0; a < B_max / noThread; a++) {//200kB data with 8byte blocks
        // fseek(fptr, a, SEEK_SET);
        memcpy(destBuffer, srcBuffer, B);
        destBuffer += B;
        srcBuffer += B;
    }
//    free(*destBuffer);
//    free(*srcBuffer);
}

//Write Byte Block Size Sequentially
void *seq_write_byte() {
    int a;//1 byte
    char *destBuffer = (char *) malloc(GB);//reserving destination buffer space in the memory
    for (a = 0; a < B_max / noThread; a++) {//200kB data with 8byte blocks
        memset(destBuffer, 'a', B);
        destBuffer += B;
    }

//    free(*destBuffer);
}

//Write Byte Block Size Randomly
void *rand_write_byte() {
    int a;
    int random;
    char *destBuffer = (char *) malloc(GB);//reserving destination buffer space in the memory
    for (a = 0; a < B_max / noThread; a++) {//200kB data randomly with 8byte blocks
        random = rand() % (B_max * B / noThread);
        memset(&destBuffer[random], 'a', B);
    }
//    free(*destBuffer);
}


// Read and Write Kilo Byte Block Size
void *seq_read_write_kbyte() {
//    printf("start of seq_read_write %d \t",noThread);
    int a;
    char *destBuffer = (char *) malloc(GB); //reserving destination buffer space in the memory
    char *srcBuffer = (char *) malloc(GB); //reserving source buffer space in the memory
    for (a = 0; a < kB_max / noThread; a++) { //800kB data with 8kB blocks
        memcpy(destBuffer, srcBuffer, kB);
        destBuffer += kB;
        srcBuffer += kB;
    }
//    printf("\nend of seq_read_write\n");
}

//Write Kilo Byte Block Size Sequentially
void *seq_write_kbyte() {
    //printf("in seq_write");
    int a;
    char *destBuffer = (char *) malloc(GB);//reserving destination buffer space in the memory
//    char *srcBuffer =(char *)malloc(B_max);//reserving source buffer space in the memory
    for (a = 0; a < kB_max / noThread; a++) { //800kB data with 8kb blocks
        memset(destBuffer, 'a', kB);
        destBuffer += kB;
    }

}

//Write Kilo Byte Block Size Randomly
void *rand_write_kbyte() {
    //  printf("in random_write");
    int a;
    char *destBuffer = (char *) malloc(GB);//reserving destination buffer space in the memory
//    char *srcBuffer =(char *)malloc(B_max);//reserving source buffer space in the memory
    int random;
    for (a = 0; a < kB_max / noThread; a++) { //800kB data randomly with 8kb blocks
        random = rand() % (kB_max * kB / noThread);
        memset(&destBuffer[random], 'a', kB);
    }

}


//Read and Write Mega Byte Block Size
void *seq_read_write_mbyte() {
    int a;
    int count = 0;
    char *destBuffer = (char *) malloc(GB);//reserving destination buffer space in the memory
    char *srcBuffer = (char *) malloc(GB);//reserving source buffer space in the memory
    for (a = 0; a < MB_max / noThread; a++) { //160MB data with 8MB blocks
        count++;
        memcpy(destBuffer, srcBuffer, MB);
//        destBuffer+=MB;
//        srcBuffer+=MB;
    }
//    printf("\nthe loop ran for %d times", count);
    //    printf("thread count is : %d\n",noThread);
//    free(destBuffer);
}

//Write Mega Byte Block Size Sequentially
void *seq_write_mbyte() {
    int a;
    char *destBuffer = (char *) malloc(GB);//reserving destination buffer space in the memory
//    char *srcBuffer =(char *)malloc(GB);//reserving source buffer space in the memory
    for (a = 0; a < MB_max / noThread; a++) { //160MB data with 8MB blocks
        memset(&destBuffer[a], 'a', MB);
//        destBuffer+=MB;
    }
//    free(destBuffer);
}

//Write Mega Byte Block Size Randomly
void *rand_write_mbyte() {
    int a;
    char *destBuffer = (char *) malloc(GB);//reserving destination buffer space in the memory
//    char *srcBuffer =(char *)malloc(GB);//reserving source buffer space in the memory
    int random;
    for (a = 0; a < MB_max / noThread; a++) { //160MB data randomly with 8MB blocks
        random = rand() % (MB_max * MB / noThread);
        memset(&destBuffer[random], 'a', MB);
    }
//    free(destBuffer);
}


//Read and Write Ten Mega Byte Block Size
void *seq_read_write_tmbyte() {
    int a;
    char *destBuffer = (char *) malloc(GB);//reserving destination buffer space in the memory
    char *srcBuffer = (char *) malloc(GB);//reserving source buffer space in the memory
    for (a = 0; a < TMB_max / noThread; a++) { //400MB data with 80MB blocks
        memcpy(&destBuffer[a], &srcBuffer[a], TMB);
        destBuffer += TMB;
        srcBuffer += TMB;
    }
//    free(destBuffer);
}

//Write Ten Mega Byte Block Size Sequentially
void *seq_write_tmbyte() {
    int a;
    char *destBuffer = (char *) malloc(GB);//reserving destination buffer space in the memory
//    char *srcBuffer =(char *)malloc(GB);//reserving source buffer space in the memory
    for (a = 0; a < TMB_max / noThread; a++) { //400MB data with 80MB blocks
        memset(&destBuffer[a], 'a', TMB);
        destBuffer += TMB;
    }
//    free(destBuffer);
}

//Write Ten Mega Byte Block Size Randomly
void *rand_write_tmbyte() {
    int a;
    int random;
    char *destBuffer = (char *) malloc(GB);//reserving destination buffer space in the memory
//    char *srcBuffer =(char *)malloc(GB);//reserving source buffer space in the memory
    for (a = 0; a < TMB_max / noThread; a++) { //400MB data randomly with 80MB blocks
        random = rand() % (TMB_max * TMB);
        memset(&destBuffer[random], 'a', TMB);
    }
//    free(destBuffer);
}

void ByteBlock() {

    int i;
    clock_t start_t, end_t;
    long double run_time;
    long double l, l1, throughput;
    long double data_mb;
    pthread_t thread[8];

    printf("\t Byte sized block");
    printf("\n\nEnter the number of threads(1/2/4/8) :\n");
    scanf("%d", &noThread);
    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&thread[i], NULL, seq_read_write_byte, NULL);//creates threads
        pthread_join(thread[i], NULL);// joins threads
    }
    end_t = clock();
    run_time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating time taken
    data_mb = (B * B_max) / mb;
    throughput = data_mb / run_time;// Calculating the throughput in MBps
    printf("\n\nREAD + WRITE");
    printf("\nThroughtput:%0.9Lf MB/s", throughput);
    l = (run_time * 1000000) / data_mb;// Calculating latency
    printf("\nLatency : %0.9Lf us", l);

    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&thread[i], NULL, seq_write_byte, NULL);//creates threads
        pthread_join(thread[i], NULL);// joins threads
    }
    end_t = clock();
    run_time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating time taken
    data_mb = (B * B_max) / mb;
    throughput = data_mb / run_time;//  Calculating the throughput in MBps
   // printf("\n\nSEQUENTIAL WRITE”);
    printf("Sequential write\nThroughtput:%0.9Lf MB/s", throughput);
    l1 = (run_time * 1000000) / data_mb;// Calculating latency
    printf("\nLatency : %0.9Lf us", l1);

    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&thread[i], NULL, rand_write_byte, NULL);//creates threads
        pthread_join(thread[i], NULL);// joins threads
    }
    end_t = clock();
    run_time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating time taken
    data_mb = (B * B_max) / mb;
    throughput = data_mb / run_time;// Calculating the throughput in MBps
    printf("\n\nRANDOM WRITE");
    printf("\nThroughtput:%0.9Lf MB/s", throughput);
    l1 = (run_time) / 1000000 / data_mb;// Calculating latency
    printf("\nLatency : %0.9Lf us", l1);

    exit(0);

}

void KiloByteBlock() {

    int i;
    clock_t start_t, end_t;
    long double run_time;
    long double l, l1, throughput;
    long double data_mb;

    printf("\tKILO Byte sized block");

    printf("\n\nEnter the number of threads(1/2/4/8) :\n");
    scanf("%d", &noThread);
    pthread_t thread[noThread];
    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&thread[i], NULL, seq_read_write_kbyte, NULL);//creates threads
        pthread_join(thread[i], NULL);// joins threads
    }
    end_t = clock();
    run_time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating time taken

    data_mb = (kB_max * kB) / mb;
    l = (run_time * 1000000) / data_mb;// Calculating latency in us
    printf("\n\n In KB: READ + WRITE");
    throughput = data_mb / run_time;// Calculating the throughput in MBps
    printf("\nThroughtput:%0.11Lf MB/s", throughput);
    printf("\nLatency : %0.11Lf us", l);

    //  printf("done with thread...proceeding to seq_write");

    start_t = clock();
    for (i = 0; i < noThread; i++) {
//        printf("start of seq_write_thread");
        pthread_create(&thread[i], NULL, seq_write_kbyte, NULL);//creates threads
        pthread_join(thread[i], NULL);// joins threads
    }
    end_t = clock();
    run_time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating run_time taken
    data_mb = (kB_max * kB) / mb;
    throughput = data_mb / run_time;// Calculating the throughput in MBps
    printf("\n\nSEQUENTIAL WRITE");
    printf("\nThroughtput:%0.11Lf MB/s", throughput);
    l1 = (run_time * 1000000) / data_mb;// Calculating latency in us
    printf("\nLatency : %0.11Lf us", l1);

    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&thread[i], NULL, rand_write_kbyte, NULL);//creates threads
        pthread_join(thread[i], NULL);// joins threads
    }
    end_t = clock();
    data_mb = (kB_max * kB) / mb;
    run_time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating run_time taken
    l1 = (run_time * 1000000) / data_mb;// Calculating latency in us
    printf("\n\nRANDOM WRITE");
    throughput = data_mb / run_time;//Calculating the throughput in MBps
    printf("\nThroughtput:%0.11Lf MB/s", throughput);
    printf("\nLatency : %0.11Lf us", l1);
    exit(0);

}

void MegaByteBlock() {

    int i;
    clock_t start_t, end_t;
    long double run_time;
    long double l, l1, throughput;
    long double data_mb;

    printf("\tMEGA Byte sized block");
    printf("\n\nEnter the number of threads(1/2/4/8) :\n");
    scanf("%d", &noThread);
    pthread_t thread[noThread];
    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&thread[i], NULL, seq_read_write_mbyte, NULL);//creates threads
        pthread_join(thread[i], NULL);
    }
    end_t = clock();
    data_mb = (MB_max * MB) / mb;
    run_time = (double) (end_t - start_t) / CLOCKS_PER_SEC;// calculating run_time taken
    l = (run_time * 1000000) / data_mb;// Calculating latency in us
    printf("\n\nREAD + WRITE");

    throughput = data_mb / run_time;// Calculating the throughput in MBps
    printf("\nThroughtput:%0.9Lf MB/s", throughput);
    printf("\nLatency : %0.9Lf us", l);

    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&thread[i], NULL, seq_write_mbyte, NULL);//creates threads
        pthread_join(thread[i], NULL);
    }
    end_t = clock();
    data_mb = (MB * MB_max) / mb;
    run_time = (double) (end_t - start_t) / CLOCKS_PER_SEC;// calculating run_time taken
    l1 = (run_time * 1000000) / data_mb;// Calculating latency in us
    printf("\n\nSEQUENTIAL WRITE");
    throughput = data_mb / run_time;// Calculating the throughput in MBps
    printf("\nThroughtput:%0.9Lf MB/s", throughput);
    printf("\nLatency : %0.9Lf us", l1);

    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&thread[i], NULL, rand_write_mbyte, NULL);//creates threads
        pthread_join(thread[i], NULL);
    }
    end_t = clock();
    data_mb = (MB * MB_max) / mb;
    run_time = (double) (end_t - start_t) / CLOCKS_PER_SEC;// calculating run_time taken
    l = (run_time * 1000000) / data_mb;// Calculating latency in us
    printf("\n\nRANDOM WRITE");
    throughput = data_mb / run_time;//Calculating the throughput in MBps
    printf("\nThroughtput:%0.9Lf MB/s", throughput);
    printf("\nLatency : %0.9Lf us", l);

    exit(3);

}

void TMegaByteBlock() {

    int i;
    clock_t start_t, end_t;
    long double run_time;
    long double l, l1, throughput;
    long double data_mb;


    printf("\t10MEGA Byte sized block");
    printf("\n\nEnter the number of threads(1/2/4/8) :\n");
    scanf("%d", &noThread);
    pthread_t thread[noThread];
    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&thread[i], NULL, seq_read_write_tmbyte, NULL);//creates threads
        pthread_join(thread[i], NULL);
    }
    end_t = clock();
    data_mb = (TMB * TMB_max) / mb;
    run_time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating run_time taken
    l = (run_time * 1000000) / data_mb;// Calculating latency in us
    printf("\n\nREAD + WRITE ");

    throughput = data_mb / run_time;//  Calculating the throughput in MBps
    printf("\nThroughtput:%0.9Lf MB/s", throughput);
    printf("\nLatency : %0.9Lf us", l);
    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&thread[i], NULL, seq_write_tmbyte, NULL);//creates threads
        pthread_join(thread[i], NULL);
    }
    end_t = clock();
    data_mb = (TMB * TMB_max) / mb;
    run_time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating run_time taken
    l1 = (run_time * 1000000) / data_mb;// Calculating latency in us
    printf("\n\nSEQUENTIAL WRITE");
    throughput = data_mb / run_time;// Calculating the throughput in MBps
    printf("\nThroughtput:%0.9Lf MB/s", throughput);
    printf("\nLatency : %0.9Lf us", l1);

    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&thread[i], NULL, rand_write_tmbyte, NULL);//creates threads
        pthread_join(thread[i], NULL);
    }
    end_t = clock();
    data_mb = (TMB * TMB_max) / mb;
    run_time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating run_time taken
    l = (run_time * 1000000) / data_mb;// Calculating latency in us
    printf("\n\nRANDOM WRITE");
    throughput = data_mb / run_time;// Calculating the throughput in MBps
    printf("\nThroughtput:%0.9Lf MB/s", throughput);
    printf("\nLatency : %0.9Lf us", l);

    exit(3);

}


int main() {


    int i;
    //Input for selecting the block size
    printf("Start of Memory Benchmarking\n");
    printf("Select a Block Size:\n");
    printf("1.8 Bytes\n2.8 Kilo Bytes\n3.8 Mega Bytes\n4.80 Mega Bytes\n5.EXIT\n");
    printf("\nEnter your choice :");
    scanf("%d", &i);

    if (i == 1) {
        ByteBlock();
    }

    if (i == 2) {
        KiloByteBlock();
    }

    if (i == 3) {
        MegaByteBlock();
    }

    if (i == 4) {
        TMegaByteBlock();
    }

    if (i == 5) {
        printf("Terminated by the User");
        exit(1);
    }
    return 0;
}

