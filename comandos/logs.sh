#!/bin/bash

function show_logfiles {
    find /var/log/ -maxdepth 2 -name "*.log"
    find /var/log/ -maxdepth 2 -name "log.*"
}

function show_help {
    echo "$ logs.sh"
    echo "Enlista los logs disponibles"
    echo "$ logs.sh head numerodelineas archivo"
    echo "Muestra las primeras n lineas del archivo"
    echo "$ logs.sh tail numerodelineas archivo"
    echo "Muestra las ultimas n lineas del archivo"
    echo "$ logs.sh pattern patron archivo"
    echo "Busca el patron en el archivo especificado"
    echo "$ logs.sh pattern patron archivo after numerodelineas"
    echo "Busca el patron y muestra n lineas despues del patron"
    echo "$ logs.sh pattern patron archivo before numerodelineas"
    echo "Busca el patron y muestra n lineas antes del patron"
}

case "$1" in
    "")
        show_logfiles
        ;;

    "head")
        if [ -z "$2" ] || [ -z "$3" ]; then
            show_help
        else
            head -n ${2} ${3}
        fi
        ;;

    "tail")
        if [ -z "$2" ] || [ -z "$3" ]; then
            show_help
        else
            tail -n ${2} ${3}
        fi
        ;;    

    "pattern")
        if [ -z "$2" ] || [ -z "$3" ]; then
            show_help
        else
            case "$4" in
                "")
                    cat $3 | grep "$2" -A 3 -B 3 
                    ;;
                    
                "after")
                    if [ -z $5 ];then
                        show_help
                    else
                        cat $3 | grep "$2" -A $5
                    fi
                    ;;

                "before")
                    if [ -z $5 ];then
                        show_help
                    else
                        cat $3 | grep "$2" -B $5
                    fi
                    ;;

                *)
                    show_help
                    ;;

            esac
        fi
        ;;

        "help" | *)
            show_help
        ;;

    esac
