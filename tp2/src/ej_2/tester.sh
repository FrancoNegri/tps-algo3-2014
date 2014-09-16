#!/bin/bash
# declare STRING variable

DIR="testing"

rm -rf $DIR

mkdir $DIR

echo "Compilando Codigo..."
g++ -std=c++0x generadorDeEntrada.cpp -o $DIR/tester
g++ -std=c++0x ej2_b.cpp -o $DIR/ejecutable

echo "OK!"

for VARIABLE in {1..10}
do
        echo "generada entrada para n:" $VARIABLE
        ./$DIR/tester $VARIABLE 10
        echo "OK!"
        echo "Corriendo ejecutable..."
        ./$DIR/ejecutable < $DIR/test.txt > $DIR/$VARIABLE.txt
        echo "OK!"
done

echo "Limpio los binarios"
rm -rf $DIR/tester
rm -rf $DIR/ejecutable
echo "OK!"