#!/bin/bash
# declare STRING variable

DIR="testing"


rm $DIR/*
g++ -O2 -std=c++0x generador_de_entrada.cpp -o $DIR/tester



for equis in {0..100}
do
    echo "Compilando Codigo con x =" $equis
    g++ -O2 -std=c++0x Ej5/ej5A.cpp -D PORCENTAJEDEMEJORES=$equis -o $DIR/G1
    g++ -O2 -std=c++0x Ej5/ej5B.cpp -D PORCENTAJEDEMEJORES=$equis -o $DIR/G2
    g++ -O2 -std=c++0x Ej5/ej5C.cpp -D PORCENTAJEDEMEJORES=$equis -o $DIR/G3
    echo "OK!"
    echo "Corriendo Tests"
    for test in {1..4}
    do
        ./$DIR/tester 500 124750 100
        ./$DIR/G1 < $DIR/test.in >> $DIR/r1$test.txt
        ./$DIR/G2 < $DIR/test.in >> $DIR/r2$test.txt
        ./$DIR/G3 < $DIR/test.in >> $DIR/r3$test.txt
    done
    echo "OK!"
done


#     echo "Compilando Codigo con x =" $equis
#     g++ -O2 -std=c++0x Ej5/ej5A.cpp -D PORCENTAJEDEMEJORES=20 -o $DIR/G1
#     g++ -O2 -std=c++0x Ej5/ej5B.cpp -D PORCENTAJEDEMEJORES=20 -o $DIR/G2
#     g++ -O2 -std=c++0x Ej5/ej5C.cpp -D PORCENTAJEDEMEJORES=20 -o $DIR/G3
#     echo "OK!"
#     echo "Corriendo Tests"
#     for test in {1..100}
#     do
#         ./$DIR/tester 500 124750 100
#         ./$DIR/G1 < $DIR/test.in >> $DIR/r1$test.txt
#         ./$DIR/G2 < $DIR/test.in >> $DIR/r2$test.txt
#         ./$DIR/G3 < $DIR/test.in >> $DIR/r3$test.txt
#     done
#     echo "OK!"

#         echo "Compilando Codigo con x =" $equis
#     g++ -O2 -std=c++0x Ej5/ej5A.cpp -D PORCENTAJEDEMEJORES=25 -o $DIR/G1
#     g++ -O2 -std=c++0x Ej5/ej5B.cpp -D PORCENTAJEDEMEJORES=25 -o $DIR/G2
#     g++ -O2 -std=c++0x Ej5/ej5C.cpp -D PORCENTAJEDEMEJORES=25 -o $DIR/G3
#     echo "OK!"
#     echo "Corriendo Tests"
#     for test in {1..100}
#     do
#         ./$DIR/tester 500 124750 100
#         ./$DIR/G1 < $DIR/test.in >> $DIR/r1$test.txt
#         ./$DIR/G2 < $DIR/test.in >> $DIR/r2$test.txt
#         ./$DIR/G3 < $DIR/test.in >> $DIR/r3$test.txt
#     done
#     echo "OK!"

#         echo "Compilando Codigo con x =" $equis
#     g++ -O2 -std=c++0x Ej5/ej5A.cpp -D PORCENTAJEDEMEJORES=30 -o $DIR/G1
#     g++ -O2 -std=c++0x Ej5/ej5B.cpp -D PORCENTAJEDEMEJORES=30 -o $DIR/G2
#     g++ -O2 -std=c++0x Ej5/ej5C.cpp -D PORCENTAJEDEMEJORES=30 -o $DIR/G3
#     echo "OK!"
#     echo "Corriendo Tests"
#     for test in {1..100}
#     do
#         ./$DIR/tester 500 124750 100
#         ./$DIR/G1 < $DIR/test.in >> $DIR/r1$test.txt
#         ./$DIR/G2 < $DIR/test.in >> $DIR/r2$test.txt
#         ./$DIR/G3 < $DIR/test.in >> $DIR/r3$test.txt
#     done
#     echo "OK!"

#         echo "Compilando Codigo con x =" $equis
#     g++ -O2 -std=c++0x Ej5/ej5A.cpp -D PORCENTAJEDEMEJORES=35 -o $DIR/G1
#     g++ -O2 -std=c++0x Ej5/ej5B.cpp -D PORCENTAJEDEMEJORES=35 -o $DIR/G2
#     g++ -O2 -std=c++0x Ej5/ej5C.cpp -D PORCENTAJEDEMEJORES=35 -o $DIR/G3
#     echo "OK!"
#     echo "Corriendo Tests"
#     for test in {1..100}
#     do
#         ./$DIR/tester 500 124750 100
#         ./$DIR/G1 < $DIR/test.in >> $DIR/r1$test.txt
#         ./$DIR/G2 < $DIR/test.in >> $DIR/r2$test.txt
#         ./$DIR/G3 < $DIR/test.in >> $DIR/r3$test.txt
#     done
#     echo "OK!"

#         echo "Compilando Codigo con x =" $equis
#     g++ -O2 -std=c++0x Ej5/ej5A.cpp -D PORCENTAJEDEMEJORES=40 -o $DIR/G1
#     g++ -O2 -std=c++0x Ej5/ej5B.cpp -D PORCENTAJEDEMEJORES=40 -o $DIR/G2
#     g++ -O2 -std=c++0x Ej5/ej5C.cpp -D PORCENTAJEDEMEJORES=40 -o $DIR/G3
#     echo "OK!"
#     echo "Corriendo Tests"
#     for test in {1..100}
#     do
#         ./$DIR/tester 500 124750 100
#         ./$DIR/G1 < $DIR/test.in >> $DIR/r1$test.txt
#         ./$DIR/G2 < $DIR/test.in >> $DIR/r2$test.txt
#         ./$DIR/G3 < $DIR/test.in >> $DIR/r3$test.txt
#     done
#     echo "OK!"

#testeo si es un valor fijo de "oro" o es un porcentaje que varía con k
# echo "Compilando Codigo con x =" $equis
# g++ -O2 -std=c++0x Ej5/ej5A.cpp -D PORCENTAJEDEMEJORES=30 -o $DIR/G1
# g++ -O2 -std=c++0x Ej5/ej5B.cpp -D PORCENTAJEDEMEJORES=30 -o $DIR/G2
# g++ -O2 -std=c++0x Ej5/ej5C.cpp -D PORCENTAJEDEMEJORES=30 -o $DIR/G3
# echo "OK!"
# echo "Corriendo Tests"
# for test in {1..4}
# do
#     ./$DIR/tester 500 124750 100
#     ./$DIR/G1 < $DIR/test.in >> $DIR/r1$test.txt
#     ./$DIR/G2 < $DIR/test.in >> $DIR/r2$test.txt
#     ./$DIR/G3 < $DIR/test.in >> $DIR/r3$test.txt
# done
# echo "OK!"


# echo "Compilando Codigo con x =" $equis
# g++ -O2 -std=c++0x Ej5/ej5A.cpp -D PORCENTAJEDEMEJORES=3 -o $DIR/G1
# g++ -O2 -std=c++0x Ej5/ej5B.cpp -D PORCENTAJEDEMEJORES=3 -o $DIR/G2
# g++ -O2 -std=c++0x Ej5/ej5C.cpp -D PORCENTAJEDEMEJORES=3 -o $DIR/G3
# echo "OK!"
# echo "Corriendo Tests"
# for test in {1..4}
# do
#     ./$DIR/tester 500 124750 100
#     ./$DIR/G1 < $DIR/test.in >> $DIR/r1$test.txt
#     ./$DIR/G2 < $DIR/test.in >> $DIR/r2$test.txt
#     ./$DIR/G3 < $DIR/test.in >> $DIR/r3$test.txt
# done
# echo "OK!"


echo "Procesando Resultados..."
#tiempos son las lineas pares
for test in {1..100}
do
    sed -n 2~2p $DIR/r1$test.txt > $DIR/t1$test.txt
    sed -n 2~2p $DIR/r2$test.txt > $DIR/t2$test.txt
    sed -n 2~2p $DIR/r3$test.txt > $DIR/t3$test.txt
    # #performanece en las lineas impares
    sed -n 1~2p $DIR/r1$test.txt > $DIR/p1$test.txt
    sed -n 1~2p $DIR/r2$test.txt > $DIR/p2$test.txt
    sed -n 1~2p $DIR/r3$test.txt > $DIR/p3$test.txt
done

echo "" > $DIR/resultados1
echo "" > $DIR/tiempos1
echo "" > $DIR/resultados2
echo "" > $DIR/tiempos2
echo "" > $DIR/resultados3
echo "" > $DIR/tiempos3


for test in {1..100}
do
    paste $DIR/resultados1 $DIR/t1$test.txt > $DIR/aux1.txt
    paste $DIR/resultados2 $DIR/t2$test.txt > $DIR/aux2.txt
    paste $DIR/resultados3 $DIR/t3$test.txt > $DIR/aux3.txt
    
    paste $DIR/tiempos1 $DIR/p1$test.txt > $DIR/aux4.txt
    paste $DIR/tiempos2 $DIR/p2$test.txt > $DIR/aux5.txt
    paste $DIR/tiempos3 $DIR/p3$test.txt > $DIR/aux6.txt

    rm $DIR/resultados1
    rm $DIR/resultados2
    rm $DIR/resultados3

    rm $DIR/tiempos1
    rm $DIR/tiempos2
    rm $DIR/tiempos3

    cp $DIR/aux1.txt $DIR/resultados1
    cp $DIR/aux2.txt $DIR/resultados2
    cp $DIR/aux3.txt $DIR/resultados3

    cp $DIR/aux4.txt $DIR/tiempos1
    cp $DIR/aux5.txt $DIR/tiempos2
    cp $DIR/aux6.txt $DIR/tiempos3
done
echo "Limpiando Archivos"
rm -rf $DIR/tester
#rm -rf $DIR/G*
rm -rf $DIR/*.txt
echo "OK!"
