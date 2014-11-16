#!/bin/bash
# declare STRING variable

DIR="testing"

rm -rf $DIR
mkdir $DIR

echo "Compilando Codigo..."
g++ -O2 generador_de_entrada.cpp -o $DIR/tester
g++ -O2 Ej2/ej2.cpp -o $DIR/ej2
g++ -O2 Ej3/ej3.cpp -o $DIR/ej3
g++ -O2 Ej4/ej4.1.cpp -o $DIR/ej4.1
g++ -O2 Ej4/ej4.2.cpp -o $DIR/ej4.2
g++ -O2 Ej5/ej5.cpp -o $DIR/ej5

echo "OK!"

for numeroDeNodos in {1..100}
do
	echo "generada entrada para n:" $numeroDeNodos
    ./$DIR/tester 23 253 2
    ./$DIR/ej2 < $DIR/test.txt >> $DIR/resultados2.txt
    ./$DIR/ej3 < $DIR/test.txt >> $DIR/resultados3.txt
    ./$DIR/ej4.1 < $DIR/test.txt >> $DIR/resultados4.txt
    ./$DIR/ej4.2 < $DIR/test.txt >> $DIR/resultados5.txt
    ./$DIR/ej5 < $DIR/test.txt >> $DIR/resultados6.txt
    echo "OK!"
done

echo "Limpio los binarios"

paste $DIR/resultados2.txt $DIR/resultados3.txt > $DIR/aux1.txt
paste $DIR/resultados4.txt $DIR/resultados5.txt > $DIR/aux2.txt
paste $DIR/aux1.txt $DIR/aux2.txt > $DIR/aux3.txt
paste $DIR/aux3.txt $DIR/resultados6.txt > $DIR/RESULTADOS

rm -rf $DIR/tester
rm -rf $DIR/ej2
rm -rf $DIR/ej3
rm -rf $DIR/ej4
rm -rf $DIR/ej5
rm -rf *.txt

echo "OK!"
