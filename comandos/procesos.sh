#!/bin/bash

function disk_usage {
    free=$(df -h | grep /dev/mapper/ubuntu-root | awk '{print $4}')
    used=$(df -h | grep /dev/mapper/ubuntu-root | awk '{print $3}')
    echo "Disco usado: "$used
    echo "Disco libre: "$free
}

function memory {
    free=$(free -m | grep Mem | awk '{print $4}')
    used=$(free -m | grep Mem | awk '{print $3}')
    echo "Memoria usada: "$used
    echo "Memoria libre: "$free
}

case "$1" in
    "usuario")
        PROC=$(ps aufx | awk '{print $1}' | grep ${2}) 
        if [ -n "$PROC" ]; then
            ps aufx | head -n 1
            ps aufx | grep ${2}
        fi
        ;;

    "")
        echo "CPU: " + $(mpstat | awk '$12 ~ /[0-9.]+/ { print 100 - $12"%" }')
        echo "------ Procesos ------"
        ps aufx
        ;;

    "total")
        echo "CPU: " + $(mpstat | awk '$12 ~ /[0-9.]+/ { print 100 - $12"%" }')
        disk_usage
        memory
        ;;

    "help")
        echo "$ procesos"
        echo "Muestra el uso total de cpu y el arbol de procesos"
        echo ""
        echo "$ procesos usuario nombredeusuario"
        echo "Muestra los procesos de el usuario mostrado"
        echo ""
        echo "$ procesos total"
        echo "Muestra el consumo total de recursos"
        ;;

    esac
