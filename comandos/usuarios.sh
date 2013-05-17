#!/bin/bash

function user_names {
    cat "/etc/passwd" | sed s/:/\ /g | awk '{ if ( $3 >= 1000 ) print $1,"\t",$4,"\t",$6,"\t",$7 }'
}

function show_groups {
    GRUPOS=$(getent group | sed s/:/\ /g | awk '{ print $1 }')
    for grupo in $GRUPOS; do
        echo "Grupo: "$grupo
        cat /etc/group | grep ${grupo} | sed s/:/\ /g |awk '{print $4}'
        echo "=============================="
    done
}

case "$1" in
    "")
        user_names
        ;;

    "grupos")
        show_groups
        ;;

    "help")
        echo "$ usuarios.sh"
        echo "Muestra la lista de usuarios, incluyendo login, nombre, grupo, home directory y shell de inicio."
        echo "$ grupos"
        echo "Muestra cada grupo y sus usuarios"
    esac
