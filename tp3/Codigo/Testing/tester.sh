#!/bin/bash
# declare STRING variable

DIR="testing"

rm -rf $DIR
mkdir $DIR

echo "Compilando Codigo..."
g++ -O2 -std=c++0x generador_de_entrada.cpp -o $DIR/tester
g++ -O2 -std=c++0x Ej2/ej2.cpp -o $DIR/ej2
g++ -O2 -std=c++0x Ej3/ej3.cpp -o $DIR/ej3
g++ -O2 -std=c++0x Ej4/ej4.1.cpp -o $DIR/ej4.1
g++ -O2 -std=c++0x Ej4/ej4.2.cpp -o $DIR/ej4.2
g++ -O2 -std=c++0x Ej4/ej4.3.cpp -o $DIR/ej4.3
g++ -O2 -std=c++0x Ej5/ej5A.cpp -o $DIR/ej5A
g++ -O2 -std=c++0x Ej5/ej5B.cpp -o $DIR/ej5B


echo "OK!"

for numeroDeNodos in {1..100}
do
	echo "generada entrada para n:" $numeroDeNodos
    ./$DIR/tester 23 253 2
    ./$DIR/ej2 < $DIR/test.txt >> $DIR/resultados2.txt
    ./$DIR/ej3 < $DIR/test.txt >> $DIR/resultados3.txt
    ./$DIR/ej4.1 < $DIR/test.txt >> $DIR/resultados4.txt
    ./$DIR/ej4.2 < $DIR/test.txt >> $DIR/resultados5.txt
    ./$DIR/ej4.3 < $DIR/test.txt >> $DIR/resultados6.txt
    ./$DIR/ej5A < $DIR/test.txt >> $DIR/resultados7.txt
    ./$DIR/ej5B < $DIR/test.txt >> $DIR/resultados8.txt
    echo "OK!"
done

echo "Prosesando Resultados..."

#tiempos son las lineas pares
sed -n 2~2p $DIR/resultados2.txt > $DIR/tiempos2.txt
sed -n 2~2p $DIR/resultados3.txt > $DIR/tiempos3.txt
sed -n 2~2p $DIR/resultados4.txt > $DIR/tiempos4.txt
sed -n 2~2p $DIR/resultados5.txt > $DIR/tiempos5.txt
sed -n 2~2p $DIR/resultados6.txt > $DIR/tiempos6.txt
sed -n 2~2p $DIR/resultados7.txt > $DIR/tiempos7.txt
sed -n 2~2p $DIR/resultados8.txt > $DIR/tiempos8.txt

#performanece en las lineas impares
sed -n 1~2p $DIR/resultados2.txt > $DIR/performanece2.txt
sed -n 1~2p $DIR/resultados3.txt > $DIR/performanece3.txt
sed -n 1~2p $DIR/resultados4.txt > $DIR/performanece4.txt
sed -n 1~2p $DIR/resultados5.txt > $DIR/performanece5.txt
sed -n 1~2p $DIR/resultados6.txt > $DIR/performanece6.txt
sed -n 1~2p $DIR/resultados7.txt > $DIR/performanece7.txt
sed -n 1~2p $DIR/resultados8.txt > $DIR/performanece8.txt

#copio todos los tiempos en un solo lugar
paste $DIR/tiempos2.txt $DIR/tiempos3.txt > $DIR/aux1.txt
paste $DIR/tiempos4.txt $DIR/tiempos5.txt > $DIR/aux2.txt
paste $DIR/tiempos6.txt $DIR/tiempos7.txt > $DIR/aux3.txt
paste $DIR/aux3.txt tiempos8.txt > $DIR/aux5.txt
paste $DIR/aux1.txt $DIR/aux2.txt > $DIR/aux4.txt
paste $DIR/aux4.txt $DIR/aux5.txt > $DIR/TIEMPOS

#copio todos las performances (resultados) en un solo lugar
paste $DIR/performanece2.txt $DIR/performanece3.txt > $DIR/aux1.txt
paste $DIR/performanece4.txt $DIR/performanece5.txt > $DIR/aux2.txt
paste $DIR/performanece6.txt $DIR/performanece7.txt > $DIR/aux3.txt
paste $DIR/aux3.txt performanece8.txt > $DIR/aux5.txt
paste $DIR/aux1.txt $DIR/aux2.txt > $DIR/aux4.txt
paste $DIR/aux4.txt $DIR/aux5.txt > $DIR/PERFORMANCE

echo "Limpiando Archivos"

rm -rf $DIR/tester
rm -rf $DIR/ej2
rm -rf $DIR/ej3
rm -rf $DIR/ej4
rm -rf $DIR/ej5
rm -rf $DIR/*.txt

echo "OK!"
