#!/bin/bash

function basic_data {
    echo "Ruta absoluta: "$(readlink -f ${1})
    echo "Tamano: "$(ls -lah ${1} | awk '{ print $5 }')
    echo "Dueno: "$(ls -l ${1} | awk '{ print $3 }')
    echo "Grupo: "$(ls -l ${1} | awk '{ print $4 }')
    echo "Permisos: "$(ls -l ${1} | awk '{ print $1 }')
}

basic_data $1
