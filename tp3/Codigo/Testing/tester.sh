#!/bin/bash
# declare STRING variable

DIR="testing"

rm -rf $DIR
mkdir $DIR

echo "Compilando Codigo..."
g++ -std=c++11 generador_de_entrada.cpp -o $DIR/tester
g++ -std=c++11 Ej2/ej2.cpp -o $DIR/ej2
g++ -std=c++11 Ej3/ej3.cpp -o $DIR/ej3
g++ -std=c++11 Ej4/ej4.cpp -o $DIR/ej4
g++ -std=c++11 Ej5/ej5.cpp -o $DIR/ej5

echo "OK!"

for numeroDeNodos in {100..150}
do
	echo "generada entrada para n:" $numeroDeNodos "con aristas de 1 a 100"
	for numeroDeAristas in {100..100}
	do
        ./$DIR/tester $numeroDeNodos $(( (numeroDeNodos*(numeroDeNodos-1))/2 )) 10
        #tarda mucho
        #./$DIR/ej2 < $DIR/test.txt >> $DIR/resultados2.txt
        ./$DIR/ej3 < $DIR/test.txt >> $DIR/resultados3.txt
        ./$DIR/ej4 < $DIR/test.txt >> $DIR/resultados4.txt
        ./$DIR/ej5 < $DIR/test.txt >> $DIR/resultados5.txt
    done
    echo "OK!"
done

echo "Limpio los binarios"
rm -rf $DIR/tester
rm -rf $DIR/ej2
rm -rf $DIR/ej3
rm -rf $DIR/ej4
rm -rf $DIR/ej5
echo "OK!"