#/bin/bash

apt-get install ssh

ssh-keygen

cat /root/.ssh/id_rsa.pub >> /root/.ssh/authorized_keys

chmod 0600 authorized_keys

ssh localhost