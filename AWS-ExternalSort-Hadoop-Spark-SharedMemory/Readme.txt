CS553 : CLOUD COMPUTING 

PROGRAMMING ASSIGNMENT 2 - Terasort on Shared memory/Hadoop/Spark

Authors :
1. Vaishnavi Gudur(A20384900)
2. Satya Suveen Reddy Mekala(A20379568)

The Assignment Directory contains following documents and folders:

1. Source Code of the program for Terasort: (Source folders of Shared memory, Hadoop, and Spark)
2. Performance Evaluation Report - prog2_report.pdf
3. Output Files

1. Source Code folder
-This folder contains all the automation scripts and source files to run the Shared Memory , Hadoop and Spark Programs to do Terasort.
- The file listing is as follows,
  - * Scripts : Scripts need to be set up for 1 node and 8 nodes.
  - Code - Code for the sorting process.

******Steps to run the Shared Memory*********

- Create an amazon instance with java runtime environment by following the steps mentioned in performance report.

- Add the Jar files present in JARS_AND_JAVA folder for all threads using ssh the instance DNS.

- Generate input file using gensort following the steps in the report

- Run the below command to execute the JAR files

java - jar FILENAME INPUT_FILE_PATH OUTPUT_FILE_NAME

- Evaluate the output file using Valsort.

********************************************


******Steps to run the Hadoop Terasort*********

- Create a virtual hadoop cluster following the steps mentioned in performance report.

- Copy the configuration files from the report to /hadoop/etc/bin folder

- Authorize the Keys (.pem file)

- Start the Hadoop Cluster (make sure that the data node and name nodes are running by using jps)

- Copy the Map_Reduce_Terasort Jar file at the home directory of our instance. This is include

- Once the cluster is started ,run the hadoop tera sort using the command below,

Creating Input and Output Directory.
Go to /mnt/raid/64/

hadoop fs -mkdir /input

Gensort to create input file

 ./gensort -a 1000 inputfile

Valsort to evaluate the output

********************************************

******Steps to run the Spark Terasort*********

- Launch the Spark virtual cluster following the steps mentioned in Programming report.

- Copy the bash script getTimeOfSparkRun.sh to the spark/bin directory

- Evaluate the output file using Valsort.

********************************************

2. Performance_Evaluation_Report
- This file prog2_report.pdf contains all the steps to set up virtual clusters, terasort results and data charts to analyze the results.
