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
     ./$DIR/tester 18 $((18*17/2)) 4
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
    sed -n 2~2p $DIR/resultados$i.txt > $DIR/tiempo$i.txt
    sed -n 1~2p $DIR/resultados$i.txt > $DIR/respuesta$i.txt
done

paste $DIR/tiempo2.txt $DIR/tiempo3.txt $DIR/tiempo4.txt $DIR/tiempo7.txt > $DIR/tiempos
paste $DIR/respuesta2.txt $DIR/respuesta3.txt $DIR/respuesta4.txt $DIR/respuesta7.txt > $DIR/respuestas

rm $DIR/*.txt
