#!/bin/bash
# declare STRING variable

DIR="testing"

rm -rf $DIR

mkdir $DIR

echo "Compilando Codigo..."
g++ -std=c++11 generadorDeEntrada.cpp -o $DIR/tester
g++ -std=c++11 ej_1_no_graph.cpp -o $DIR/ejecutable

echo "OK!"

for VARIABLE1 in {1..50}
do
	echo "generada entrada para n:" $(($VARIABLE1 * 10))
	for VARIABLE2 in {1..50}
	do
        ./$DIR/tester $(($VARIABLE1 * 10)) 10
        ./$DIR/ejecutable < $DIR/test.txt >> $DIR/resultados.txt
        
    done
    echo "OK!"
    echo "" >> $DIR/resultados.txt #agrego un end of line, asi voy creando una matriz con los resultados
done

echo "Limpio los binarios"
rm -rf $DIR/tester
rm -rf $DIR/ejecutable
echo "OK!"