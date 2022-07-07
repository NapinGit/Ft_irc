#!/bin/bash
sudo /etc/init.d/screen-cleanup start
i=1
while [ $i -le 100 ]
do 
    rand=$( cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -c 8 )
    screen -A -m -d irssi -c 127.0.0.1 -p 5000 -w yolo -n $rand
    i=$(( $i + 1 ))
    sleep 0.01
done
screen -ls | grep Detached | cut -d. -f1 | awk '{print $1}' | sudo xargs kill