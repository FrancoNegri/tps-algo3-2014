#!/bin/bash
# declare STRING variable

DIR="testing"


echo "Borrando restos del testing anterior..."
rm -rf $DIR

mkdir $DIR

echo "Compilando Codigo..."
g++ -std=c++0x generadorDeEntrada.cpp -o $DIR/tester
g++ -std=c++0x ej3.cpp -o $DIR/ejecutable
echo "OK!"

echo "Seteo de parametros"
echo "Cantidad De tests:"
read numeroDeTests
echo "Valor mas chico de m:"
read COTAINFERIOR
echo "Valor mas alto: "
read COTASUPERIOR
echo "Valor fijo de m:"
read n

for (( c=$COTAINFERIOR ; c<=$COTASUPERIOR; c++ ))
do
	echo "generada entrada para m:" $c
	inicio=1
	for (( j=$inicio ; j<=$numeroDeTests ; j++))
	do
        	./$DIR/tester $n $c
        	./$DIR/ejecutable < $DIR/test.txt >> $DIR/resultados.txt
    	done
    echo "OK!"
    echo "" >> $DIR/resultados.txt #agrego un end of line, asi voy creando una matriz con los resultados
done

echo "Limpio los binarios"
rm -rf $DIR/tester
rm -rf $DIR/ejecutable
echo "OK!"
