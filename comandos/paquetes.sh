#!/bin/bash

case "$1" in
    "paquete")
        PKG=$(dpkg -l | awk '{ print $2 }' | grep ${2})
        if [ -z "$PKG" ];then
            URL=$(apt-cache policy ${2} | tail -n 1 | awk '{ $1=""; print $0 }')
            if [ -n "$URL" ];then
                echo "El repositorio se encuentra en "$URL
            else
                echo "No se puede localizar el paquete"
            fi
        else
            echo "El paquete ya se encuentra instalado."
        fi
        ;;
    "help" | *)
        echo "$ paquetes.sh paquete nombredelpaquete"
        echo "Indicara si el paquete esta o no instalado, en caso de no estar instalado mostrara la ruta del repositorio."
        ;;
    esac
