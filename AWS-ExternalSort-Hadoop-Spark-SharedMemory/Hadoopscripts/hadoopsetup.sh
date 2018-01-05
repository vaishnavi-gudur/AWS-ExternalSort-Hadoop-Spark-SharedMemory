#!/bin/bash

sudo apt-get update && sudo apt-get dist-upgrade

Y

wget http://apache.mirrors.tds.net/hadoop/common/hadoop-2.3.0/hadoop-2.3.0.tar.gz

mkdir Downloads

cp hadoop-2.3.0.tar.gz ~/Downloads/

sudo tar zxf ~/Downloads/hadoop-* -C /usr/local

sudo mv /usr/local/hadoop-* /usr/local/Hadoop

readlink -f $(whereis java)

export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export PATH=$PATH:$JAVA_HOME/bin
export HADOOP_HOME=/usr/local/hadoop
export PATH=$PATH:$HADOOP_HOME/bin
export HADOOP_CONF_DIR=/usr/local/hadoop/etc/hadoop







