#!/bin/bash

case "$1" in
	"archivos.sh" )
		echo "ayuda"
		;;

	"informacion_sistema.sh" )
		  echo "Nombre del sistema (opción por default)" 
		  echo "Distribución y versión (opción por default)" 
		  echo "Versión del kernel (opción por default)" 
		  echo "Memoria real (usada y libre) (opción -memreal)" 
		  echo "Memoria virtual (usada y libre) (opción -memvirtual)" 
		  echo "Espacio por file system en disco (usado y libre)"
		;;

	"logs.sh" )
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
		;;

	"paquetes.sh" )
		echo "$ paquetes.sh paquete nombredelpaquete"
        echo "Indicara si el paquete esta o no instalado, en caso de no estar instalado mostrara la ruta del repositorio."
        ;;

    "procesos.sh" )
		echo "$ procesos"
		echo "Muestra el uso total de cpu y el arbol de procesos"
		echo ""
		echo "$ procesos usuario nombredeusuario"
		echo "Muestra los procesos de el usuario mostrado"
		echo ""
		echo "$ procesos total"
		echo "Muestra el consumo total de recursos"
		;;

	"usuarios.sh" )
		echo "$ usuarios.sh"
        echo "Muestra la lista de usuarios, incluyendo login, nombre, grupo, home directory y shell de inicio."
        echo "$ grupos"
        echo "Muestra cada grupo y sus usuarios"
        ;;

    "" )
		echo "ayuda"
		;;

	* )
		echo "No hay ayuda para ese comando"
esac