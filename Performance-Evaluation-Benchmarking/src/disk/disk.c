#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include <math.h>


int B_max = 200*1024; //200KB
int kB_max = 800 * 1024; //800KB
double MB_max = 160 * 1024 * 1024; //160MB
double TMB_max = 400 * 1024 * 1024; //400MB


//varying block sizes (8B, 8KB, 8MB, 80MB)
int B = 8; //8 byte
int kB = 8*1024; //8KB
double MB = 8*1024 * 1024; //8MB
double TMB = 80 * 1024 * 1024; //80MB

double mb = 1024*1024; //1MB

int noThread;

char *Buffer;


//Read and Write Byte Block Size
void *seq_read_write_byte() {
    int a;//1 byte
    FILE *fptr;
    fptr = fopen("Testing.txt", "r+");
    for (a = 0; a < B_max/noThread; a++) {//200kB data with 8byte blocks
        // fseek(fptr, a, SEEK_SET);
        fread(Buffer, 1, B, fptr);
    }
    for (a = 0; a < B_max/noThread; a++) {//200kB data with 8byte blocks
        //fseek(fptr, a , SEEK_SET);
        fwrite(Buffer, 1, B, fptr);
    }
    fclose(fptr);
}

//Read Byte Block Size Sequentially
void *seq_read_byte() {
    int a;//1 byte
    FILE *fptr;
    fptr = fopen("Testing.txt", "r");
    for (a = 0; a < B_max/noThread; a++) {//200kB data with 8byte blocks
        // fseek(fptr, a, SEEK_SET);
        fread(Buffer, 1, B, fptr);
    }
    fclose(fptr);
}

//Read Byte Block Size Randomly
void *rand_read_byte() {
    int a;
    FILE *fptr;
    fptr = fopen("Testing.txt", "r");
    for (a = 0; a < B_max/noThread; a++) {//200kB data randomly with 8byte blocks
        int random;
        random = rand() % 1024;
        fseek(fptr, random, SEEK_SET);
        fread(Buffer, 1, B, fptr);
    }
    fclose(fptr);

}


// Read and Write Kilo Byte Block Size
void *seq_read_write_kbyte() {
    int a;
    FILE *fptr;
    fptr = fopen("Testing.txt", "r+");
    for (a = 0; a < 800/noThread; a++) { //800kB data with 8kB blocks
//        fseek(fptr, kB, SEEK_SET);
        fwrite(Buffer, 1, kB, fptr);
    }
    for (a = 0; a <800/noThread; a++) { //800kB data with 8kB blocks
//        fseek(fptr, kB, SEEK_SET);
        fwrite(Buffer, 1, kB, fptr);
    }
    fclose(fptr);
}

//Read Kilo Byte Block Size Sequentially
void *seq_read_kbyte() {
    int a;
    FILE *fptr;
    fptr = fopen("Testing.txt", "r");
    for (a = 0; a < 800/noThread; a++) { //800kB data with 8kb blocks
//        fseek(fptr, 1024, SEEK_SET);
        fread(Buffer, 1, kB, fptr);
    }
    fclose(fptr);
}

//Read Kilo Byte Block Size Randomly
void *rand_read_kbyte() {
    int a;
    FILE *fptr;
    fptr = fopen("Testing.txt", "r");
    for (a = 0; a < 800; a++) { //800kB data randomly with 8kb blocks
        int random = rand() % 5;
        fseek(fptr, random, SEEK_SET);
        fread(Buffer, 1, kB, fptr);
    }
    fclose(fptr);
}


//Read and Write Mega Byte Block Size
void *seq_read_write_mbyte() {
    int a;
    FILE *fptr;
    fptr = fopen("Testing.txt", "r+");
    for (a = 0; a < 160/noThread; a++) { //160MB data with 8MB blocks
        fseek(fptr,  MB, SEEK_SET);
        fread(Buffer, 1, MB, fptr);
    }
    for (a = 0; a < 160/noThread; a++) { //160MB data with 8MB blocks
        fseek(fptr, MB, SEEK_SET);
        fwrite(Buffer, 1, MB, fptr);
    }
    fclose(fptr);
//    printf("thread count is : %d\n",noThread);
}

//Read Mega Byte Block Size Sequentially
void *seq_read_mbyte() {
    int a;
    FILE *fptr;
    fptr = fopen("Testing.txt", "r");
    for (a = 0; a < 160/noThread; a++) { //160MB data with 8MB blocks
        fseek(fptr, a * MB, SEEK_SET);
        fread(Buffer, 1, MB, fptr);
    }
    fclose(fptr);
}

//Read Mega Byte Block Size Randomly
void *rand_read_mbyte() {
    int a;
    FILE *fptr;
    fptr = fopen("Testing.txt", "r");
    for (a = 0; a < 160/noThread; a++) { //160MB data randomly with 8MB blocks
        int random = rand() % 10;
        fseek(fptr, random * a , SEEK_SET);
        fread(Buffer, 1, MB, fptr);
    }
    fclose(fptr);
}


//Read and Write Ten Mega Byte Block Size
void *seq_read_write_tmbyte() {
    int a;
    FILE *fptr;
    fptr = fopen("Testing.txt", "r+");
    for (a = 0; a < 400/noThread; a++) { //400MB data with 80MB blocks
        fseek(fptr, TMB, SEEK_SET);
        fread(Buffer, 1, TMB, fptr);
    }
    for (a = 0; a < 2; a++) { //20MB data with 10MB blocks
        fseek(fptr, TMB, SEEK_SET);
        fwrite(Buffer, 1, TMB, fptr);
    }
    fclose(fptr);
}

//Read Ten Mega Byte Block Size Sequentially
void *seq_read_tmbyte() {
    int a;
    FILE *fptr;
    fptr = fopen("Testing.txt", "r");
    for (a = 0; a < 400/noThread; a++) { //400MB data with 80MB blocks
        fseek(fptr, TMB, SEEK_SET);
        fread(Buffer, 1, TMB, fptr);
    }
    fclose(fptr);
}

//Read Ten Mega Byte Block Size Randomly
void *rand_read_tmbyte() {
    int a;
    FILE *fptr;
    fptr = fopen("Testing.txt", "r");
    for (a = 0; a < 400/noThread; a++) { //400MB data randomly with 80MB blocks
        int random = rand() % 2;
        fseek(fptr, random, SEEK_SET);
        fread(Buffer, 1, TMB, fptr);
    }
    fclose(fptr);
}

void CreateFile(){
    int a;
    int k;
    Buffer = (char *) malloc(TMB_max);
    FILE *fptr;
    for (k = 0; k < (TMB_max ); k++)// Buffer data
    {
        Buffer[k] = 'a';
    }
    fptr = fopen("Testing.txt", "w");
    for (a = 0; a < (TMB_max ); a++) {
        fseek(fptr, a , SEEK_SET);
        fwrite(Buffer, 1, 1, fptr);
    }
    fclose(fptr);

}

void ByteBlock() {

    int i, k;
    clock_t start_t, end_t;
    double time;
    double l, l1, throughput;
    double total_mb;
    pthread_t th[8];

    printf("\t 8Byte sized block");
    printf("\n\nEnter the number of threads(1/2/4/8) :\n");
    scanf("%d", &noThread);
    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&th[i], NULL, seq_read_write_byte, NULL);//creates threads
        pthread_join(th[i], NULL);// joins threads
    }
    end_t = clock();
    time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating time taken
    total_mb = (noThread * B_max) / mb;
    throughput = total_mb / time;// Calculating the throughput in MBps
    printf("\n\nREAD + WRITE");
    printf("\nThroughtput:%f MB/s", throughput);
    l = (time / 1000) / total_mb;// Calculating latency
    printf("\nLatency : %f ms", l);

    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&th[i], NULL, seq_read_byte, NULL);//creates threads
        pthread_join(th[i], NULL);// joins threads
    }
    end_t = clock();
    time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating time taken
    total_mb = (B_max) / mb;
    throughput = total_mb / time;//  Calculating the throughput in MBps
    printf("\n\nSEQUENTIAL READ");
    printf("\nThroughtput:%f MB/s", throughput);
    l1 = (time / 1000) / total_mb;// Calculating latency
    printf("\nLatency : %f ms", l1);

    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&th[i], NULL, rand_read_byte, NULL);//creates threads
        pthread_join(th[i], NULL);// joins threads
    }
    end_t = clock();
    time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating time taken
    total_mb = (B_max) / mb;
    throughput = total_mb / time;// Calculating the throughput in MBps
    printf("\n\nRANDOM READ");
    printf("\nThroughtput:%f MB/s", throughput);
    l1 = (time / 1000) / total_mb;// Calculating latency
    printf("\nLatency : %f ms", l1);

    exit(0);

}

void KiloByteBlock() {

    int i;
    clock_t start_t, end_t;
    double time;
    long double l, l1, throughput;
    long double total_mb;

    pthread_t th[8];
    printf("\t8KILO Byte sized block");

    printf("\n\nEnter the number of threads(1/2/4/8) :\n");
    scanf("%d", &noThread);
    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&th[i], NULL, seq_read_write_kbyte, NULL);//creates threads
        pthread_join(th[i], NULL);// joins threads
    }
    end_t = clock();
    time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating time taken

    total_mb = ( kB_max) / mb;
    throughput = total_mb / time;// Calculating the throughput in MBps
    printf("\n\n READ + WRITE");
    printf("\nThroughtput:%0.9Lf MB/s", fabsl(throughput));
    l = (time / 1000) / total_mb;// Calculating latency in ms
    printf("\nLatency : %0.9Lf ms", l);

    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&th[i], NULL, seq_read_kbyte, NULL);//creates threads
        pthread_join(th[i], NULL);// joins threads
    }
    end_t = clock();
    time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating time taken
    total_mb = (kB_max) / mb;
    throughput = total_mb / time;// Calculating the throughput in MBps
    printf("\n\nSEQUENTIAL READ");
    printf("\nThroughtput:%0.9Lf MB/s",fabsl( throughput));
    l1 = (time / 1000) / total_mb;// Calculating latency in ms
    printf("\nLatency : %0.9Lf ms", l1);

    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&th[i], NULL, rand_read_kbyte, NULL);//creates threads
        pthread_join(th[i], NULL);// joins threads
    }
    end_t = clock();
    total_mb = (kB_max) / mb;
    time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating time taken
    l1 = (time / 1000) / total_mb;// Calculating latency in ms
    printf("\n\nRANDOM READ");
    throughput = total_mb / time;//Calculating the throughput in MBps
    printf("\nThroughtput:%0.9Lf MB/s", fabsl(throughput));
    printf("\nLatency : %0.9Lf ms", l1);
    exit(0);

}

void MegaByteBlock() {

    int i;
    clock_t start_t, end_t;
    long double time;
    long double l, l1, throughput;
    long double total_mb;
    pthread_t th[8];

    printf("\t8MEGA Byte sized block");
    printf("\n\nEnter the number of threads(1/2/4/8) :\n");
    scanf("%d", &noThread);
    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&th[i], NULL, seq_read_write_mbyte, NULL);//creates threads
        pthread_join(th[i], NULL);
    }
    end_t = clock();
    total_mb = (MB_max) / mb;
    time = (long double) (end_t - start_t) / CLOCKS_PER_SEC;// calculating time taken
    l = (time / 1000) / total_mb;// Calculating latency in ms
    printf("\n\nREAD + WRITE");

    throughput = total_mb / time;// Calculating the throughput in MBps
    printf("\nThroughtput:%0.9Lf MB/s", throughput);
    printf("\nLatency : %0.9Lf ms", l);

    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&th[i], NULL, seq_read_mbyte, NULL);//creates threads
        pthread_join(th[i], NULL);
    }
    end_t = clock();
    total_mb = (MB_max) / mb;
    time = (long double) (end_t - start_t) / CLOCKS_PER_SEC;// calculating time taken
    l1 = (time / 1000) / total_mb;// Calculating latency in ms
    printf("\n\nSEQUENTIAL READ");
    throughput = total_mb / time;// Calculating the throughput in MBps
    printf("\nThroughtput:%0.9Lf MB/s", throughput);
    printf("\nLatency : %0.9Lf ms", l1);

    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&th[i], NULL, rand_read_mbyte, NULL);//creates threads
        pthread_join(th[i], NULL);
    }
    end_t = clock();
    total_mb = (MB_max) / mb;
    time = (long double) (end_t - start_t) / CLOCKS_PER_SEC;// calculating time taken
    l = (time) / 1000 / total_mb;// Calculating latency in ms
    printf("\n\nRANDOM READ ");
    throughput = total_mb / time;//Calculating the throughput in MBps
    printf("\nThroughtput:%0.9Lf MB/s", throughput);
    printf("\nLatency : %0.9Lf ms", l);

    exit(3);

}

void TMegaByteBlock() {

    int i;
    clock_t start_t, end_t;
    double time;
    long double l, l1, throughput;
    long double total_mb;
    pthread_t th[8];

    printf("\t80MEGA Byte sized block");
    printf("\n\nEnter the number of threads(1/2/4/8) :\n");
    scanf("%d", &noThread);
    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&th[i], NULL, seq_read_write_tmbyte, NULL);//creates threads
        pthread_join(th[i], NULL);
    }
    end_t = clock();
    total_mb = (TMB_max) / mb;
    time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating time taken
    l = (time / 1000) / total_mb;// Calculating latency in ms
    printf("\n\nREAD + WRITE");

    throughput = total_mb / time;//  Calculating the throughput in MBps
    printf("\nThroughtput:%0.9Lf MB/s", throughput);
    printf("\nLatency : %0.9Lf ms", l);
    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&th[i], NULL, seq_read_tmbyte, NULL);//creates threads
        pthread_join(th[i], NULL);
    }
    end_t = clock();
    total_mb = (TMB_max) / mb;
    time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating time taken
    l1 = (time / 1000) / total_mb;// Calculating latency in ms
    printf("\n\nSEQUENTIAL READ");
    throughput = total_mb / time;// Calculating the throughput in MBps
    printf("\nThroughtput:%0.9Lf MB/s", throughput);
    printf("\nLatency : %0.9Lf ms", l1);

    start_t = clock();
    for (i = 0; i < noThread; i++) {
        pthread_create(&th[i], NULL, rand_read_tmbyte, NULL);//creates threads
        pthread_join(th[i], NULL);
    }
    end_t = clock();
    total_mb = (TMB_max) / mb;
    time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;// calculating time taken
    l = (time / 1000) / total_mb;// Calculating latency in ms
    printf("\n\nRANDOM READ");
    throughput = total_mb / time;// Calculating the throughput in MBps
    printf("\nThroughtput:%0.9Lf MB/s", throughput);
    printf("\nLatency : %0.9Lf ms", l);

    exit(3);

}


int main() {
    //menu driven program
    int i;
    CreateFile();
    //Select the Block Size to carry out
    printf("start of Disk Benchmarking\n");
    printf("Select a Block Size:\n");
    printf("1.8Byte\n2.8Kilo Byte\n3.8Mega Byte\n4.80 Mega Bytes\n5.EXIT\n");
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
        printf("user terminated");
        exit(1);
    }
    printf("\n");
}



