#!/bin/bash

sudo mdadm --create --verbose --force /dev/md0 --level=0 --name=MY_RAID --raid-devices=1 /dev/nvme0n1

sudo mkfs.ext4 -L MY_RAID /dev/md0

mkdir -p /mnt/raid 

mount LABEL=MY_RAID /mnt/raid

df -h

lsblk

cd /mnt/raid/

