#!/bin/bash

#downloading the gensort file.
sudo wget http://www.ordinal.com/try.cgi/gensort-linux-1.5.tar.gz ~/mnt/raid

tar -xvzf gensort-linux-1.5.tar.gz

cd 64
#128 GB
./gensort -a 1374388831 inoutfile.txt
#1 TB 
./gensort -a 1099511627776 inOutFile.txt

