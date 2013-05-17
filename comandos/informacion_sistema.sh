#!/bin/bash

function get_hostname {
    echo $(/bin/hostname)
}

function get_version {
    echo $(cat /etc/issue.net)
}

function kernel {
    echo $(uname -r)
}

function memory {
    free=$(free -m | grep Mem | awk '{print $4}')
    used=$(free -m | grep Mem | awk '{print $3}')
    echo "Usada: "$used
    echo "Libre: "$free
}

function vmemory {
    free=$(vmstat -sS m | grep "free swap" | awk '{print $1}')
    used=$(vmstat -sS m | grep "used swap" | awk '{print $1}')
    echo "Usada: "$used
    echo "Libre: "$free
}

function disk_usage {
    free=$(df -h | grep /dev/mapper/ubuntu-root | awk '{print $4}')
    used=$(df -h | grep /dev/mapper/ubuntu-root | awk '{print $3}')
    echo "Usado: "$used
    echo "Libre: "$free
}

echo "hostname: "
get_hostname
echo "version: "
get_version
echo "kernel: "
kernel
echo "Memoria"
memory
echo "Memoria virtual"
vmemory
echo "Disco"
disk_usage
df -H
