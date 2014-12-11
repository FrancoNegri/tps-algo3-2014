#!/bin/bash
# declare STRING variable

DIR="testing"

rm $DIR/*.txt

for equis in {1..20}
do
    echo "Compilando Codigo con x =" $equis
    g++ -O2 -std=c++0x Ej5/ej5A.cpp -D PORCENTAJEDEMEJORES=$equis -o $DIR/G1
    g++ -O2 -std=c++0x Ej5/ej5B.cpp -D PORCENTAJEDEMEJORES=$equis -o $DIR/G2
    g++ -O2 -std=c++0x Ej5/ej5C.cpp -D PORCENTAJEDEMEJORES=$equis -o $DIR/G3
    echo "OK!"
    echo "Corriendo Test"
        ./$DIR/G1 < $DIR/test.in >> $DIR/r1.txt
        ./$DIR/G2 < $DIR/test.in >> $DIR/r2.txt
        ./$DIR/G3 < $DIR/test.in >> $DIR/r3.txt
    echo "OK!"
done

echo "Procesando Resultados..."
#tiempos son las lineas pares
sed -n 2~2p $DIR/r1.txt > $DIR/t1.txt
sed -n 2~2p $DIR/r2.txt > $DIR/t2.txt
sed -n 2~2p $DIR/r3.txt > $DIR/t3.txt
# #performanece en las lineas impares
sed -n 1~2p $DIR/r1.txt > $DIR/p1.txt
sed -n 1~2p $DIR/r2.txt > $DIR/p2.txt
sed -n 1~2p $DIR/r3.txt > $DIR/p3.txt
# #copio todos los tiempos en un solo lugar
paste $DIR/p1.txt $DIR/p2.txt $DIR/p3.txt > $DIR/Performance
# #copio todos las performances (resultados) en un solo lugar
paste $DIR/t1.txt $DIR/t2.txt $DIR/t2.txt > $DIR/Tiempo
echo "Limpiando Archivos"
rm -rf $DIR/tester
rm -rf $DIR/G*
rm -rf $DIR/*.txt
echo "OK!"
