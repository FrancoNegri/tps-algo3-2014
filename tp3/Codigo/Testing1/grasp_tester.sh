#!/bin/bash
# declare STRING variable

DIR="testing"


rm $DIR/*
g++ -O2 -std=c++0x generador_de_entrada.cpp -o $DIR/tester

 g++ -O2 -std=c++0x Ej2/ej2.cpp -o $DIR/ej2
 g++ -O2 -std=c++0x Ej3/ej3.cpp -o $DIR/ej3
 g++ -O2 -std=c++0x Ej4/ej4.1.cpp -o $DIR/ej4.1
 g++ -O2 -std=c++0x Ej5/ej5A.cpp -o $DIR/ej5A

for test in {1..100}
do
    ./$DIR/generador_de_entrada 19 171 4
    ./$DIR/ej2 < $DIR/test.in >> $DIR/resultados2.txt
    ./$DIR/ej3 < $DIR/test.in >> $DIR/resultados3.txt
    ./$DIR/ej4.1 < $DIR/test.in >> $DIR/resultados4.txt
    #./$DIR/ej4.2 < $DIR/test.in >> $DIR/resultados5.txt
    #./$DIR/ej4.3 < $DIR/test.in >> $DIR/resultados6.txt
    ./$DIR/ej5A < $DIR/test.in >> $DIR/resultados7.txt
    #./$DIR/ej5B < $DIR/test.in >> $DIR/resultados8.txt
done

for i in 2 3 4 7
do
    sed -n 2~2p resultados$i.txt > tiempo$i
    sed -n 1~2p resultados$i.txt > respuesta$i
done

paste tiempo2 tiempo3 tiempo4 tiempo7 > tiempos
paste respuesta2 respuesta3 respuesta4 respuesta7 > respuestas

rm $DIR/*.txt