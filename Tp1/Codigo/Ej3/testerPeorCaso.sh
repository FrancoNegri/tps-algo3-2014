#!/bin/bash
# declare STRING variable

DIR="testingPeorCaso"
back1="/backtrack"
back2="/backtrack_invertido"
back3="/backtrack_random"
back4="/fuerzaBruta"

rm -rf $DIR

mkdir $DIR
mkdir $DIR$back1
mkdir $DIR$back2
mkdir $DIR$back3
mkdir $DIR$back4

echo "Compilando Codigo..."
g++ -std=c++0x generadorDeEntrada.cpp -o $DIR/tester
g++ -std=c++0x Ej3.cpp -o $DIR$back1/backtrack1
g++ -std=c++0x Ej3_podas_invertidas.cpp -o $DIR$back2/backtrack_invertido
g++ -std=c++0x Ej3_random.cpp -o $DIR$back3/backtrack_random
g++ -std=c++0x fuerzaBruta.cpp -o $DIR$back4/fuerzaBruta
echo "OK!"

sl="/"
ext=".txt"
for VARIABLE in {1..10}
do
	
	./$DIR/tester $VARIABLE 10
	echo "generada entrada para n:" $VARIABLE
	echo "Corriendo Backtrack..."
	./$DIR$back1/backtrack1 < $DIR/test.txt > $DIR$back1$sl$VARIABLE$ext
	echo "Corriendo Backtrack Invertido..."
	./$DIR$back2/backtrack_invertido < $DIR/test.txt > $DIR$back2$sl$VARIABLE$ext
	echo "Corriendo Backtrack random..."
	#./$DIR$back3/backtrack_random < $DIR/test.txt > $DIR$back3$sl$VARIABLE$ext
	echo "Corriendo Fuerza Bruta..."
	./$DIR$back4/fuerzaBruta < $DIR/test.txt > $DIR$back4$sl$VARIABLE$ext
	echo "OK!"
done
